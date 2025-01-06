/*
 * uart.h
 *
 * Created: Sep. 2024, Bochert
 *
 * Routines for communication via UART.
 */ 

#include <avr/io.h>

uint8_t * uart_init(uint32_t);
/*
Initializes UART.
*/

int uart_putc(const uint8_t);
/*
Sends single character.
*/

uint8_t uart_getc_wait(void);
/*
Receives single character.
*/

int uart_getc_nowait(void);
/*
Receives single character.
*/

void uart_puts_n(const char *s,const int);
/*
Sends string.
*/

void uart_puts(const char *s);
/*
Sends string.
*/

static inline void uart_flush(void)
{
   while (UCSRB & (1<<UDRIE));
}
