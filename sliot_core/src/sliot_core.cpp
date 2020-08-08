#include "../inc/sliot_core.hpp"

sliot_core_logger_c  sliot_core_logger;
sliot_wifi_c        *sliot_wifi = NULL;

sliot_result_e sliot_core_init()
{
  sliot_result_e ret_val = SLIOT_RESULT_SUCCESS;

  #ifdef SLIOT_CORE_VERBOSE_LOGGING_ENABLED
  sliot_core_logger = *(new sliot_core_logger_c());
  #endif 

  #ifdef SLIOT_SERIAL_ENABLED
  sliot_serial_init();
  #endif

  #ifdef SLIOT_WIFI_WIFI_SHIELD_ENABLED
    sliot_wifi = sliot_wifi_wifi_shield_c::sliot_wifi_wifi_shield_init();
  #endif

  return ret_val;
}
