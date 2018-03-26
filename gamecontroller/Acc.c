#include <avr/io.h>
#include "acc.h"



void AccInit(void)
{
	//accelerometer uit slaaptoestand
	// PC6 = ACC_SLEEP
	PORTA.PIN6CTRL = 0b00010001; // 0 reserved - 0 inverted IO enable - 010 Pull-down (on input) - 001 Sense rising edge

	
}
unsigned int AccGetXAxisRaw(void)
{
	return AnalogGetCh(0, 4); //X op PA0 & PinNeg op PA4 = GND
}
unsigned int AccGetYAxisRaw(void)
{
	return AnalogGetCh(1, 4); //Y op PA1 & PinNeg op PA4 = GND
}
unsigned int AccGetZAxisRaw(void)
{
	return AnalogGetCh(2, 4); //Z op PA2 & PinNeg op PA4 = GND
}

int AccGetXAxis(unsigned int AccRaw)
{
	return 0;
}

int AccGetYAxis(unsigned int AccRaw)
{
	return 0;
}

int AccGetZAxis(unsigned int AccRaw)
{
	return 0;
}