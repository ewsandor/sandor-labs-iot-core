#ifndef _SLIOT_INTERNET_TYPES_
#define _SLIOT_INTERNET_TYPES_

typedef uint32_t sliot_ip_port_t;
typedef uint32_t sliot_subnet_mask_t;
typedef uint8_t  sliot_subnet_cidr_t;

#define SLIOT_IP_ADDRESS_NUM_OCTETS 4
typedef uint32_t sliot_ip_address_raw_t;
typedef uint8_t  sliot_ip_address_octet_t;

class sliot_ip_address_c
{
  private:
  sliot_ip_address_raw_t addr;

  void               init();
  /* Returns octet of ip address in format 0.1.2.3 */
  sliot_ip_address_octet_t get_octet(uint8_t octet_num);

  public:
  sliot_ip_address_c();
  sliot_ip_address_c(sliot_ip_address_c *ip_address);
  sliot_ip_address_c(sliot_ip_address_raw_t raw_ip_address);

  String string();
};

typedef enum
{
  SLIOT_IP_MODE_DHCP,
  SLIOT_IP_MODE_STATIC,
  SLIOT_IP_MODE_MAX
} sliot_ip_mode_e;
typedef struct
{
  sliot_ip_address_c  addr;
  sliot_subnet_cidr_t subnet_cidr;
  sliot_ip_address_c  gateway;
  sliot_ip_address_c  dns;
} sliot_ip_config;
#endif //_SLIOT_INTERNET_TYPES_