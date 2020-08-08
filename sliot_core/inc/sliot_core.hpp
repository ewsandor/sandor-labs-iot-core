#ifndef _SLIOT_CORE_H_
#define _SLIOT_CORE_H_

//Include IoT Core Internal Common Definitions
#include "sliot_core_internal.hpp"

#ifdef SLIOT_SERIAL_ENABLED
#include "sliot_serial.hpp"
#endif

//MQTT if enabled
#ifdef SLIOT_MQTT_ENABLED
#include "sliot_mqtt.hpp"
#endif

//WIFI Sheild WiFi if enabled
#ifdef SLIOT_WIFI_WIFI_SHIELD_ENABLED
#include "sliot_wifi_wifi_shield.hpp"
#endif

#endif //_SLIOT_CORE_H_
