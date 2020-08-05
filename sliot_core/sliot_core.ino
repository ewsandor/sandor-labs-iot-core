/* 
 *  Basic program to test Sandor Labortories IoT Core
 */

#include "sliot_core.h"

uint32_t sliot_core_test_counter;

void setup
(
)
{
  sliot_core_test_counter = 0;
  
  sliot_core_init();
}

void loop() {

  sliot_core_test_counter++;

}
