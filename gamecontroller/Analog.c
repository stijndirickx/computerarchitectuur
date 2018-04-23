#include "Analog.h"
#include <avr/io.h>

void AnalogInit(void)
{
	ADCA.REFCTRL = 0b0000010; // 0 - 000 (INT1V: referentie 1V) - 0 - 1 bandgap enable: 'verboden zone' - 0 (temp sensor uit)
	ADCA.PRESCALER = 0b00000010; // 010 = DIV16 = divide by 16 --> 16 MHz (clock) / 16 = 1 MHz, ADC max 1.4 mHz
	ADCA.CTRLB = 0b00010000; // 0 momenteel unused - 00 current limiet uit - 1 Conversion Mode: configured for signed mode - 0 geen freerunning - 00 conversion op 12-bit, right adjusted - 0 

}
int AnalogGetCh(int PinPos,int PinNeg)
{
	//Get analog channel value
	ADCA.CH0.MUXCTRL = ((PinPos & 0b00000111) << 3) | (PinNeg & 0b00000111); // 1e bit reserved - 4 bits MUXPOS[3:0] niet boven 15 - 3 bits MUXNEG[2:0] niet boven 7

	if(PinNeg == -1){
		//Single ended mode: input pin (0 to 15)
		ADCA.CH0.CTRL = 0b10000001; // 1 Start - 00 reserved - 00 gain - 10 inputmode single ended
	} else if(PinNeg > 3) {
		//Differential mode: GAIN
		ADCA.CH0.CTRL = 0b10000011; // 1 Start - 00 reserved - 00 gain - 10 inputmode differential
	} else {
		//Differential mode: no Gain
		ADCA.CH0.CTRL = 0b10000010; // 1 Start - 00 reserved - 00 gain - 10 inputmode differential 
	}

	ADCA.INTFLAGS = 0b00000001;	//Reset interrupt flag
	ADCA.CTRLA = 0b00000101; // 00000 = reserved - 1 CH0(ADC) start - 0 pipeline flush - 1 enable ADC
	while(ADCA.INTFLAGS == (0x00)); // wait until last bit is set = ADC conversion complete

	return ADCA.CH0.RES; // return Channel 0 Result register
}