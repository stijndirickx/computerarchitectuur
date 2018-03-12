#include "usart.h"
#include <avr/io.h>
#include <stdio.h>

static int stdio_putchar(char c, FILE * stream);
static int stdio_getchar(FILE *stream);
static FILE UsartStdio = FDEV_SETUP_STREAM(stdio_putchar, stdio_getchar,_FDEV_SETUP_WRITE);

void USARTInit(void)
{
	USART_PORT.DIRSET=0b00001000;	//transmitlijn als output, receive lijn als input
	USART_PORT.DIRCLR=0b00000100;
	
	USART.CTRLA=0b00000000; //polled mode = interrupts uitgeschakeld
	USART.CTRLB=0b00011000; //transmitter en reveicer aan, double speed comm uit
	USART.CTRLC=0b00000011; // USART in async mode
	
	//USART.BAUDCTRLA=0xE5; //BSEL=3301, BSCALE=-5 9600 baud
	//USART.BAUDCTRLB=0xBC; 

	//BSEL=983=0011 1101 0111, BSCALE=-7=1001 --> 115200 baud [afwijking: 115211 baud]
	USART.BAUDCTRLA=0xD7; //1101 0111
	USART.BAUDCTRLB=0x93; //1001 0011
	
	stdout=&UsartStdio; // koppeling tussen drivercode en stdio lib
	stdin=&UsartStdio;
}

//vormt onderste laag van stdio lib
static int stdio_putchar(char c, FILE * stream) //1 byte over USART
{
	USART.DATA = 0x55;//USARTD --> c, USARTC --> 0x55 = 0101 0101
	while (!(USART.STATUS & 0b01000000)); //wachten op TXCIF (Transmit Complete interrupt flag) = byte verzonden
	USART.STATUS=0b01000000; //vlag op 0 voor volgende datatransfer
	return 0;
}
	
static int stdio_getchar(FILE *stream)
{
	while (!(USART.STATUS & 0b10000000)); //wacht tot er een byte in de receive buffer zit
	return USART.DATA;
}
