#include "../inc/sliot_serial.hpp"

// Initial serial communication
boolean sliot_serial_init
(
  void
)
{
  boolean ret_val = true;

  #ifdef SLIOT_SERIAL_ENABLED
  Serial.begin(SLIOT_SERIAL_BAUD_RATE);
  delay(10);
  #endif

  sliot_core_logger.println("Initialized Serial");

  return ret_val;
}
