#include "Analog.h"
#include <avr/io.h>

void AnalogInit(void)
{
	ADCA.REFCTRL = 0b0000010; // 0 - 000 (INT1V: referentie 1V) - 0 - 1 (bandgap enable: 'verboden zone') - 0 (temp sensor uit)
	ADCA.PRESCALER = 0b00000010; // 010 = DIV16 = divide by 16 --> 16 MHz (clock) / 16 = 1 MHz
	//ADCA.CTRLB = 0b00010000; // 0 momenteel unused - 00 current limiet uit - 1 Conversion Mode: configured for signed mode - 0 geen freerunning - 00 conversion op 12-bit, right adjusted - 0 

}
int AnalogGetCh(int PinPos,int PinNeg)
{
	//Get analog channel value
	ADCA.CH0.MUXCTRL = ((PinPos & 0b00000111) << 3) | (PinNeg & 0b00000111); // 1e reserved - MUXPOS[3:0] niet boven 15 - MUXNEG[2:0] niet boven 7

	//PinPos:
		//Differential mode: positive input pin (0 to 15)
		ADCA.CH0.CTRL = 0b10000010; // 1 Start - 00 reserved - 00 gain - 10 inputmode differential 

		//Single ended mode: input pin (0 to 15)
		ADCA.CH0.CTRL = 0b10000001; // 1 Start - 00 reserved - 00 gain - 10 inputmode single ended 

	//PinNeg:
		//Differential mode: negative input pin (0 to 7)
		ADCA.CH0.CTRL = 0b10000010;

		//Single ended mode: write '-1' to select single ended mode

	ADCA.CTRLA = 0b00000101; // 00000 = reserved - 1 CH0start - 0 pipeline flush - 1 enable ADC
	while(ADCA.INTFLAGS == (0x00)); // if laatste bit is set = ADC conversion complete

	//Return value:
	//-2048 to 2047 (signed) or 0 to 4095 (unsigned)
	//10000: Invalid pin settings
	return ADCA.CH0RES; // return Channel 0 Result register
}