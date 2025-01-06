/*
 * dataio.h
 *
 * Created: Sep. 2024, Bochert
 *
 * Routines for the a/d converter and digital port i/o.
 */ 

void AdcInit(void);
/*
The a/d converter will be initialized with external reference AVCC.
The prescaler is set to 16 to enable a conversion with 62.5 kHz.
Single mode conversion requires to start each conversion separately.
*/

uint16_t ReadAdc(uint8_t);
/*
Returns the value of one conversion of the selected channel.
input: a/d channel to be read.
return: result of a/d conversion.
*/


void PortInit(void);
/*
Initialize port pins as input or output and sets the pull-up resistors
*/

void SetPortD(uint8_t);
/*
Sets the selected pin at port D.
input: pin to be set.
*/

void ResetPortD(uint8_t);
/*
Resets the selected pin at port D.
input: pin to be reset.
*/

void TogglePortD(uint8_t);
/*
Toggles the selected pin at port D.
input: pin to be toggled.
*/

uint8_t ReadPortD(uint8_t);
/*
Returns the value of the selected pin from Port D.
input: pin to be read.
return: pin status.
*/
