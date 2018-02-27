#include "switch.h"
#include <avr/io.h>

void SwitchInit(void)
{
	//11,13,15 p124
	
	PORTD.DIRCLR |= 0b11110001;
	PORTD.PIN0CTRL= 0b00000001;		//indrukkenn
	PORTD.PIN4CTRL= 0b00000001;		//rechts
	PORTD.PIN5CTRL= 0b00000001;		//beneden
	PORTD.PIN6CTRL= 0b00000001;		//links
	PORTD.PIN7CTRL= 0b00000001;		//omhoog
}


char SwitchGet(void)
{
	//return 
	PORTB.PIN0CTRL = PORTD.PIN0CTRL;
	PORTB.PIN1CTRL = PORTD.PIN4CTRL;
	PORTB.PIN2CTRL = PORTD.PIN5CTRL;
	PORTB.PIN3CTRL = PORTD.PIN6CTRL;
	PORTB.PIN4CTRL = PORTD.PIN7CTRL;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                