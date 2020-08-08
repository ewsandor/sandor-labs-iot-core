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

sliot_ip_address_c sliot_wifi_wifi_shield_c::get_ip_addr()
{
  sliot_ip_address_raw_t addr = SLIOT_BIT_OP_REVERSE_OCTET_32B(WiFi.localIP());

  return *(new sliot_ip_address_c(addr));
}
sliot_ip_address_c sliot_wifi_wifi_shield_c::get_subnet()
{
  sliot_ip_address_raw_t  addr = SLIOT_BIT_OP_REVERSE_OCTET_32B(WiFi.localIP());
  sliot_subnet_mask_t subnet_mask = SLIOT_BIT_OP_REVERSE_OCTET_32B(WiFi.subnetMask());

  return *(new sliot_ip_address_c((subnet_mask & addr)));

}
sliot_subnet_cidr_t sliot_wifi_wifi_shield_c::get_subnet_cidr()
{
  sliot_subnet_cidr_t cidr = 0;
  sliot_subnet_mask_t subnet_mask = SLIOT_BIT_OP_REVERSE_OCTET_32B(WiFi.subnetMask());

  while(subnet_mask & (1<<31))
  {
    cidr++;
    subnet_mask = subnet_mask << 1;
  }

  return cidr;
}
sliot_ip_address_c sliot_wifi_wifi_shield_c::get_gateway_addr()
{
  sliot_ip_address_raw_t addr = SLIOT_BIT_OP_REVERSE_OCTET_32B(WiFi.gatewayIP());

  return *(new sliot_ip_address_c(addr));
}
sliot_ip_address_c sliot_wifi_wifi_shield_c::dns_lookup(char * hostname)
{
  sliot_ip_address_c resolved_ip = new sliot_ip_address_c((sliot_ip_address_raw_t)0);
  IPAddress ip_lookup;
 
  if( 1 == WiFi.hostByName(hostname, ip_lookup) )
  {
    resolved_ip = new sliot_ip_address_c(SLIOT_BIT_OP_REVERSE_OCTET_32B(ip_lookup));
  }

  return resolved_ip;
}

/* Connect to WiFi */
sliot_result_e sliot_wifi_wifi_shield_c::connect()
{
  sliot_core_logger.println("Connecting to Wi-Fi AP '" + String(ssid) + "'");
  WiFi.begin(ssid, password);
  return SLIOT_RESULT_ASYNC;
}
sliot_result_e sliot_wifi_wifi_shield_c::connect(sliot_time_ms_t timeout)
{
  connect();
  return connect(SLIOT_WIFI_DEFAULT_TIMEOUT);
}
/* Disconnect from WiFi */
sliot_result_e sliot_wifi_wifi_shield_c::disconnect()
{
  WiFi.disconnect();

  return SLIOT_RESULT_ASYNC;
}
/* Check current Wi-Fi status */
sliot_wifi_status_e sliot_wifi_wifi_shield_c::wifi_status()
{
  sliot_wifi_status_e status = SLIOT_WIFI_STATUS_MAX;
  switch(WiFi.status())
  {
    case WL_IDLE_STATUS:
      status = SLIOT_WIFI_STATUS_IDLE;
      break;
    case WL_SCAN_COMPLETED:
      status = SLIOT_WIFI_STATUS_SCAN_COMPLETED;
      break;
    case WL_CONNECTED:
      status = SLIOT_WIFI_STATUS_CONNECTED;
      break;
    case WL_CONNECT_FAILED:
      status = SLIOT_WIFI_STATUS_CONNECTION_FAILED;
      break;
    case WL_CONNECTION_LOST:
      status = SLIOT_WIFI_STATUS_CONNECTION_LOST;
      break;
    case WL_DISCONNECTED:
      status = SLIOT_WIFI_STATUS_DISCONNECTED;
      break;
    case WL_NO_SSID_AVAIL:
      status = SLIOT_WIFI_STATUS_CONFIG_ERROR;
      break;
    default:
      break;
  }
  return status;
}
