#ifndef _SLIOT_WIFI_HPP_
#define _SLIOT_WIFI_HPP_

#include "../inc/sliot_core_internal.hpp"
#include "../inc/sliot_internet_if.hpp"
#include "../config/sliot_wifi_config.hpp"

typedef enum
{
  SLIOT_WIFI_STATUS_IDLE,
  SLIOT_WIFI_STATUS_SCAN_COMPLETED,
  SLIOT_WIFI_STATUS_CONNECTED,
  SLIOT_WIFI_STATUS_CONNECTION_FAILED,
  SLIOT_WIFI_STATUS_CONNECTION_LOST,
  SLIOT_WIFI_STATUS_DISCONNECTED,
  SLIOT_WIFI_STATUS_CONFIG_ERROR,
  SLIOT_WIFI_STATUS_MAX
} sliot_wifi_status_e;

/* Default timeout for Wi-Fi operations */
#define SLIOT_WIFI_DEFAULT_TIMEOUT 5000

class sliot_wifi_c : public sliot_internet_if
{
  private:

  protected:
  char* ssid;
  char* password;

  public:
  sliot_wifi_c(void);

  /* Connect to WiFi */
  virtual sliot_result_e connect() = 0;
  /* Disconnect from WiFi */
  virtual sliot_result_e disconnect() = 0;
  /* Check current Wi-Fi status */
  virtual sliot_wifi_status_e wifi_status() = 0;
  /* Checks if Wi-Fi is currently connected */
  boolean connected() { return (SLIOT_WIFI_STATUS_CONNECTED == wifi_status()); }
  /* Checks if Wi-Fi is currently connected, retries within timeout if waiting for connection */
  sliot_result_e wait_for_connection(sliot_time_ms_t timeout);
};

#endif  //_SLIOT_WIFI_HPP_