#pragma once
#ifndef BUTTON_H_
#define BUTTON_H_

#include <avr/io.h>
#include "../clockfreq.h"
#include <util/delay.h>

void InitButton(uint8_t button, void (*callback)(void));    // Initialize one push button
void ButtonFunctionRun(uint8_t button);                     // Run the push button functions
void ButtonManagerFunctionCall();                           // Button manager with function pointer

uint8_t MatrixManager();                                    // Matrix keyboard manager

uint8_t ButtonManager();                                    // Returns witch button was pressed


#endif