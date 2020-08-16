#ifndef _SLIOT_PACKET_HPP_
#define _SLIOT_PACKET_HPP_

#include "sliot_core_internal.hpp"
#include "../api/sliot_internet_types.hpp"

typedef enum {
  SLIOT_PACKET_DEST_SLIOT_DEVICE,
  SLIOT_PACKET_DEST_IP
} sliot_packet_node_type_e;

typedef struct {
  sliot_packet_node_type_e dest_type;
} sliot_packet_node_hdr_s;

typedef uint32_t sliot_packet_sliot_device_id_t;
typedef uint32_t sliot_packet_sliot_device_port_t;
typedef struct {
  sliot_packet_node_hdr_s          dest_hdr;
  sliot_packet_sliot_device_id_t   device_id;
  sliot_packet_sliot_device_port_t device_port;
} sliot_packet_node_sliot_device_s;

typedef struct {
  sliot_packet_node_hdr_s        dest_hdr;
  sliot_ip_address_c             ip;
  sliot_ip_port_t                port;
} sliot_packet_node_ip_s;

typedef union sliot_packet_node_u {
  sliot_packet_node_hdr_s          dest_hdr;
  sliot_packet_node_sliot_device_s sliot_device;
  sliot_packet_node_ip_s           ip;
  sliot_packet_node_u() {};
};

typedef struct {
 sliot_byte_t *data_ptr;
 sliot_size_t  num_bytes;
} sliot_packet_data_s;

class sliot_packet_c {
  private:
  sliot_packet_node_u source;
  sliot_packet_node_u destination;
  sliot_packet_data_s data;
  void init();

  public:
  sliot_packet_c(sliot_packet_node_u source, sliot_packet_node_u destination);
  sliot_packet_c(sliot_packet_node_u source, sliot_packet_node_u destination, sliot_packet_data_s data);
  sliot_packet_c(sliot_packet_node_u source, sliot_packet_node_u destination, sliot_byte_t *data_ptr, sliot_size_t num_bytes);
  sliot_packet_node_u get_source()      {return source;}
  sliot_packet_node_u get_destination() {return destination;}
  sliot_packet_data_s get_data()        {return data;}
};

#endif //_SLIOT_PACKET_HPP_