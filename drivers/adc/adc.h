#pragma once
#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_Init(uint8_t ref, uint8_t clock_prescale);		// ADC_init(0x00, 0x07);

void ADC_ConvSendStart(uint8_t channel);                // Starts the ADC conversion
void ADC_ConvStart(uint8_t channel);                    // Starts the ADC if not already running

void ADC_EnableInterrupts();                            // Enables ADC interrupts
uint8_t ADC_IsInConversion();                           // Checks if ADC is in conversion


// ====================
// Sample code for ADC
// ====================

// ADC variables
// uint8_t AdcResult;
// uint8_t temperature;

// ADC initialization
// ADC_Init(0x00, 0x07);

// Enable ADC interrupts
// ADC_EnableInterrupts();

// ADC conversion start
// ADC_ConvStart(0x00);

// Interrupt handler
/* ISR(ADC_vect) {
	AdcResult = ADC;
	AdcResult = AdcResult >> 2;
	AdcResult = AdcResult/10;
	temperature = AdcResult >> 2;
	ADCSRA &= ~(1<<ADIF);
}
*/



#endif