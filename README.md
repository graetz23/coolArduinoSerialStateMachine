## cool Arduino Serial State Machine

A serial device driven state machine for _all_ arduino boards: **cool Arduino Serial State Machine (coolASSM)**.

### Introduction
This is a state machine for any arduino board that can be driven via sending commands over a serial console connection. The commands are common to the know one's as: PING, PONG, ACKNWLDG, WAIT, PROCESS, .., and so. Arduino is going to switch between states then, like: IDLE, RUNNING, or even ERROR.

The project itself shall be extended by including own code or methods to several call back methods that are cylic driven by each different state.

### Building
For building the HEX file, the [arduino Makefile](https://github.com/sudar/Arduino-Makefile) is used. So clone or download / unzip this first to your system. Afterwards configure the _Makefile_ to your arduino boards and type: _make_.

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
  21. CONNECT - may be used to establish a connection,
  22. DISCNCT - may be used to release an established connection.

The **STATES** are:

  0. ERROR - the machine go or should go to this state in case of an error,
  1. IDLE - the machine is idling and waiting for commands,
  2. RUNNING - the machine processes its tasks.

### Callback methods
Each command (and each state) has its own **CALLBACK** method. Within this methods you can settle your own code or calls by _overloading_ the method. Therefore, extend the class by an own class and just reimplement the method with your processing.

### Remarks
I use this project for driving own sensors remotely.

Everything was coded using:

  - [**atom**](https://atom.io/) editor,
  - [**arduino Makefile**](https://github.com/sudar/Arduino-Makefile),
  - [**Gnome**](https://www.gnome.org/) windows manager,
  - and [**debian**](https://www.debian.org/) GNU/Linux.


## ChangeLog

**20200330**
  - adding class ASSM_CALLBACK for having virtual methods to be overloaded

**20200329**:
  - removing and cleaning OLED display code,
  - adding the README.md for explanation,
  - setting up reository on [github.com](https://github.com/graetz23/coolArduinoSerialStateMachine).
