#include "switch.h"
#include <avr/io.h>

void SwitchInit(void)
{
	//11,13,15 p124
	
	//PORTD.DIRCLR=
	PORTD.PIN0CTRL= 0b00000001;//indrukkenn
	PORTD.PIN4CTRL= 0b00000001;//rechts
	PORTD.PIN5CTRL= '00000001';//beneden
	PORTD.PIN6CTRL= '00000001';//links
	PORTD.PIN7CTRL= '00000001';//omhoog
}


char SwitchGet(void)
{
	//return 
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                