
#include "fifo.h"


// Initialize the fifo
void FifoInit(fifo_t *fifo, uint8_t *buffer, uint8_t size) {
    fifo->buffer = buffer;                      // Set the buffer   
    fifo->size = size;                          // Set the size
    fifo->head = 0;                             // Set the head
    fifo->tail = 0;                             // Set the tail
}

// Put data in the fifo
uint8_t FifoPut(fifo_t *fifo, uint8_t data) {
    uint8_t next = fifo->head + 1;              // Get the next head

    if (next >= fifo->size) {                   // Check if the next head is out of bounds
        next = 0;                               //   If so move the head to the start of the buffer
    }

    if (next == fifo->tail) {                   // Check if the next head is the same as the tail
        return 0;                               //  If so the buffer is full, return 0 to indicate failure
    }

    fifo->buffer[fifo->head] = data;            // Put the data in the buffer
    fifo->head = next;                          // Set the head to the next head

    return 1;                                   // Return 1 to indicate success
}

// Get data from the fifo
uint8_t FifoGet(fifo_t *fifo) {
    uint8_t data;                               // Create a variable to store the data

    if (fifo->head == fifo->tail) {             // Check if the head is the same as the tail
        return 0;                               //  If so the buffer is empty, return 0 to indicate failure
    }

    data = fifo->buffer[fifo->tail];            // Get the data from the buffer
    fifo->tail++;                               // Increment the tail

    if (fifo->tail >= fifo->size) {             // Check if the tail is out of bounds
        fifo->tail = 0;                         //  If so move the tail to the start of the buffer
    }

    return data;                                // Return the data
}

// Clear the fifo
void FifoClear(fifo_t *fifo) {
    fifo->head = 0;                             // Set the head to the start of the buffer
    fifo->tail = 0;                             // Set the tail to the start of the buffer
}

// Check if the fifo is full
uint8_t FifoIsFull(fifo_t *fifo) {
    uint8_t next = fifo->head + 1;              // Get the next head

    if (next >= fifo->size) {                   // Check if the next head is out of bounds
        next = 0;                               //   If so move the head to the start of the buffer
    }

    if (next == fifo->tail) {                   // Check if the next head is the same as the tail
        return 1;                               //  If so the buffer is full, return 1 to indicate full
    }

    return 0;                                   // Return 0 to indicate not full
}

// Return the number of elements in the fifo
uint8_t FifoCount(fifo_t *fifo) {
    uint8_t count = fifo->head - fifo->tail;    // Get the difference between the head and the tail

    if (fifo->head < fifo->tail) {              // Check if the head is smaller than the tail
        count += fifo->size;                    //  If so add the size of the buffer to the count
    }

    return count;                               // Return the count
}



