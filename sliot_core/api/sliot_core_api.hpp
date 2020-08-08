#ifndef _SLIOT_CORE_API_H_
#define _SLIOT_CORE_API_H_

#include "Arduino.h"
#include "sliot_types.hpp"
//Include per project config
#include "../config/sliot_core_config.hpp"

//Initialize Sandor Laboratories IoT Core
sliot_result_e sliot_core_init ();

#endif //_SLIOT_CORE_API_H_
