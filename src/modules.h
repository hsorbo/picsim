#include "../include/picsim.h"
//dirt hack to include dynamic load in static lib

 void PIC16F887_start(_pic * pic);
 void PIC18F67J94_start(_pic * pic);
 void PIC18F46J50_start(_pic * pic);
 void PIC16F18324_start(_pic * pic);
 void PIC18F47K40_start(_pic * pic);
 void PIC18F27K40_start(_pic * pic);
 void PIC16F1789_start(_pic * pic);
 void PIC16F1788_start(_pic * pic);
 void PIC16F1939_start(_pic * pic);
 void PIC16F18855_start(_pic * pic);
 void PIC16F1619_start(_pic * pic);
 void PIC16F84A_start(_pic * pic);
 void PIC16F877A_start(_pic * pic);
 void PIC16F777_start(_pic * pic);
 void PIC16F648A_start(_pic * pic);
 void PIC16F628A_start(_pic * pic);
 void PIC18F4620_start(_pic * pic);
 void PIC18F45K50_start(_pic * pic);
 void PIC18F4550_start(_pic * pic);
 void PIC18F452_start(_pic * pic);
 void PIC18F4520_start(_pic * pic);


void dirt_load (_pic * pic)
{
 PIC16F887_start(pic);
 PIC18F67J94_start(pic);
 PIC18F46J50_start(pic);
 PIC16F18324_start(pic);
 PIC18F47K40_start(pic);
 PIC18F27K40_start(pic);
 PIC16F1789_start(pic);
 PIC16F1788_start(pic);
 PIC16F1939_start(pic);
 PIC16F18855_start(pic);
 PIC16F1619_start(pic);
 PIC16F84A_start(pic);
 PIC16F877A_start(pic);
 PIC16F777_start(pic);
 PIC16F648A_start(pic);
 PIC16F628A_start(pic);
 PIC18F4620_start(pic);
 PIC18F45K50_start(pic);
 PIC18F4550_start(pic);
 PIC18F452_start(pic);
 PIC18F4520_start(pic);
};
