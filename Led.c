#include "LED.h"
#include <avr/io.h>

void LEDInit(void)
{
	PORTE.DIRSET |= 0b00001111; //dir = 1 --> output
	PORTE.PIN0CTRL=PORT_OPC_PULLUP_gc; //enkel belangrijk on input
	PORTE.PIN1CTRL=PORT_OPC_PULLUP_gc;
	PORTE.PIN2CTRL=PORT_OPC_PULLUP_gc;
	PORTE.PIN3CTRL=PORT_OPC_PULLUP_gc;
}

void LEDSet(char bitmask)
{
	PORTE.OUT &= 0b11110000; //4 ledbits op 0, rest blijft ongewijzigd
	PORTE.OUT |= ~bitmask; //juiste ledbit wordt op 1 gezet
}