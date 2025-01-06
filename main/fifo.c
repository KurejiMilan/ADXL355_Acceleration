/*
 * fifo.c
 *
 * Created: Sep. 2024, Bochert
 *
 * Routines for the FIFO buffer.
 */ 

#include "fifo.h"

void fifo_init (fifo_t *f, uint8_t *buffer, const uint8_t size)
/*
FIFO is initialized.
*/
{
	f->count = 0;
	f->pread = f->pwrite = buffer;
	f->read2end = f->write2end = f->size = size;
}

uint8_t fifo_put (fifo_t *f, const uint8_t data)
/*
Put single character inti FIFO.
*/
{
	return _inline_fifo_put (f, data);
}

uint8_t fifo_get_wait (fifo_t *f)
/*
Gets single character from FIFO. If no character is available
the routine waits until the next character is received.
*/
{
	while (!f->count);
	
	return _inline_fifo_get (f);	
}

int fifo_get_nowait (fifo_t *f)
/*
Gets single character from FIFO. Only if a character is available.
*/
{
	if (!f->count)		return -1;
		
	return (int) _inline_fifo_get (f);	
}
