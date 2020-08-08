#ifndef _SLIOT_WIFI_WIFI_SHIELD_H_
#define _SLIOT_WIFI_WIFI_SHIELD_H_

#include "../inc/sliot_wifi.hpp"

class sliot_wifi_wifi_shield_c : public sliot_wifi_c 
{
  private:

  public:
  // Initial sliot_wifi_wifi_shield communication
  static sliot_wifi_c *sliot_wifi_wifi_shield_init();
  /* Connect to WiFi */
  sliot_result_e connect();
  sliot_result_e connect(sliot_time_ms_t timeout);
  /* Disconnect from WiFi */
  sliot_result_e disconnect();
  /* Check current Wi-Fi status */
  sliot_wifi_status_e wifi_status();
};

#endif //_SLIOT_WIFI_WIFI_SHIELD_H_
