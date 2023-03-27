#pragma once
#ifndef SEVSEG_H_
#define SEVSEG_H_

#include <avr/io.h>

void SevsegPort(uint8_t num, uint8_t digitsel);     // Converts a 4 digit integer into 4 different digits
void SevsegOut(uint16_t val);                       // Writes out the input to seven segment dispaly

#endif