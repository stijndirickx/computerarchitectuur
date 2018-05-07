#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "encoder.h"

volatile char encoderPosition;			//the volatile keyword indicates that a value may change between different accesses
void EncoderInit(void)
{
	//Pin 4 & 5 as input
	PORTC.DIRCLR 	= 0b00110000;		//Set Input
	PORTC.PIN4CTRL 	= 0b00011000;		//Bit 5:3 totempole pull up;
	PORTC.PIN5CTRL 	= 0b00011000;		//Bit 2:0 reacts on both edges (falling and rising)
	
	//p122-123 in processor manual
	PORTC.INTCTRL 	= 0b00000101;		//Bit 3:2 interrupt 1 op low level;	 Bit 1:0 interrupt 0 op low level 
	PORTC.INT0MASK 	= 0b00010000;		//interrupt 0 - pin 4
	PORTC.INT1MASK 	= 0b00100000;		//interrupt 1 - pin 5
	PORTC.INTFLAGS 	= 0b00000011;		//Bit 7:2 reserved; bit 1:0 interrupt n flag
	PMIC.CTRL 		= 0b10000001;		//8e bit round robin scheduling, 1ste bit low level interrupt aanzetten
}

int EncoderGetPos(void)
{
	return encoderPosition;
}

//To understand next code look at the table given in the description on p19
//there are 8 different scenario's

ISR(PORTC_INT0_vect) //PC4 is arrow (has edge)
{
	_delay_ms(5);									//against debounce time
	PORTC.INTFLAGS = 0b00000011;					//Reset interruptflag
	if((PORTC.IN & 0b00010000) == 0b00010000){		//PC4 = Arrow up (rising edge)
		if((PORTC.IN & 0b00100000) == 0b00100000){}	//PC5 = 1 (high)
			encoderPosition--;						//Encoder decrement
		}
		else{										//PC5 = 0 (low)
			encoderPosition++;						//Encoder increment
		}
	}
	else{											//PC4 = Arrow down (falling edge)
		if((PORTC.IN & 0b00100000) == 0b00100000){	//PC5 = 1 (high)
			encoderPosition++;						//Encoder increment
		}
		else{										//PC5 = 0 (low)
			encoderPosition--;						//Encoder decrement
		}
	}
}

ISR(PORTC_INT1_vect) //PC5 is arrow (has edge)
{
	_delay_ms(5);									//against debounce time
	PORTC.INTFLAGS = 0b00000011;					//Reset interruptflag
	if((PORTC.IN & 0b00100000) == 0b00100000){		//PC5 = Arrow up (rising edge)
		if((PORTC.IN & 0b00010000) == 0b00010000){	//PC4 = 1 (high)
			encoderPosition++;						//Encoder increment
		}
		else{										//PC4 = 0 (low)
			encoderPosition--;						//Encoder decrement
		}
	}
	else{											//PC5 = Arrow down (falling edge)
		if((PORTC.IN & 0b00010000) == 0b00010000){	//PC4 = 1 (high)
			encoderPosition--;						//Encoder decrement
		}
		else{										//PC4 = 0 (low)
			encoderPosition++;						//Encoder increment
		}
	}
}

//The encoder was unreliable at first, didnt take into account for the debounce time
//https://electronics.stackexchange.com/questions/318391/ky-040-rotary-middle-push-button-switch-is-unreliable