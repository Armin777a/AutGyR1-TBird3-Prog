#pragma once
#ifndef FIFO_H_
#define FIFO_H_

#include <avr/io.h>

typedef struct fifo {
    uint8_t *buffer;
    uint8_t size;
    uint8_t head;
    uint8_t tail;
    uint8_t count;
} fifo_t;


void FifoInit(fifo_t*, uint8_t*, uint8_t);		// Initializes the fifo, struct buffer and size
uint8_t FifoPut(fifo_t*, uint8_t);              // Gets a byte from the fifo
uint8_t FifoGet(fifo_t*);                       // Puts a byte into the fifo
void FifoClear(fifo_t*);                        // Clears the fifo
uint8_t FifoIsFull(fifo_t*);                    // Checks if the fifo is full
uint8_t FifoCount(fifo_t *fifo);                // Returns the number of bytes in the fifo


#endif