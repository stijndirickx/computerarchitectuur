#include <avr/io.h>
#include "acc.h"



void AccInit(void)
{
	//De accelerometer dient geïnitialiseerd te worden.
	//Dit houdt in dat de accelerometer uit slaaptoestand moet gehaald worden. 

	//accelerometer uit slaaptoestand
	// PC6 = ACC_SLEEP
	PORTC.DIRSET = 0b01000000;
	PORTC.PIN6CTRL = 0b00010001; // 0 reserved - 0 inverted IO enable - 010 Pull-down (on input) - 001 Sense rising edge

	//accelerometer actief zetten
	PORTC.OUTSET = 0b01000000; //driven high
	
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

//Acc needs to return value:
//min -1000
//neutral 0 
//max  1000

//Callibratie voor bord 7
int AccGetXAxis(unsigned int AccRaw)
{
	//min = 420; max = 1200;
	double schaalfactor = 2.56; //(2000/(1200-420))
	return (schaalfactor * AccRaw) - 2080; 
	//2080 is nieuwe offset na schaling
}

int AccGetYAxis(unsigned int AccRaw)
{
	//min = 450; max = 1250;
	double schaalfactor = 2.5; //(2000/(1250-450))
	return (schaalfactor * AccRaw) - 2135;
	//2135 is nieuwe offset na schaling
}

int AccGetZAxis(unsigned int AccRaw)
{
	//min = 300; max = 1075;
	double schaalfactor = 2.58; //(2000/(1075-300))
	return (schaalfactor * AccRaw) - 1770;
	//1770 is nieuwe offset na schaling
}