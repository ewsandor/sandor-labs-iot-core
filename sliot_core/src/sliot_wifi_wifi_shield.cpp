#include <WiFi.h>

#include "../inc/sliot_core_internal.hpp"
#include "../inc/sliot_wifi_wifi_shield.hpp"

sliot_wifi_wifi_shield_c *sliot_wifi_wifi_shield;

sliot_wifi_c *sliot_wifi_wifi_shield_c::sliot_wifi_wifi_shield_init()
{
  sliot_core_logger.println("Initializing Wi-Fi Shield");  

  sliot_wifi_c * sliot_wifi = new sliot_wifi_wifi_shield_c();
  
  return sliot_wifi;
}

/* Connect to WiFi */
sliot_result_e sliot_wifi_wifi_shield_c::connect()
{
  return connect(SLIOT_WIFI_DEFAULT_TIMEOUT);
}
sliot_result_e sliot_wifi_wifi_shield_c::connect(sliot_time_ms_t timeout)
{
  sliot_core_logger.println("Connecting to Wi-Fi AP '" + String(ssid) + "'");
  WiFi.begin(ssid, password);
  return wait_for_connection(timeout);
}
/* Disconnect from WiFi */
sliot_result_e sliot_wifi_wifi_shield_c::disconnect()
{
  return SLIOT_RESULT_FAILURE;
}
/* Check current Wi-Fi status */
sliot_wifi_status_e sliot_wifi_wifi_shield_c::wifi_status()
{
  sliot_wifi_status_e status = SLIOT_WIFI_STATUS_MAX;
  switch(WiFi.status())
  {
    case WL_CONNECTED:
      status = SLIOT_WIFI_STATUS_CONNECTED;
      break;
    default:
      break;
  }
  return status;
}
