#pragma once
#ifndef LED_H_
#define LED_H_

#include <avr/io.h>

void LedOut(uint8_t led);
void RgbLed(uint8_t red, uint8_t green, uint8_t blue);

#endif