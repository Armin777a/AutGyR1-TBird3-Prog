/*
 * sevseg.h
 *
 * Created: 11/24/2022 11:14:59 AM
 *  Author: Armin
 */ 


#ifndef SEVSEG_H_
#define SEVSEG_H_

#include <avr/io.h>

// Converts a 4 digit integer into 4 different digits
void SevsegPort(uint8_t num, uint8_t digitsel);

// Writes out the input to seven segment dispaly
void SevsegOut(uint16_t val);


#endif /* SEVSEG_H_ */