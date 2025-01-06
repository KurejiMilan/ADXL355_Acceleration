/*
 * fifo.h
 *
 * Created: Sep. 2024, Bochert
 *
 * Routines for the FIFO buffer.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

typedef struct
{
	uint8_t volatile count;       // number of characters in buffer
	uint8_t size;                 // buffer size
	uint8_t *pread;               // read pointer
	uint8_t *pwrite;              // write pointer
	uint8_t read2end, write2end;  // number of characters to overflow of read and write pointer
} fifo_t;

void fifo_init (fifo_t*, uint8_t* buf, const uint8_t size);
/*
Initializes fifo.
*/

uint8_t fifo_put (fifo_t*, const uint8_t data);
/*
Put single character inti FIFO.
*/

uint8_t fifo_get_wait (fifo_t*);
/*
Gets single character from FIFO.
*/

int fifo_get_nowait (fifo_t*);
/*
Gets single character from FIFO.
*/


static inline uint8_t
_inline_fifo_put (fifo_t *f, const uint8_t data)
/*
Put single character inti FIFO.
*/
{
	if (f->count >= f->size)
		return 0;
		
	uint8_t * pwrite = f->pwrite;
	
	*(pwrite++) = data;
	
	uint8_t write2end = f->write2end;
	
	if (--write2end == 0)
	{
		write2end = f->size;
		pwrite -= write2end;
	}
	
	f->write2end = write2end;
	f->pwrite = pwrite;

	uint8_t sreg = SREG;
	cli();
	f->count++;
	SREG = sreg;
	
	return 1;
}

static inline uint8_t 
_inline_fifo_get (fifo_t *f)
/*
Gets single character from FIFO.
*/
{
	uint8_t *pread = f->pread;
	uint8_t data = *(pread++);
	uint8_t read2end = f->read2end;
	
	if (--read2end == 0)
	{
		read2end = f->size;
		pread -= read2end;
	}
	
	f->pread = pread;
	f->read2end = read2end;
	
	uint8_t sreg = SREG;
	cli();
	f->count--;
	SREG = sreg;
	
	return data;
}
