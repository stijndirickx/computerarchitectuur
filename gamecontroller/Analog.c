#include "Analog.h"
#include <avr/io.h>

void AnalogInit(void)
{
	ADCA.REFCTRL = 0b0000010; // 0 - 000 (INT1V: referentie 1V) - 0 - 1 (bandgap enable: 'verboden zone') - 0 (temp sensor uit)
	ADCA.PRESCALER = 0b00000010; // 010 = DIV16 = divide by 16 --> 16 MHz / 16 = 1 MHz

}
int AnalogGetCh(int PinPos,int PinNeg)
{

	return;
}