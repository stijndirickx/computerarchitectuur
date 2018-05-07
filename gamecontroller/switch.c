#include "switch.h"
#include <avr/io.h>

void SwitchInit(void)
{
	
	//This register sets the data direction for the individual pins of the port. If DIRn is written to one,
	//pin n is configured as an output pin. If DIRn is written to zero, pin n is configured as an input pin
	//PORTD.DIR &= 0b00001110; 
	PORTD.DIRSET |= 0b00001110; 

	//11.13.15 p124
	PORTD.PIN0CTRL= 0b01011001;		//Center
	PORTD.PIN4CTRL= 0b01011001;		//Right
	PORTD.PIN5CTRL= 0b01011001;		//Down
	PORTD.PIN6CTRL= 0b01011001;		//Left
	PORTD.PIN7CTRL= 0b01011001;		//Up
}


char SwitchGet(void)
{
	char input = PORTD.IN; 
	//PORTDIN looks like 11110001 'if everything would be pressed', the wanted format however is: 00011111
	//To achieve this, bitshift 4 bits 3 places to the right and keep the other bit at the same place
	input = ((input & 0b11110000) >> 3) | (input & 0b00000001);
	return input;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                