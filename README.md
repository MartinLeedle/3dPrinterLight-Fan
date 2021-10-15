# 3dPrinterLight-Fan
Primarily an Arduino Nano giving PWM outputs to a fan and LED strip. Utilized a L298N due to it being around. Both the fan and the LED require 12V input, 
so the L298N fit the requirements. The power source is 24V from an Ender 3 power supply. The PWM of the fan is controlled by a Thermistor that will increase
or decrease PWM depending on enclosure temperature. The LED strip is controlled by a switch. There is no interupts. All of the controlling is done in a 
superloop that will wait refresh every 1 second.

BOM

Arduino Nano 	  x1

Thermistor 100k   x1

Resistor   100k   x1

LED Strip 12V 1ft x1

L298N		  x1

Switch		  x1

PC Fan 12V	  x1

Installation
A Schematic will be the Directory. This project was created with the PlatformIO addon on VSCode, and that will be required to run the Code.
