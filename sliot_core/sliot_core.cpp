#include "sliot_core.h"

boolean sliot_core_init
(
  void
)
{
  boolean ret_val = true;

  #ifdef SLIOT_SERIAL_ENABLED
  sliot_serial_init();
  #endif

  return ret_val;
}
