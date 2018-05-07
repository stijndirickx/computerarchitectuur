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
char bitmask;

void SimpleFunction(void);	//A simple function: print a counter (0 to 9) to the terminal
void LightLoop(void);
void SwitchPrint(void);
void TestSpeaker(void);


int main(void)
{	
	//###1###
	
	//Initialize subsystems
	ClockInit();			//Initialize system clock (16 MHz)
	USARTInit();			//Initialize USART and bind to stdout,stdin
	AnalogInit();			//Initialize ADC
	AccInit();				//Initialize accelerometer system
	LEDInit();				//Initialize LEDs
	SwitchInit();			//Initialize switches
	EncoderInit();			//Initialize encoder
	SpeakerInit();			//Initialize speaker system

	//Enable interrupts
	PMIC.CTRL|=0b00000111;  //Enable low, medium, high priority interrupts
	SREG|=0b10000000;		//Globale interrupt enable
	_delay_ms(500);

	//###2###
	//SimpleFunction();

	TestSpeaker();
	bitmask = 0b00000001;
	while (1){
		LightLoop();
		SwitchPrint();
		AccPrint();
		_delay_ms(500);
	}
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
	LEDSet(bitmask);
	if(bitmask == 0b00001000){
		bitmask >>= 3; //first led
	} else {
		bitmask <<= 1; //bitshift to next led
	}
}

void SwitchPrint(void)
{
	printf("$SWITCH %d\r\n", SwitchGet());
}

void AccPrint(void)
{
	int accXRaw = AccGetXAxisRaw();
	int accYRaw = AccGetYAxisRaw();
	int accZRaw = AccGetZAxisRaw();
	printf("$ACCRAW %d %d %d\r\n", accXRaw, accYRaw, accZRaw); // print uncalibrated X Y Z of ACC
	printf("$ACC %d %d %d\r\n", AccGetXAxis(accXRaw), AccGetYAxis(accYRaw), AccGetZAxis(accZRaw));
}

void TestSpeaker(void)
{
	SpeakerBeep(500, 500);
	_delay_ms(500);
	SpeakerBeep(1000, 500);
	_delay_ms(500);
	SpeakerBeep(1500, 500);
}