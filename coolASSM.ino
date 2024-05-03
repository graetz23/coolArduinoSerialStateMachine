/**
 * coolASSM - cool arduino serial state machine
 *
 * Christian
 * graetz23@gmail.com
 * created 20190511
 * version 20200402
 *
 * MIT License
 *
 * Copyright (c) 2019-2024 coolASSM Christian (graetz23@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "./coolASSM.h" // cool arduino serial state machine
ASSM assm; // static object

void setup( ) {

  assm.setup( ); // start serial console, and etc.
  // not necessary but helpful ..
  assm.welcome( ); // display some welcome message
  assm.ready( ); // display some alive message

} // method

void loop( ) {


  assm.loop( ); // processing loop of ASSM; it's not a while one ..

  delay(100);

} // method
