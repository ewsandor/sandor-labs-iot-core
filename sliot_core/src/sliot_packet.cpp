#include "../inc/sliot_packet.hpp"

void sliot_packet_c::init()
{
  memset(&this->source,      0, sizeof(sliot_packet_node_u));
  memset(&this->destination, 0, sizeof(sliot_packet_node_u));
  memset(&this->data,        0, sizeof(sliot_packet_data_s));
}

sliot_packet_c::sliot_packet_c(sliot_packet_node_u source, sliot_packet_node_u destination)
{
  init();
  this->source      = source;
  this->destination = destination;
}
sliot_packet_c::sliot_packet_c(sliot_packet_node_u source, sliot_packet_node_u destination, sliot_packet_data_s data)
{
  init();
  this->source      = source;
  this->destination = destination;
  this->data = data;
}
sliot_packet_c::sliot_packet_c(sliot_packet_node_u source, sliot_packet_node_u destination, sliot_byte_t *data_ptr, sliot_size_t num_bytes)
{
  init();
  this->source         = source;
  this->destination    = destination;
  this->data.data_ptr  = data_ptr;
  this->data.num_bytes = num_bytes;
}