/**
 * coolASSM - cool arduino serial state machine
 *
 * Christian
 * graetz23@gmail.com
 * created 20190511
 * updated 20200330
 * version 0.5
 */
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "./coolASSM.h" // cool arduino serial state machine
ASSM assm; // static object

#define LED 13 // arduino's built-in LED

void setup( ) {

  pinMode(LED, OUTPUT); // arduino's built-in LED

  assm.setup( ); // start serial console, and etc.
  assm.welcome( ); // display some welcome message
  assm.ready( ); // display some welcome message

} // method

void loop( ) {

  digitalWrite(LED, HIGH); // sets the digital pin LED on
  // delay(10);            // waits for a moment in ECU time

  assm.loop( ); // processing loop of ASSM; it's not a while one ..

  digitalWrite(LED, LOW);  // sets the digital pin LED off

  delay(100);

} // method
