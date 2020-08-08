/*
    Basic program to test Sandor Labortories IoT Core
*/

#include "inc/sliot_core.hpp"

uint32_t sliot_core_test_counter;
extern sliot_wifi_c *sliot_wifi;

void setup
(
)
{
  sliot_result_e result;
  sliot_core_test_counter = 0;

  result = sliot_core_init();
  sliot_core_logger.println("Sliot Core Initialized.  Status " + String(result));

  if(sliot_wifi)
  {
    sliot_wifi->connect();
    if(SLIOT_RESULT_SUCCESS == sliot_wifi->wait_for_connection(30000))
    {
      sliot_core_logger.println("Connected to Wi-Fi");      
      sliot_core_logger.println("IP: " + sliot_wifi->get_ip_addr().string() + "/" + String(sliot_wifi->get_subnet_cidr()));
      sliot_core_logger.println("Subnet: " + sliot_wifi->get_subnet().string());
      sliot_core_logger.println("Gateway: " + sliot_wifi->get_gateway_addr().string());
      sliot_core_logger.println("x-mqtt: " + sliot_wifi->dns_lookup("x-mqtt.lan.ewsandor.com").string());
    }
    else
    {
      sliot_core_logger.println("Wi-Fi connection failed");        
    }
  }
  
}

void loop() {

  sliot_core_test_counter++;

}
