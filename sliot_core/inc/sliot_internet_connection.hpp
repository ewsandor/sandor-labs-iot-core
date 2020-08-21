#ifndef _SLIOT_INTERNET_CONNECTION_HPP_
#define _SLIOT_INTERNET_CONNECTION_HPP_

#include "sliot_core_internal.hpp"
#include "../api/sliot_internet_types.hpp"
#include "../inc/sliot_packet.hpp"

typedef enum {
  SLIOT_INTERNET_CONNECTION_STATUS_DISCONNECTED,
  SLIOT_INTERNET_CONNECTION_STATUS_CONNECTED,
} sliot_internet_connection_status_e;

class sliot_internet_connection_c {
  private:
  sliot_internet_if_c *interface;

  public:
  virtual sliot_internet_connection_status_e get_status();
  virtual sliot_result_e connect();
  virtual sliot_result_e disconnect();

  boolean is_connected() { return (SLIOT_INTERNET_CONNECTION_STATUS_CONNECTED==get_status()); }

  /* Write data to internet connection, returns number of bytes written */
  virtual sliot_size_t write(sliot_packet_data_s data);
  /* Read data from internet connection up to size of 'buffer'. Assumes 'buffer' is initialized */
  virtual sliot_size_t read(sliot_packet_data_s buffer);
  /* Flush all data written to interface in blocking call */
  virtual sliot_result_e flush();
};

#endif //_SLIOT_INTERNET_CONNECTION_HPP_