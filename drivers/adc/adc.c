#include "adc.h"



// Starts the ADC conversion
void ADC_ConvSendStart(uint8_t channel) {
	ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0));
	ADMUX |= ((channel&0x08) << MUX3) | ((channel&0x04) << MUX2) | ((channel&0x02) << MUX1) | ((channel&0x01) << MUX0);
	ADCSRA |= (1 << ADSC);
}


// Starts the ADC if not already running
void ADC_ConvStart(uint8_t channel) {
	if (!ADC_IsInConversion()) {
		ADC_ConvSendStart(channel);
	}
}


// ADC initialization
void ADC_Init(uint8_t ref, uint8_t clock_prescale) {
	
	ADMUX |= ((ref&0x02) << REFS1) | ((ref&0x01) << REFS0) | (1 << ADLAR);
	
	ADCSRA |= (1<<ADEN) | ((clock_prescale&0x04) << ADPS2) | ((clock_prescale&0x02) << ADPS1) | ((clock_prescale&0x01) << ADPS0);
}


// Enables ADC interrupts
void ADC_EnableInterrupts() {
	ADCSRA |= (1 << ADIE);
	sei();
}


// Checks if ADC is in conversion
uint8_t ADC_IsInConversion() {
	return ADCSRA & (1 << ADIF);
}