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

void ASSM_CALLBACK::error( uint8_t command ) {
} // method

void ASSM_CALLBACK::idle( uint8_t command ) {
} // method

void ASSM_CALLBACK::running( uint8_t command ) {
} // method
