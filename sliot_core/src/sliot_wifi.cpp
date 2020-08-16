#include "../inc/sliot_wifi.hpp"

sliot_wifi_c::sliot_wifi_c(void)
  : sliot_internet_if_c()
{
  sliot_core_logger.println("Constructing Wi-Fi Object");  
  ssid     = SLIOT_WIFI_DEFAULT_SSID;
  password = SLIOT_WIFI_DEFAULT_PASSWORD;
}

sliot_result_e sliot_wifi_c::wait_for_connection(sliot_time_ms_t timeout)
{
  sliot_result_e ret_val = SLIOT_RESULT_FAILURE;

  sliot_time_ms_t time_last = millis();
  sliot_time_ms_t time_now  = millis();

  do
  {
    if( connected() )
    {
      ret_val = SLIOT_RESULT_SUCCESS;
      break;
    }
    time_now  = millis();
  }
  while ( (time_now - time_last) < timeout);

  return ret_val;
}