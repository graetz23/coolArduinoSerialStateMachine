/**
 * coolASSM - cool arduino serial state machine
 *
 * Christian
 * graetz23@gmail.com
 * created 20190511
 * updated 20200330
 * version 0.5
 */
#ifndef __ARDUINO_COOLASSM_CALLBACKS_H__
#define __ARDUINO_COOLASSM_CALLBACKS_H__

#include "./coolASSM_commands.h" //

class ASSM_CALLBACK {

public:

  /*!
   * \brief Constructor
   */
  ASSM_CALLBACK( void );

  /*!
   * \brief Destructor
   */
  virtual ~ASSM_CALLBACK( void );

  /*!
   * \brief cyclic called when coolASSM is in ERROR state - overload method
   */
  virtual uint8_t error( uint8_t command );

  /*!
   * \brief cyclic called when coolASSM is in IDLE state - overload method
   */
  virtual uint8_t idle( uint8_t command );

  /*!
   * \brief cyclic called when coolASSM is in RUNNING state - overload method
   */
  virtual uint8_t running( uint8_t command );

}; // class

#endif
