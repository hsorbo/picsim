
# PICsim - PIC Simulator

PICsim emulates a microcontroller PIC16F84A/16F628/16F777/16F877A/18F452/18F4520/18F4550/18F4620 and periferics such as USART and timers, the simulator architecture permit easy implementation of external elements in c language.




## Pic supported hardware:

* ADC
* Interrupts
* WTD
* TMR0
* TMR1
* TMR2
* USART
* CCP1 ->PWM (8bits) and Comparator
* CCP2 ->PWM (8bits) and Comparator
* CCP3 ->PWM (8bits) and Comparator
* EEPROM
* IO PORTS

![PICsim Hardware Support](docs/support.png?raw=true "PICsim Hardware support")


## Utils:


com0com		- For serial emulation in windows  http://com0com.sourceforge.net/ 

tty0tty 	- For serial emulation in linux    https://github.com/lcgamboa/tty0tty or http://tty0tty.sourceforge.net/

gputils		- For assemble examples            http://gputils.sourceforge.net/

sdcc		- For compile examples             http://sdcc.sourceforge.net/

