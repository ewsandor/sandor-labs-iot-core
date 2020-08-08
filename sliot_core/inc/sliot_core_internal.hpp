/* 
 *  Internal common definitions and functions for Sandor Laboratories IoT Core
 */

#ifndef _SLIOT_CORE_INTERNAL_HPP_
#define _SLIOT_CORE_INTERNAL_HPP_

//Include per project config
#include "../config/sliot_core_config.hpp"
//Include API Definitions
#include "../api/sliot_core_api.hpp"

class sliot_core_logger_c : public Print
{ 
  private:
  Print *logging_device;

  public:
  sliot_core_logger_c();

  size_t write(uint8_t);
  size_t write(const uint8_t *buffer, size_t size);
  int    availableForWrite();
  void   flush();
};

extern sliot_core_logger_c sliot_core_logger;

#endif //_SLIOT_CORE_INTERNAL_HPP_