## cool Arduino Serial State Machine

A serial device driven state machine for _all_ arduino boards: **cool Arduino Serial State Machine (coolASSM)**.

### Introduction
This is a state machine for any arduino board that can be driven via sending commands over a serial console connection. The commands are common to the know one's as: PING, PONG, ACKN, RUN, WAIT, STOP, DONE. .., and so. Arduino is going to switch between states then, like: IDLE, MODE1, MODE2, .., MODE7, or even ERROR.

The project itself shall be extended by including own code or methods to several call back methods that are cylic driven by each different state.

### Building
For building the HEX file, the [arduino Makefile](https://github.com/sudar/Arduino-Makefile) is used. Clone or download / unzip this first to your system and configure the _Makefile_ by _your local path_ where you have cloned / unzipped. Change in  _Makefile_ to your arduino board and type: _make_ && _make upload_.

### Usage

After start up arduino has **nine STATES** available:

  - **ERROR** - arduino swtches from _all other states_, turn permanently (predefined) LED 13 on, and processes code of method: [**error()**](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  - **IDLE** - arduino switches from ERROR and _all other_ MODEs, and is idling, does a heartbeat blinking on LED 13, and processes code of method:  [**idle()**](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  - **MODE1** - arduino switches from IDLE and _all other_ MODEs, blinks rapidly, and processes code of method: [**runMODE1()**](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  - **MODE2** - arduino switches from IDLE and _all other_ MODEs, blinks rapidly, and processes code of method: [**runMODE2()**](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  - **MODE3** - arduino switches from IDLE and _all other_ MODEs, blinks rapidly, and processes code of method: [**runMODE3()**](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  - **MODE4** - arduino switches from IDLE and _all other_ MODEs, blinks rapidly, and processes code of method: [**runMODE4()**](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  - **MODE5** - arduino switches from IDLE and _all other_ MODEs, blinks rapidly, and processes code of method: [**runMODE5()**](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  - **MODE6** - arduino switches from IDLE and _all other_ MODEs, blinks rapidly, and processes code of method: [**runMODE6()**](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  - **MODE7** - arduino switches from IDLE and _all other_ MODEs, blinks rapidly, and processes code of method: [**runMODE7()**](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp).

To switch between theses STATEs, **COMMANDs** are sent to _arduino_. Theses COMMANDs **follow** an **XML like** syntax: **<CMD_ID>**.

The **COMMANDS** are:

  - **<0>** NULL - the null command is driven internally by arduino itself,
  - **<1>** SNA - State Not Available; sent arduino in ERROR state,
  - **<2>** PING - is replied by PONG and let arduino from ERROR to IDLE state,
  - **<3>** PONG - is replied by PING and let arduino from ERROR to IDLE state,
  - **<4>** AKNW - may be sent to arduino as an _notifier_; _optionally_,
  - **<5>** RUN - may be sent to arduino to _start_ any run MODE; _optionally_,
  - **<6>** WAIT - may arduino reply while it is processing data in a loop; _optionally_,
  - **<7>** EVENT - may be sent to arduino to request some data processing; _optionally_,
  - **<8>** DONE - may be sent as _notifier_ of finishing a data processing; _optionally_,
  - **<9>** STOP - is sent to arduino to return from _any_ run MODE to IDLE state,
  - **<10>** STATUS - is _always_ replied by the current state of arduino,
  - **<11>** run MODE1 - go from ANY state to this run MODE1, if not in ERROR state,
  - **<12>** run MODE2 - go from ANY state to this run MODE2, if not in ERROR state,
  - **<13>** run MODE3 - go from ANY state to this run MODE3, if not in ERROR state,
  - **<14>** run MODE4 - go from ANY state to this run MODE4, if not in ERROR state,
  - **<15>** run MODE5 - go from ANY state to this run MODE5, if not in ERROR state,
  - **<16>** run MODE6 - go from ANY state to this run MODE6, if not in ERROR state,
  - **<17>** run MODE7 - go from ANY state to this run MODE7, if not in ERROR state,
  - **<18>** CNCT - may be used to establish a connection; _optionally_,
  - **<19>** DCNT - may be used to release a connection; _optionally_.

Theses COMMANDs are **sent by their ID** to arduino**. However, **arduino will not reply by an ID**, arduino will reply **instead by an - regular - XML syntax**:  

  - For single replys, arduino uses _single / empty XML tags_ **<CMD_STR/>**,
  - For **data** replys, arduino may use _XML tags_ **<CMD_STR>data</CMD_STR>**; _optionally_.

All replies of arduino to your _client_ can be directly processed as [XML](https://en.wikipedia.org/wiki/XML); e.g. in [python](https://www.python.org/).

Examples look like:

  - Single / empty XML reply: a sent **<10>** to arduino, will be replied by its state, e.g. **\<IDLE\/\>**, **\<MODE1\/\>**, or **\<MODE2\/\>**
  - And ; _optional_ Content / data XML replys _may be implemented_ like:
    - **\<DATA\>** 1.2;3.4;5.6 **\<\/DATA\>**,
    - **\<INFO\>** sensor A0: is broke **\<\/INFO\> **,
    - **\<LOG\>** system voltage: 5.783 **\<\/LOG\> **,
    - **\<MSG\>** 0700 - good morning **\<\/MSG\> **.

Theses content / data based replies are held _fully independent_; those are not predefined. You can individually implemented such by _extending_ the class _ASSM_, **overloading** the **virtual methods** up to _all_ STATEs.

### Example

For an example, run [run_MODE7()](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp) is generating and sending some dummy data after processing. You can challenge arduino to process and responded - try:

  - flash / boot arduino out of the box,
  - start _arduino IDE_ and press: **SHFT + CTRL + m** to ope serial monitor,
    - be sure you have the _right port_ and the _correct baudrate_.
  - Type into the serial monitor:
    - **<17>**, to tell arduino to go to state of run **MODE7**:
      - arduino will start processing and reply with an: **<AKNW/>**.
    - **<7>**, to sent an **EVENT** to arduino:
      - arduino will reply with an: **<AKNW/>**, and start processing:
        - sents each second for three times a: **<WAIT/>** to you,
        - and afterwards the result: **<DATA>1.2;3.4;5.6</DATA>**.
    - **<9>**, to tell arduino to go back to state IDLE and blinks a heartbeat.

### Retrieving data \& individual commands

For retrieving data / content / logs / messages / .. /, you can use the following predefined methods:

  - **writeData_starting( String str )** - let arduino sent: **<str>**,  
  - **writeData( String str )** - let arduino sent: **str**,  
  - **writeData_stopping( String str )** - let arduino sent: **</str>**.  

For retrieving _individual_ COMMANDSs for adapting those on your client side, you can use the following predefiend method:

  - **writeCommand( Str str )** - let arduino sent: **<str/>**.

### Remarks
I use this project as a basis for sensor applications; e.g. see: [coolASSTCP](https://github.com/graetz23/coolArduinoSerialStateTCP).

On client side I use the _mirrow_ project: [**coolPythonSerialStateMachine (coolPSSM)**](https://github.com/graetz23/coolPythonSerialStateMachine) to implement the processing of retrieved data / content / logs / messages / .. /; the project is not finished yet.

Everything was coded using:

- [**atom**](https://atom.io/) editor,
- [**arduino Makefile**](https://github.com/sudar/Arduino-Makefile) for automated building,
- [**arduino IDE**](https://www.arduino.cc/en/main/software) for serial monitor,
- [**Gnome**](https://www.gnome.org/) as window manager,
- and [**debian**](https://www.debian.org/) GNU/Linux.

have fun :-)

## ChangeLog

**20200403**
  - extending the README.

**20200402**
  - add light up and flashing of arduino's built in LED on PIN 13:
    - in ERROR state it will light up permanently,
    - in IDLE state it will do a _heartbeat_:
      - with a duration of 60 bpm,
      - that let arduino do a general delay of a _full second_.
    - in _ALL_ run MODE states:
      - it will flash rapidly by 10 milliseconds,
      - that let arduino do a general delay of _20 milliseonds_ in total.
  - added COMMANDs:
    - RNMD1, RNMD2, RNMD3, RNMD4, RNMD5, RNMD6, RNMD7,
    - equivalent IDs are: 11, 12, 13, 14, 15, 15, 16, 17.
  - added STATEs:
    - MODE1, MODE2, MODE3, MODE4, MODE5, MODE6, MODE7,
    - equivalent IDs are: 11, 12, 13, 14, 15, 15, 16, 17.
  - STATE _running_ with ID _3_ is deprecated,
  - changed COMMAND CONNECT:
    - to name _CNCT_,
    - and ID to 18.
  - changed COMMAND DISCONNECT:
    - to _DCNT_,
    - and ID tp 19.

**20200331**
  - reset the _public_ and _private_ methods,
  - renamed files to _coolASSM_config.*_,
  - adding MIT License to all files.

**20200330**
  - adding class ASSM_CALLBACK for having virtual methods to be overloaded

**20200329**:
  - removing and cleaning OLED display code,
  - adding the README.md for explanation,
  - setting up reository on [github.com](https://github.com/graetz23/coolArduinoSerialStateMachine).
