#ifndef _SLIOT_CORE_CONFIG_H_
#define _SLIOT_CORE_CONFIG_H_

//Uncomment to enable verbose SLIOT CORE logging (SLIOT_SERIAL must also be enabled)
#define SLIOT_CORE_VERBOSE_LOGGING_ENABLED

//Uncomment to enable MQTT reporting, fully configured in sliot_mqtt_config.h
#define SLIOT_MQTT_ENABLED

//Uncomment to enable serial communicaion, fully configured in sliot_serial_config.h
#define SLIOT_SERIAL_ENABLED

//Uncoment to enable ESP32 Wifi, fully configured in sliot_wifi_config.h
#define SLIOT_WIFI_ESP32_ENABLED

/***************IMPLICIT ENABLES****************/
#ifdef SLIOT_CORE_VERBOSE_LOGGING_ENABLED
#ifndef SLIOT_SERIAL_ENABLED
#define SLIOT_SERIAL_ENABLED
#endif
#endif

#endif //_SLIOT_CORE_CONFIG_H_
