/**
 * coolASSM - cool arduino serial state machine
 *
 * Christian
 * graetz23@gmail.com
 * created 20190511
 * updated 20200330
 * version 0.5
 */
#ifndef __ARDUINO_COOLASSM_H__
#define __ARDUINO_COOLASSM_H__

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

// #include "./coolASSM_commands.h" // the ASSM commands and converts ..
#include "./coolASSM_callbacks.h" // the ASSM callback methods ..

#define SERIAL_BAUD                         9600  // Baudrate
// #define SERIAL_BAUD                      19200  // Baudrate
// #define SERIAL_BAUD                      115200  // Baudrate

#define ASSM_DEBUG                          true
#define ASSM_DEBUG_SHOW_COMMAND             false
#define ASSM_DEBUG_SHOW_COMMAND_INTERNAL    false
#define ASSM_DEBUG_SHOW_STATE               false
#define ASSM_DEBUG_SHOW_STATE_INTERNAL      false
#define ASSM_DEBUG_SHOW_RUNNING_INTERNAL    false
#define ASSM_DEBUG_DISPLAY_SHOW             200
#define ASSM_DEBUG_DISPLAY_BLANK            100

/*!
 * \brief The cool ASSM - the cool arduino serial state machine
 */
class ASSM {

private:

  uint8_t _command; // current command of cool ASSM

  uint8_t _state; // current state of cool ASSM

  ASSM_HELPER* _helper; // COMMAND and STATE processing helper

  ASSM_CALLBACK* _callback; // base pointer to your overloaded class

public:

  /*!
   * \brief Constructor
   */
  ASSM( void );

  /*!
   * \brief Destructor
   */
  ~ASSM( void );

  /*!
   * \brief Returns the HELPER for using it outside cool ASSM ..
   * \return the pointer to the internal, private STATE / COMMAND helper
   */
  ASSM_HELPER* get_ASSM_HELPER( void );

  /*!
   * \brief Read one byte from the serial and cast it to an Order
   * \return the order received
   */
  uint8_t readCommand( );

  /*!
   * \brief Send a command to the CLIENT
   * \param The COMMAND number
   */
  void writeCommand( uint8_t command );

  /*!
   * \brief Send a command to the CLIENT
   * \param The COMMAND as some string
   */
  void writeCommand( String command );

  /*!
  * \brief Send a state to the CLIENT
  * \param The STATE number
   */
  void writeState( uint8_t state );

  /*!
  * \brief Send a state to the CLIENT
  * \param The STATE number as some string
   */
  void writeState( String state );

  /*!
   * \brief Send some data to CLIENT
   * \param the bare data ..
   */
  void writeData( String command );

  /*!
   * \brief Display some string including current STATE and COMMAND
   */
  void display( String s );

  /*!
   * \brief Connect the serial and send ping to client
   */
  void setup( );

  /*!
   * \brief Display a welcome message for showing interactivity
   */
  void welcome( );

  /*!
   * \brief Display a ready message for showing interactivity
   */
  void ready( );

  /*!
   * \brief Connect the serial and send ping to client
   */
  void loop( );

  /*!
   * \brief Handing the RECEIVED or NEXT COMMAND and CURRENT STATE
   * \param receives a COMMAND and a STATE changes to the NEXT STATE
   * \return the NEXT STATE
   */
  uint8_t process_command( uint8_t command );

  /*!
  * \brief Handing the CURRENT COMMAND and NEXT STATE
   * \param receives a STATE and a COMMAND and MAY change to the NEXT COMMAND
   * \return may return the NEXT COMMAND, INSTEAD of RECEIVED COMMAND
   */
  uint8_t process_state( uint8_t state );

  /*!
   * \brief Listen the serial and decode the message received
   */
  virtual uint8_t process( uint8_t command );

private: // some stuff that's not so interesting

  const char _markerHead = '<';
  const char _markerFoot = '>';
  const String _markerCommand = "CMD_";

  // Adafruit_SSD1306* _display; // running OLEDisplay for msgs and dbgng
  // U8GLIB_SH1106_128X64* _u8g;	// I2C / TWI

  /*!
   * \brief converts a char array into an integer
   * \param the cahr array keeping a one or more digit number
   * \return the correspoding integer
   */
  int a2i( const char *s );

}; // class

#endif
