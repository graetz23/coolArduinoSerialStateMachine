/**
 * coolASSM - cool arduino serial state machine
 *
 * Christian
 * graetz23@gmail.com
 * created 20190511
 * updated 20200330
 * version 0.5
 */

#include "./coolASSM_callbacks.h" // base class header file

ASSM_CALLBACK::ASSM_CALLBACK( void ) {
} // method

ASSM_CALLBACK::~ASSM_CALLBACK( void ) {
} // method

uint8_t ASSM_CALLBACK::error( uint8_t command ) {

  uint8_t next_command = ASSM_CMD_NULL; // do nothing else

  return next_command;

} // method

uint8_t ASSM_CALLBACK::idle( uint8_t command ) {

  uint8_t next_command = ASSM_CMD_NULL; // do nothing else

  return next_command;

} // method

uint8_t ASSM_CALLBACK::running( uint8_t command ) {

  uint8_t next_command = ASSM_CMD_NULL; // do nothing else

  return next_command;

} // method
