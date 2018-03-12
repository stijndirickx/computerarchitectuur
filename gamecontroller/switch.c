#include "switch.h"
#include <avr/io.h>

void SwitchInit(void)
{
	
	//This register sets the data direction for the individual pins of the port. If DIRn is written to one,
	//pin n is configured as an output pin. If DIRn is written to zero, pin n is configured as an input pin
	PORTD.DIR &= 0b00001110; 

	//11.13.15 p124
	PORTD.PIN0CTRL= 0b00000001;		//Center
	PORTD.PIN4CTRL= 0b00000001;		//Right
	PORTD.PIN5CTRL= 0b00000001;		//Down
	PORTD.PIN6CTRL= 0b00000001;		//Left
	PORTD.PIN7CTRL= 0b00000001;		//Up
}


char SwitchGet(void)
{
	char input = PORTD.IN; 
	//PORTDIN looks like 11110001 'if everything would be pressed', the wanted format for ex.: xxx11111
	//To achieve this bitshift first 4 bits , 3 to the right and the bit on the right stays at the same place
	return ((input & 0b11110000) >> 3) | (input & 0x01);
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                