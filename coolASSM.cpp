/**
 * coolASSM - cool arduino serial state machine
 *
 * Christian
 * graetz23@gmail.com
 * created 20190511
 * updated 20200329
 * version 0.5
 */
#include <Arduino.h>
#include <Servo.h>

#include "./coolASSM.h" // base class header file

ASSM::ASSM( void ) {
  _state = ASSM_STATE_IDLE; // initial STATE is IDLE due to not reacting
  _command = ASSM_CMD_NULL; // set COMMAND to NO (NULL) COMMAND
  _helper = new ASSM_HELPER( ); // use internal helper ..
} // method

ASSM::~ASSM( void ) {
  delete _helper;
} // method

void ASSM::setup( void ) {
  Serial.begin( SERIAL_BAUD ); // set up serial
  delay(10); // 10 ms
} // method

ASSM_HELPER* ASSM::get_ASSM_HELPER( void ) {
  return _helper; // if one needs the helper outside cool ASSM ..
} // method

void ASSM::display( String s ) {
  const char* cstr = s.c_str();
  String sstate = _helper->state_to_String( _state );
  const char* cstate = sstate.c_str();
  String scmmnd = _helper->command_to_String( _command );
  const char* ccmmnd = scmmnd.c_str();
  // you can drive some display here
  // e.g. an liquid crystal 20x2 lcd
} // method

void ASSM::welcome( ) {
  // print some welcome message to display here
  delay(250); // 500 ms
} // method

void ASSM::ready( ) {
  // prin some ready messsafe to display here
  delay(750); // 500 ms
} // method

void ASSM::writeData( String data ) {
  // char c = command + 10 +'0';
  // char str[ 10 ];
  // sprintf( str, "%d", command );
  const char* cstr = data.c_str( );
  Serial.write( cstr );
} // method

void ASSM::writeCommand( uint8_t command ) {
  writeCommand( _helper->command_to_String( command ) );
} // method

void ASSM::writeCommand( String command ) {
  String str = _helper->mark_as_Command( command );
  const char* cstr = str.c_str( );
  Serial.write( cstr );
} // method


void ASSM::writeState( uint8_t state ) {
 writeState( _helper->state_to_String( state ) );
} // method

void ASSM::writeState( String state ) {
  String str = _helper->mark_as_Command( state );
  const char* cstr = str.c_str( );
  Serial.write( cstr );
} // method


// read the received State from serial
uint8_t ASSM::readCommand( ) {
  const byte numChars = 32;
  char receivedChars[numChars]; // an array to store the received data
  static byte ndx = 0;
  static boolean isReceiving = false;
  char rc;
  uint8_t cmd = ASSM_CMD_NULL;
  if( Serial.available( ) > 0 ) {
    while( Serial.available( ) > 0 ) {
      rc = Serial.read( );
      if( isReceiving == true ) {
         if( rc != _markerFoot ) {
             receivedChars[ ndx ] = rc;
             ndx++;
             if( ndx >= numChars ) {
                 ndx = numChars - 1;
             } // if
         } else {
             receivedChars[ ndx ] = '\0'; // terminate the string
             isReceiving = false;
             ndx = 0;
         } // if
      } // if
      else if( rc == _markerHead )
      { // found a beginning
         isReceiving = true;
      } // if
    } // loop
    cmd = a2i( receivedChars );
  } // if
  return cmd;
} // method

/**
 * running the recevied command
 */
void ASSM::loop( ) {

  uint8_t command = readCommand( ); // read and filter a command from serial

  if( ASSM_DEBUG_SHOW_COMMAND ) {
    display( "COMMAND ->" );
    delay( ASSM_DEBUG_DISPLAY_BLANK );
    display( _helper->command_to_String( command ) );
    delay( ASSM_DEBUG_DISPLAY_SHOW );
    display( "" );
    delay( ASSM_DEBUG_DISPLAY_BLANK );
    // TODO tell about state machine
  } // if

  uint8_t command_internal = command;

  bool isProcessingInternally = true;

  while( isProcessingInternally ) {

    uint8_t state = process_command( command_internal );

    if( ASSM_DEBUG_SHOW_STATE ) {
      display( "STATE ->" );
      delay( ASSM_DEBUG_DISPLAY_BLANK );
      display( _helper->state_to_String( state ) );
      delay( ASSM_DEBUG_DISPLAY_SHOW );
      display( "" );
      delay( ASSM_DEBUG_DISPLAY_BLANK );
      // TODO tell about state machine
    } // if

    command_internal = process_state( state );

    if( command_internal == ASSM_CMD_NULL ) {
      isProcessingInternally = false;
    } // if

    if( ASSM_DEBUG ) {
      display( "DEBUG" );
      delay( ASSM_DEBUG_DISPLAY_SHOW );
      display( "" );
      delay( ASSM_DEBUG_DISPLAY_BLANK );
      // TODO tell about state machine
    } // if

  } // loop

} // method

uint8_t ASSM::process_command( uint8_t command ) {

  _command = command; // copy to internal member variable

  uint8_t state = ASSM_STATE_ERROR; // initial state is always last state

  uint8_t debug_command;

  switch( _command ) {
    // process the COMMAND SNA - State Not Available; we are in ERROR state ..
    case ASSM_CMD_SNA:
      state = ASSM_STATE_ERROR;
      if( ASSM_DEBUG_SHOW_COMMAND_INTERNAL )
        debug_command = ASSM_CMD_SNA;
      break;
    // process the COMMAND PING
    case ASSM_CMD_PING:
      if( _state == ASSM_STATE_ERROR ) {
        state = ASSM_STATE_IDLE;
      } else {
        state = _state;
      }// if
      writeCommand( ASSM_CMD_PONG ); // ALWAYS answer a PING with a PONG
      if( ASSM_DEBUG_SHOW_COMMAND_INTERNAL )
        debug_command = ASSM_CMD_PING;
    break;
    // process the COMMAND PONG
    case ASSM_CMD_PONG:
      if( _state == ASSM_STATE_ERROR ) {
        state = ASSM_STATE_IDLE;
      } else {
        state = _state;
      }// if
      writeCommand( ASSM_CMD_PING ); // ALWAYS answer a PONG with a PING
      if( ASSM_DEBUG_SHOW_COMMAND_INTERNAL )
        debug_command = ASSM_CMD_PONG;
    break;
    // process the COMMAND ACKNOWLEDGE; not really something to do here ..
    case ASSM_CMD_AKNWLDG:
      state = _state;
      if( ASSM_DEBUG_SHOW_COMMAND_INTERNAL )
        debug_command = ASSM_CMD_AKNWLDG;
    break;
    // process the COMMAND RUN; now some working task should be processed
    case ASSM_CMD_RUN:
      if(_state != ASSM_STATE_ERROR ) {
        state = ASSM_STATE_RUNNING; // only if we are not in ERROR ..
        writeCommand( ASSM_CMD_AKNWLDG ); // answer with a ACKNOWLEDGE
      } else {
        state = _state;
      }// if
      if( ASSM_DEBUG_SHOW_COMMAND_INTERNAL )
        debug_command = ASSM_CMD_CONNECT;
    break;
    // process the COMMAND STOP; leave some working task and return to IDLE
    case ASSM_CMD_STOP:
      if(_state == ASSM_STATE_RUNNING ) {
        state = ASSM_STATE_IDLE;
        writeCommand( ASSM_CMD_AKNWLDG ); // answer with a ACKNOWLEDGE
      } else {
        state = _state;
      }// if
      if( ASSM_DEBUG_SHOW_COMMAND_INTERNAL )
        debug_command = ASSM_CMD_DISCNCT;
    break;
    // process the COMMAND WAIT; may be stop some processing task ..
    case ASSM_CMD_WAIT:
      state = _state;
      if( ASSM_DEBUG_SHOW_COMMAND_INTERNAL )
        debug_command = ASSM_CMD_WAIT;
    break;
    // process the COMMAND EVENT; may be do something while processing ..
    case ASSM_CMD_EVENT:
      state = _state;
      if( ASSM_DEBUG_SHOW_COMMAND_INTERNAL )
        debug_command = ASSM_CMD_EVENT;
    break;
    // process the COMMAND STATUS
    case ASSM_CMD_STATUS:
      state = _state;
      writeState( _state ); // ALWAYS tell about the current STATE
      if( ASSM_DEBUG_SHOW_COMMAND_INTERNAL )
        debug_command = ASSM_CMD_STATUS;
    break;
    // process the COMMAND CONNECT
    case ASSM_CMD_CONNECT:
      // may be one want to CONNECT and DISCONNECT while IDLE / RUNNING ..
      state = _state;
      if( ASSM_DEBUG_SHOW_COMMAND_INTERNAL )
        debug_command = ASSM_CMD_CONNECT;
    break;
    // process the COMMAND DISCNCT
    case ASSM_CMD_DISCNCT:
      // may be one want to CONNECT and DISCONNECT while IDLE / RUNNING ..
      state = _state;
      if( ASSM_DEBUG_SHOW_COMMAND_INTERNAL )
        debug_command = ASSM_CMD_DISCNCT;
    break;
    // process no (NULL) or an unknown COMMAND
    default:
      state = _state; // next STATE is the same as last STATE ..
      if( ASSM_DEBUG_SHOW_COMMAND_INTERNAL ) {
        display( "CMND DEFAULT" );
        delay(ASSM_DEBUG_DISPLAY_SHOW);
        display( "" );
        delay(ASSM_DEBUG_DISPLAY_BLANK);
      } // if
    break;
  } // switch
  // display some debugging message to display
  if( ASSM_DEBUG_SHOW_COMMAND_INTERNAL ) {
    display( _helper->command_to_String( debug_command ) );
    delay(ASSM_DEBUG_DISPLAY_SHOW);
    display( "" );
    delay(ASSM_DEBUG_DISPLAY_BLANK);
  } // if
  return state;
} // method

uint8_t ASSM::process_state( uint8_t state ) {

  _state = state; // copy to internal member variable

  uint8_t next_command = ASSM_CMD_NULL; // return no command

  uint8_t debug_state;

  switch( _state ) {
    case ASSM_STATE_ERROR: // SNA - State Not Available
      next_command = ASSM_CMD_NULL;
      if( ASSM_DEBUG_SHOW_STATE_INTERNAL )
        debug_state = ASSM_STATE_ERROR;
      break;
    case ASSM_STATE_IDLE: // IDLE around, and around, and arountthe world
      next_command = ASSM_CMD_NULL;
      if( ASSM_DEBUG_SHOW_STATE_INTERNAL )
        debug_state = ASSM_STATE_IDLE;
    break;
    case ASSM_STATE_RUNNING: // RUNNING

      if( ASSM_DEBUG_SHOW_STATE_INTERNAL )
        debug_state = ASSM_STATE_RUNNING;
      next_command = process( _command ); // use internal member here
      // next_command = ASSM_CMD_NULL;
    break;
    default:
      next_command = ASSM_CMD_NULL;
      if( ASSM_DEBUG_SHOW_STATE_INTERNAL ) {
        display( "def_state" );
        delay(ASSM_DEBUG_DISPLAY_SHOW);
        display( "" );
        delay(ASSM_DEBUG_DISPLAY_BLANK);
      } // if
    break;
  } // switch
  if( ASSM_DEBUG_SHOW_STATE_INTERNAL ) {
    display( _helper->state_to_String( debug_state ) );
    delay(ASSM_DEBUG_DISPLAY_SHOW);
    display( "" );
    delay(ASSM_DEBUG_DISPLAY_BLANK);
  } // if
  return next_command;
} // method

int ASSM::a2i(const char *s)
{
  int sign=1;
  if(*s == '-'){
    sign = -1;
    s++;
  }
  int num=0;
  while(*s){
    num=((*s)-'0')+num*10;
    s++;
  }
  return num*sign;
} // method

uint8_t ASSM::process( uint8_t command ) {

  uint8_t next_command = ASSM_CMD_NULL;

  if( ASSM_DEBUG_SHOW_RUNNING_INTERNAL ) {
    display( "RUNNING ->" );
    delay(ASSM_DEBUG_DISPLAY_SHOW);
    display( _helper->state_to_String( _state ) );
    delay(ASSM_DEBUG_DISPLAY_SHOW);
    display( _helper->command_to_String( _command ) );
    delay(ASSM_DEBUG_DISPLAY_SHOW);
    display( "" );
    delay(ASSM_DEBUG_DISPLAY_BLANK);
  } // if

  // TODO implement your running here

  if( command == ASSM_CMD_EVENT ) {

    int cnt = 0;
    while( cnt < 3 ) {

      writeCommand( ASSM_CMD_WAIT );

      cnt++;
      delay( 1000 );
    } // loop

    writeCommand( "DATA" );

    writeData( "1;2;3;4;5;6;7;8;9;0;" );

    writeCommand( "/DATA" );

    writeCommand( ASSM_CMD_STOP );

  } // if

  return next_command;

} // method
