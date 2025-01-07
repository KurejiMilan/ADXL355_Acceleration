/*
 * DataAcquisition.c
 *
 * Created: Sep. 2024, Bochert
 *
 * Program skeleton for the experiments in maritime 
 * systems laboratory of embedded system design.
 * Prior to modify the program, change the name in
 * the "Created:" line. 
 */ 

#define F_CPU 16000000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "fifo.h"
#include "uart.h"
#include "dataio.h"
#include "timer0interupt.h"

volatile uint16_t intnum=0;
volatile uint8_t *bufcounter;
volatile uint8_t sample = 0;

void InitialiseHardware(void)
{
	sei();							// enables interrupts by setting the global interrupt mask
	AdcInit();						// initializes the a/d converter
	bufcounter = uart_init(19200);	// initializes the UART for the given Baudrate
	PortInit();						// initializes the port settings
	StartTimer0Interrupt();			// timer 0 interrupt for 15 ms
}

int main(void)
/*
Example program for first experiments.
After initializing the interfaces and "Hello World" is send to the serial port.
In a period of a second port pin D7 is toggled and sample data are send to the 
serial port. These sample data contain an index, analog data input, digital port 
inputs and an interrupt counter.
*/
{
	char Text[64];
	uint16_t ADCValue;
	uint16_t index=0;

	//InitialiseHardware(); 
	//sprintf( Text,"\r\nMoin\r\n");
	//uart_puts(Text); 
	//_delay_ms(1000);
	
	while(1)
    {
		TogglePortD(7);
		//index++;
		//ADCValue=ReadAdc(6);
		//sprintf( Text,"Examples: %d %d %d %d %d\r\n",index,ADCValue,ReadPortD(3),ReadPortD(4),intnum);
		//uart_puts(Text); _delay_ms(1000);
		
		if (sample){
			TogglePortD(10);
			ADCValue += ReadAdc(6);
			sample = 0;	
		}
		if (intnum == 10){
			sprintf(Text, "V=%d\r\n", ADCValue);
			uart_puts(Text);
			ADCValue = 0;
			intnum = 0;
		}
    }
}

ISR(TIMER0_COMP_vect)
/*
Interrupt service routine for timer 0 interrupt.
*/
{
	sample = 1;
	intnum++;
}