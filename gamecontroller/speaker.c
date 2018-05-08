#include <avr/io.h>
#include <avr/interrupt.h>
#include "speaker.h"
#include <util/delay.h>

void SpeakerInit(void)
{
		//Setup IO
		PORTC.DIRCLR= 0b00000001; //set individual pins as input -> Clear PC0
		
		//Setup TC for frequency generation
		TCC0.CTRLA= 0b00000001; // Bit 7:4 – Reserved, Bit 3:0 Clock select 1 = Prescaler: Clk
		TCC0.CTRLB= 0b00010011; // Bit 7:4 – CCxEN = CCAEN capture A channel = Pin PC0, Bit 3 – Reserved, Bit 2:0 - Waveform Generation Mode = Single-slope PWM
		TCC0.CTRLC= 0b00000000; // Bit 3:0 – CMPx: Compare Output Value x
		TCC0.CTRLD= 0b00000000; // Bit 7:5 – Event Action = None, Bit 3:0 - Timer Event Source Select = None
		TCC0.CTRLE= 0b00000000; // Bit 1:0 – Byte Mode = NORMAL
		
		//Setup TC for duration timing
		//TCC1.CTRLA=
		//TCC1.CTRLB=
		//TCC1.CTRLC=
		//TCC1.CTRLD=
		//TCC1.CTRLE=
		
}
void SpeakerBeep(int Frequency,int Length)
{
	//single-slope PWM frequency = Fclk / (n*(PER + 1)) ==> PER = (Fclk - 1)/(freq*N) --> FORMULE P145
	int fper = (16000000-1)/(Frequency*1); //Fclk = 16 MHz, prescaler divider used N = 1

	TCC0.PER = fper; // topvalue
	TCC0.CCA = fper/2; // pulse width (duty cycle)

	PORTC.DIRSET = 0b00000001; // set individual pins as output
	_delay_ms(Length);
	PORTC.DIRCLR=0b00000001; // set pin back to input & clear
}



