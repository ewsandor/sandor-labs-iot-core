#ifndef _SLIOT_TYPES_HPP_
#define _SLIOT_TYPES_HPP_

typedef enum
{
  /* Action completed successfully */
  SLIOT_RESULT_SUCCESS,
  /* Action completed unsuccessfully */
  SLIOT_RESULT_FAILURE,
  /* Action is asyncronous and is still in progress */
  SLIOT_RESULT_ASYNC,
  /* Invalid result */
  SLIOT_RESULT_MAX
} sliot_result_e;

//Standard type for time in ms (inline with Arduino millis() API)
typedef unsigned long sliot_time_ms_t;

#endif //_SLIOT_TYPES_HPP_