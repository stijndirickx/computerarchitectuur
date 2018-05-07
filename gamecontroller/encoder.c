#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "encoder.h"

volatile char encoderPosition;			//the volatile keyword indicates that a value may change between different accesses
void EncoderInit(void)
{
	PORTC.DIRCLR = 0b00110000;		//Set Input
	
	//pin 4&5
	//bit4t/m6 (011) --> totempole pull up
	//bit3t/m1 (000) --> reageert op rising EN falling edge
	PORTC.PIN4CTRL = 0b00011000;
	PORTC.PIN5CTRL = 0b00011000;
	
	//bit4t/m3 - interrupt 1 op low level
	//bit2t/m1 - interrupt 0 op low level
	PORTC.INTCTRL = 0b00000101;	
			
	PORTC.INT0MASK = 0b00010000;		//interrupt 0 - pin 4
	PORTC.INT1MASK = 0b00100000;		//interrupt 1 - pin 5
	PORTC.INTFLAGS = 0b00000011;
	PMIC.CTRL = 0b10000001;				//8e bit round robin scheduling, 1ste bit low level interrupt aanzetten
}

int EncoderGetPos(void)
{
	return encoderPosition;
}

ISR(PORTC_INT0_vect)
{
	_delay_ms(5);						//against debounce time
	PORTC.INTFLAGS = 0b00000011;		//Reset interruptflag
	if((PORTC.IN & 0x10) == 0x10)		//PC4 rising edge
	{
		if((PORTC.IN & 0x20) == 0x20)	//PC5 hoog
		{
			encoderPosition--;			//Encoder decrementeren
		}
		else							//PC5 laag
		{
			encoderPosition++;			//Encoder incrementeren
		}
	}
	else								//PC4 falling edge
	{
		if((PORTC.IN & 0x20) == 0x20)	//PC5 hoog
		{
			encoderPosition++;			//Encoder incrementeren
		}
		else							//PC5 laag
		{
			encoderPosition--;			//Encoder decrementeren
		}
	}
}

ISR(PORTC_INT1_vect)
{
	_delay_ms(5);						//against debounce time
	PORTC.INTFLAGS = 0b00000011;		//Reset interruptflag
	if((PORTC.IN & 0x20) == 0x20)		//PC5 rising edge
	{
		if((PORTC.IN & 0x10) == 0x10)	//PC4 hoog
		{
			encoderPosition++;			//Encoder incrementeren
		}
		else							//PC4 laag
		{
			encoderPosition--;			//Encoder decrementeren
		}
	}
	else								//PC5 falling edge
	{
		if((PORTC.IN & 0x10) == 0x10)	//PC4 hoog
		{
			encoderPosition--;			//Encoder decrementeren
		}
		else							//PC4 laag
		{
			encoderPosition++;			//Encoder incrementeren
		}
	}
}