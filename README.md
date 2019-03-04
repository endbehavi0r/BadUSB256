# BadUSB256
A BadUSB Human Interface Device project that can store and execute 256 scripts at a time. <br />
This project uses a microSD breakout module with a microSD card to store and execute the scripts from. <br />
The scripts are executed according to the positions or states of the dip switches connected to the board.

## Prerequisites
This project requires the following prerequisites to be created:
* Arduino Pro Micro (Leonardo)
* microSD breakout module
* SD Card
* 8 way dip switch

## Setup
##### Connections:
```
Arduino microSD
VCC --> VCC
D15 --> SCK
D14 --> MISO
D16 --> MOSI
GND --> GND
A0 --> CS

The 8 pins on one side of the dip switch are connected to pins 2 through 10.
The 8 pins on the other side are together connected to GND.
```

##### Uploading:
***Easy way:***<br /> 
* Clone this repository
* Open Arduino IDE and select the correct port.
* Upload the sketch to the Arduino board.
<br/>
**Alternative:**<br /> 
* Download the core hex file.
* Upload them to the board using AVRdude.
=====
### Note:
The script naming convention is according to the switch states. Therefore, if all switches are in an off state, the script **"00000000.txt"** will be executed and it will execute script **"11111111.txt"** if all of them are in an on state.<br /><br />
*The **REPEAT** feature of the Ducky script has not yet been implemented.*
