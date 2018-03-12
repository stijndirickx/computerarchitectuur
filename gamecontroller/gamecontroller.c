//CONTROLLER 6
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Clock.h"
#include "USART.h"
#include "Analog.h"
#include "acc.h"
#include "LED.h"
#include "switch.h"
#include "encoder.h"
#include "speaker.h"


char text[10][10];
int a;

void SimpleFunction(void);	//A simple function: print a counter (0 to 9) to the terminal
void LightLoop(void);

int main(void)
{

	
	//###1###
	
	//Initialize subsystems
	ClockInit();			//Initialize system clock (16 MHz)
	USARTInit();			//Initialize USART and bind to stdout,stdin
	AnalogInit();			//Initialize ADC
	AccInit();				//Initialize accelerometer system
	LEDInit();				//Initialize LEDs
	//SwitchInit();			//Initialize switches
	EncoderInit();			//Initialize encoder
	SpeakerInit();			//Initialize speaker system
	
	//Enable interrupts
	PMIC.CTRL|=0b00000111;  //Enable low, medium, high priority interrupts
	SREG|=0b10000000;		//Globale interrupt enable
	_delay_ms(500);

	//###2###
	//SimpleFunction();
	LightLoop();
	while (1);
}

void SimpleFunction(void)
{
	for (a=0;a<10;a++)
	{
		//The variable text had the same address throughout the execution of the program.
		sprintf(text[a],"Counter:%d\r",a);
		puts(text[a]);
	}
}

void LightLoop(void)
{
	char bitmask = 0b00000001;
	while (1)
	{
		LEDSet(bitmask);
		if(bitmask == 0b00001000){
			bitmask >>= 3; //terug eerste led
		} else {
			bitmask <<= 1; //bitshift naar volgende led
		}
		_delay_ms(500);
		
		//GPIO INPUT:
		char switch_out[5];
		sprintf(switch_out, "SWITCH x\r\n", SwitchGet());
		puts(switch_out);
	};
}