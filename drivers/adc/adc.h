#pragma once
#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_Init(uint8_t ref, uint8_t clock_prescale);		// ADC_init(0x00, 0x07);
void ADC_ConvStart(uint8_t channel);

// tmp = ADC_conv_start(0x00);
// tmp = tmp/10;
// temperature = tmp >> 2;

void ADC_EnableInterrupts();
uint8_t ADC_IsInConversion();

#endif /* ADC_H_ */