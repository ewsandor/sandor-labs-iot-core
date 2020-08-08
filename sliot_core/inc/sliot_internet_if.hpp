#ifndef _SLIOT_INTERNET_IF_HPP_
#define _SLIOT_INTERNET_IF_HPP_

#include "sliot_core_internal.hpp"
#include "../api/sliot_internet_types.hpp"

class sliot_internet_if
{
  private:
  sliot_ip_mode_e ip_mode;
  sliot_ip_config static_ip_config;
  
  void init();

  public:
  sliot_internet_if();
  virtual sliot_ip_address_c  get_ip_addr() = 0;
  virtual sliot_ip_address_c  get_subnet() = 0;
  virtual sliot_subnet_cidr_t get_subnet_cidr() = 0;
  virtual sliot_ip_address_c  get_gateway_addr() = 0;
  virtual sliot_ip_address_c  dns_lookup(char * hostname) = 0;
};

#endif //_SLIOT_INTERNET_IF_HPP_