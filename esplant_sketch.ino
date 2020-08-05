/* Basic program to run ESPlant from Arduino.  
 *  
 * Data is reported to Cayenne MQTT.  https://developers.mydevices.com/cayenne/features/
 *
 */

#include <CayenneMQTTESP32.h>
#include <Wire.h>

#define si7021Addr 0x40

#include "esplant_cayenne_key.h"
#include "esplant_wifi_config.h"

#define ESPLANT_CAYENNE_ENABLE

#define ESPLANT_SDA_GPIO         21
#define ESPLANT_SCL_GPIO         22
#define ESPLANT_SENSOR_EN_GPIO   26
#define ESPLANT_TH_EN_GPIO       27
#define ESPLANT_PUMP_GPIO        32
#define ESPLANT_BATT_ANALOG_GPIO 33
#define ESPLANT_SOIL_ANALOG_GPIO 34
#define ESPLANT_AMBL_ANALOG_GPIO 35

#define ESPLANT_CAYENNE_BATTERY_LEVEL_CHANNEL 0
#define ESPLANT_CAYENNE_SOIL_MOISTURE_CHANNEL 1
#define ESPLANT_CAYENNE_AMBIENT_LIGHT_CHANNEL 2

#define ESPLANT_ADC_REF_VOLTAGE 3300 //mV
#define ESPLANT_ADC_MAX 4096

#define ESPLANT_BATTERY_VDIV_R1 33
#define ESPLANT_BATTERY_VDIV_R2 51

#define ESPLANT_SOIL_MOISTURE_AIR   3200
#define ESPLANT_SOIL_MOISTURE_WATER 1500
#define ESPLANT_SOIL_MOISTURE_RANGE (ESPLANT_SOIL_MOISTURE_AIR - ESPLANT_SOIL_MOISTURE_WATER)

const char* wifi_ssid     = ESPLANT_DEFAULT_WIFI_SSID;
const char* wifi_password = ESPLANT_DEFAULT_WIFI_PASSWORD;

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  600         /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

/*
Method to print the reason by which ESP32
has been awaken from sleep
*/
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

int esplant_get_battery_level()
{
  
  int battery_level = 0;
  
  //Read battery level
  int battery_level_raw = analogRead(ESPLANT_BATT_ANALOG_GPIO);  

  //Battery level = ((adc_raw/adc_max)*adc_ref(v) ) / ( R2 / (R1+R2) )
  battery_level = ( battery_level_raw * ESPLANT_ADC_REF_VOLTAGE * (ESPLANT_BATTERY_VDIV_R1 + ESPLANT_BATTERY_VDIV_R2) ) / (ESPLANT_ADC_MAX * ESPLANT_BATTERY_VDIV_R2);

  Serial.println("Battery Level: " + String(battery_level_raw) + ", " + String(battery_level) + "mV");
  
  return battery_level;    
}


int esplant_get_soil_moisture()
{
  int soil_moisture = 0;

  //Read soil moisture
  int soil_moisture_raw = analogRead(ESPLANT_SOIL_ANALOG_GPIO);  

  soil_moisture = soil_moisture_raw;

  // Limit value if soil moisture if below reading of water, recailbration may be needed if exceeding value
  soil_moisture = max(soil_moisture, ESPLANT_SOIL_MOISTURE_WATER);
  // Limit value if soil moisture if above reading of air, recailbration may be needed if exceeding value
  soil_moisture = min(soil_moisture, ESPLANT_SOIL_MOISTURE_AIR);

  /* Find percentage of water vs air */
  soil_moisture = ( 100 * (soil_moisture - ESPLANT_SOIL_MOISTURE_WATER) ) / ESPLANT_SOIL_MOISTURE_RANGE;

  /* Invert percentage such that more moisture is higher percentage */
  soil_moisture = 100 - soil_moisture;
  
  Serial.println("Soil Moisture: " + String(soil_moisture_raw) + ", " + String(soil_moisture) + "%");

  return soil_moisture;
}

int esplant_get_ambient_light()
{
  int ambient_light = 0;

  //Read ambient light
  int ambient_light_raw = analogRead(ESPLANT_AMBL_ANALOG_GPIO);

  ambient_light = (100 * ambient_light_raw) / ESPLANT_ADC_MAX;
  
  Serial.println("Ambient Light: " + String(ambient_light_raw) + ", " + String(ambient_light) + "%");

  return ambient_light;
}


void setup() {

  pinMode(ESPLANT_SENSOR_EN_GPIO, OUTPUT);
  pinMode(ESPLANT_TH_EN_GPIO, OUTPUT);
  pinMode(ESPLANT_PUMP_GPIO, OUTPUT);
  digitalWrite(ESPLANT_SENSOR_EN_GPIO, HIGH);
  digitalWrite(ESPLANT_TH_EN_GPIO, LOW);
  digitalWrite(ESPLANT_PUMP_GPIO, LOW);

  Serial.begin(115200);
  delay(10);

  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("");
  Serial.println("Boot number: " + String(bootCount));

  //Print the wakeup reason for ESP32
  print_wakeup_reason();
    
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for " + String(TIME_TO_SLEEP) +
  " Seconds");


  Serial.println("");
  Serial.println("Enabling Sensors");
  digitalWrite(ESPLANT_SENSOR_EN_GPIO, LOW);
  delay(100);
  
  Serial.println("");
  Serial.println("Reading Sensors");

  int battery_level = esplant_get_battery_level();
  int soil_moisture = esplant_get_soil_moisture();
  int ambient_light = esplant_get_ambient_light();

  Serial.println("");
  Serial.println("Disabling Sensors");
  digitalWrite(ESPLANT_SENSOR_EN_GPIO, HIGH);    


#ifdef ESPLANT_CAYENNE_ENABLE
  /* Connect to Cayenne */
  Serial.println("");
  Serial.println("Connecting to Cayenne");
  Cayenne.begin(ESPLANT_CAYENNE_MQTT_USERNAME, ESPLANT_CAYENNE_MQTT_PASSWORD, ESPLANT_CAYENNE_MQTT_CLIENT_ID, wifi_ssid, wifi_password);
  Serial.println("Reporting to Cayenne");    
  Cayenne.virtualWrite(ESPLANT_CAYENNE_BATTERY_LEVEL_CHANNEL, ((float)battery_level)/1000, "batt" , "v");
  Cayenne.virtualWrite(ESPLANT_CAYENNE_SOIL_MOISTURE_CHANNEL, soil_moisture, "soil_moist", "p");
  Cayenne.virtualWrite(ESPLANT_CAYENNE_AMBIENT_LIGHT_CHANNEL, ambient_light, "lum", "p");
  Cayenne.loop();
#endif

  Serial.println("");
  Serial.println("Going to sleep");
  Serial.println("#####################################################################");
  Serial.flush(); 
  esp_deep_sleep_start();
}

void loop() {

  /* This will not be called */

}
