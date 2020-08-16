#include "../inc/sliot_core_internal.hpp"

sliot_device_id_t sliot_get_device_id()
{
  return SLIOT_DEVICE_ID;
}

sliot_core_logger_c::sliot_core_logger_c()
{
  logging_device = &Serial;
}

size_t sliot_core_logger_c::write(uint8_t var)
{
  size_t ret_val = 0;

  #ifdef SLIOT_CORE_VERBOSE_LOGGING_ENABLED
  if(logging_device)
  {
    ret_val = logging_device->write(var);
  }
  #endif

  return ret_val;
}
size_t sliot_core_logger_c::write(const uint8_t *buffer, size_t size)
{
  size_t ret_val = 0;

  #ifdef SLIOT_CORE_VERBOSE_LOGGING_ENABLED
  if(logging_device)
  {
    ret_val = logging_device->write(buffer, size);
  }
  #endif

  return ret_val;
}
#if 0
int sliot_core_logger_c::availableForWrite()
{
  int ret_val = 0;

  #ifdef SLIOT_CORE_VERBOSE_LOGGING_ENABLED
  if(logging_device)
  {
    ret_val = logging_device->availableForWrite();
  }
  #endif

  return ret_val;
}
void sliot_core_logger_c::flush()
{
  #ifdef SLIOT_CORE_VERBOSE_LOGGING_ENABLED
  if(logging_device)
  {
    logging_device->flush();
  }
  #endif

}
#endif