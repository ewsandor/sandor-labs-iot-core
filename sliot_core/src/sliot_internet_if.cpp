#include "../inc/sliot_core_internal.hpp"
#include "../api/sliot_internet_types.hpp"
#include "../inc/sliot_internet_if.hpp"

void sliot_ip_address_c::init()
{
  addr = 0;
}

sliot_ip_address_c::sliot_ip_address_c()
{
  init();
}
sliot_ip_address_c::sliot_ip_address_c(sliot_ip_address_c *ip_address)
{
  init();
  addr = ip_address->addr;
}
sliot_ip_address_c::sliot_ip_address_c(sliot_ip_address_raw_t raw_ip_address)
{
  init();
  addr = raw_ip_address;
}

sliot_ip_address_octet_t sliot_ip_address_c::get_octet(uint8_t octet_num)
{
  sliot_ip_address_octet_t octet = 0;

  if(octet_num < SLIOT_IP_ADDRESS_NUM_OCTETS)
  {
    octet = ( addr >> (8 * ((SLIOT_IP_ADDRESS_NUM_OCTETS-1) - octet_num)) ) & 0xFF;
  }

  return octet;
}

String sliot_ip_address_c::string()
{
  uint8_t            i;
  sliot_ip_address_octet_t octet;
  String             ip_str = "";

  for(i = 0; i < SLIOT_IP_ADDRESS_NUM_OCTETS; i++)
  {
    if(i != 0)
    {
      ip_str += ".";
    }
    ip_str += String(get_octet(i));
  }

  return ip_str;
}



void sliot_internet_if::init()
{
  ip_mode = SLIOT_IP_MODE_DHCP;
  memset(&static_ip_config, 0, sizeof(sliot_ip_config));
}
sliot_internet_if::sliot_internet_if()
{
  init();
}