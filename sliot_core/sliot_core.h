#ifndef _SLIOT_CORE_H_
#define _SLIOT_CORE_H_

//Include IoT Core Internal Common Definitions
#include "sliot_core_internal.h"

#ifdef SLIOT_SERIAL_ENABLED
#include "sliot_serial.h"
#endif

//MQTT if enabled
#ifdef SLIOT_MQTT_ENABLED
#include "sliot_mqtt.h"
#endif

//ESP32 WiFi if enabled
#ifdef SLIOT_WIFI_ESP32_ENABLED
#include "sliot_wifi_esp32.h"
#endif

#endif //_SLIOT_CORE_H_
