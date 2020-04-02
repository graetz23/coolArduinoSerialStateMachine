## cool Arduino Serial State Machine

A serial device driven state machine for _all_ arduino boards: **cool Arduino Serial State Machine (coolASSM)**.

### Introduction
This is a state machine for any arduino board that can be driven via sending commands over a serial console connection. The commands are common to the know one's as: PING, PONG, ACKN, RUN, WAIT, STOP, DONE. .., and so. Arduino is going to switch between states then, like: IDLE, MODE1, MODE2, .., MODE7, or even ERROR.

The project itself shall be extended by including own code or methods to several call back methods that are cylic driven by each different state.

### Building
For building the HEX file, the [arduino Makefile](https://github.com/sudar/Arduino-Makefile) is used. Clone or download / unzip this first to your system and configure the _Makefile_ by _your local path_ where you have cloned / unzipped. Change in  _Makefile_ to your arduino board and type: _make_ && _make upload_.

### Usage
The **commands** are:

  0. NULL - the null command is driven by the state machine itself,
  1. SNA - State not available; this is the error message that leads to ERROR state,
  2. PING - send to request a PONG and to go to IDLE state,
  3. PONG - send to request a PING and to go to IDLE state,
  4. AKNWLDG - responded by eachother in case of a request,
  5. RUN - request to go from IDLE state to PROCESSING state,
  6. WAIT - may be responded to request that can not be processed yet,
  7. EVENT - may be send as notifier that an event has happend,
  8. DONE - may be send as notifier / finishing message,
  9. STOP - send to go out of PROCESSING state ot IDLE state,
  10. STATUS - request for sending back the current state,
  11. run MODE 1 - go from ANY state to this run MODE 1, if not in ERROR state,
  12. run MODE 2 - go from ANY state to this run MODE 2, if not in ERROR state,
  13. run MODE 3 - go from ANY state to this run MODE 3, if not in ERROR state,
  14. run MODE 4 - go from ANY state to this run MODE 4, if not in ERROR state,
  15. run MODE 5 - go from ANY state to this run MODE 5, if not in ERROR state,
  16. run MODE 6 - go from ANY state to this run MODE 6, if not in ERROR state,
  17. run MODE 7 - go from ANY state to this run MODE 7, if not in ERROR state,
  18. CNCT - may be used to establish a connection,
  19. DSNT - may be used to release an established connection.

The **STATES** are:

  0. ERROR - the machine go to this state in case of an error, executes [error()](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  1. IDLE - the machine is idling, waiting for commands, executes [idle()](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  11. MODE1 - the machine processes the code of method: [run_MODE1()](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  12. MODE2 - the machine processes the code of method: [run_MODE2()](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  13. MODE3 - the machine processes the code of method: [run_MODE3()](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  14. MODE4 - the machine processes the code of method: [run_MODE4()](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  15. MODE5 - the machine processes the code of method: [run_MODE5()](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  16. MODE6 - the machine processes the code of method: [run_MODE6()](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp),
  17. MODE7 - the machine processes the code of method: [run_MODE7()](https://github.com/graetz23/coolArduinoSerialStateMachine/blob/master/coolASSM.cpp).    

### Callback methods
Each _processing_ command (and each state) has its own **CALLBACK** method. Within this methods you can settle your own code or calls by _overloading_ the method. Therefore, extend the class by an own class and just reimplement the methods with your processing.

### Remarks
I use this project for driving own sensors remotely.

Everything was coded using:

  - [**atom**](https://atom.io/) editor,
  - [**arduino Makefile**](https://github.com/sudar/Arduino-Makefile),
  - [**Gnome**](https://www.gnome.org/) windows manager,
  - and [**debian**](https://www.debian.org/) GNU/Linux.


## ChangeLog

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
  - STATE _running_ with ID _3_ is decrapted,
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
