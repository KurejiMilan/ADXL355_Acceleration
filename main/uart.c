/*
 * uart.c
 *
 * Created: Sep. 2024, Bochert
 *
 * Routines for communication via UART.
 */ 

#ifndef F_CPU
#define F_CPU 16000000
#endif
#include "fifo.h"
#include "uart.h"

#define BUFSIZE_IN 0x40		// buffer for 64 characters 
uint8_t inbuf[BUFSIZE_IN];	
fifo_t infifo;

#define BUFSIZE_OUT 0x40	// buffer for 64 characters
uint8_t outbuf[BUFSIZE_OUT];
fifo_t outfifo;

uint8_t * uart_init(uint32_t baudrate)
/*
Initializes UART.
*/
{
   uint8_t sreg = SREG;
   uint16_t ubrr = (uint16_t) ((uint32_t) F_CPU/(16l*baudrate) - 1);
   UBRRL = ubrr;							// set baudrate
  
   cli();									// disable interrupts

   UCSRB = _BV(RXCIE)|(1<<RXEN)|(1<<TXEN);	// enable UART receiver and transmitter
   UCSRC = (1<<URSEL)|(3<<UCSZ0);			// data mode 8N1, asynchrony
   
   do	//flush receive buffer
   {
      UDR;
   }
   while (UCSRA & (1<<RXC));
   
   UCSRA = (1<<RXC)|(1<<TXC);	// reset receive and transmit complete flags
 
   SREG = sreg;					// disable interrupts
   
   fifo_init (&infifo,   inbuf, BUFSIZE_IN);	// initialize input FIFO buffer  
   fifo_init (&outfifo, outbuf, BUFSIZE_OUT);	// initialize output FIFO buffer
   return (uint8_t *)&outfifo.count;
}

int uart_putc(const uint8_t c)
/*
Sends single character.
*/
{
   int ret = fifo_put(&outfifo, c);
   
   UCSRB |= (1<<UDRIE);
   
   return ret;
}

void uart_puts(const char *s)
/*
Sends string.
*/
{
   do
   {
      if (*s != '\0') uart_putc(*s);
   }
   while(*s++);
}

void uart_puts_n(const char *s, const int n)
/*
Sends string with defined length.
*/
{
   for(int i=0;i<n;i++)
   {
      uart_putc(*s++);
   }
}

int uart_getc_nowait()
/*
Receives single character.
*/
{
   return fifo_get_nowait(&infifo);
}

uint8_t uart_getc_wait()
/*
Receives single character. This routine waits if 
no character is available. 
*/
{
   return fifo_get_wait(&infifo);
}

SIGNAL(USART_RXC_vect)	// received characters will be stored in input FIFO
{
   _inline_fifo_put(&infifo, UDR);
}

SIGNAL(USART_UDRE_vect)	// characters from the output FIFO will be send
{						// until buffer is empty. 
   if (outfifo.count > 0)
      UDR = _inline_fifo_get(&outfifo);
   else
      UCSRB &= ~(1<<UDRIE); // disable interrupt
} 
