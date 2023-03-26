/*
 * init.h
 *
 * Created: 11/24/2022 11:11:44 AM
 *  Author: Armin
 */ 


#ifndef INIT_H_
#define INIT_H_

#include <avr/io.h>
#include <avr/interrupt.h>

// Port initialization
void InitPorts();

// Timer initialization
void InitTimer();


#endif /* INIT_H_ */