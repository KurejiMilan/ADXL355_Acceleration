/*
 * dataio.c
 *
 * Created: Sep. 2024, Bochert
 *
 * Routines for the a/d converter and digital port i/o.
 */ 

#include <avr/io.h>
#include "dataio.h"

void AdcInit(void)
/*
The a/d converter will be initialized with external reference AVCC.
The prescaler is set to 16 to enable a conversion with 62.5 kHz.
Single mode conversion requires to start each conversion separately.
*/
{
  uint16_t dummy;
 
  ADCSRA = 0B10000100;			// enable converter and set prescaler to 16
  ADMUX = 0B01000000;			// use AVCC as reference
  ADCSRA |= (1<<ADSC);			// one conversion is started to complete initialization
  while (ADCSRA & (1<<ADSC));	// wait until conversion is completed
  dummy = ADCW;					// read conversion to empty buffer	
  dummy++;						// only to avid a warning			
}

uint16_t ReadAdc(uint8_t channel)
/*
Returns the value of one conversion of the selected channel.
*/
{
  ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);	// sets conversion channel 
  ADCSRA |= (1<<ADSC);			// single conversion is started
  while (ADCSRA & (1<<ADSC));   // wait until conversion is completed
  return ADCW;                  // read conversion
}

void PortInit(void)
/*
Initialize port pins as input or output and sets the pull-up resistors
*/
{
  DDRD = 0B11100111;	// 1: output; 0: input
  PORTD = 0B00011000;	// 1: pull-up
}

void SetPortD(uint8_t Pin)
/*
Sets the selected pin.
*/
{
  PORTD |= (1 << Pin);
}

void ResetPortD(uint8_t Pin)
/*
Resets the selected pin.
*/
{
  PORTD &= ~(1 << Pin);
}

void TogglePortD(uint8_t Pin)
/*
Toggles the selected pin.
*/
{
	PORTD ^= (1 << Pin);
}

uint8_t ReadPortD(uint8_t Pin)
/*
Returns the value of the selected pin.
*/
{
  return(1 & (PIND >> Pin));
}
