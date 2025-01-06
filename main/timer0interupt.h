/*
 * timer0interrupt.h
 *
 * Created: Sep. 2024, Bochert
 *
 * Routines for the timer 0 for interrupt generation.
 * The interrupt service routine at TIMER0_COMP_vect will be called up. 
 */ 

void StartTimer0Interrupt(void);
/*
The timer 0 is initialized to generate an interrupt every 10 ms.
*/

void StopTimer0Interrupt(void);
/*
The timer 0 is stopped and the interrupt is disabled.
*/