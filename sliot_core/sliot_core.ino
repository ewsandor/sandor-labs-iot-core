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
    if(SLIOT_RESULT_SUCCESS == sliot_wifi->wait_for_connection(5000))
    {
      sliot_core_logger.println("Connected to Wi-Fi");      
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
