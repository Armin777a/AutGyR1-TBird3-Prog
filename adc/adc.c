/*
 * adc.c
 *
 * Created: 30-Nov-22 22:13:35
 *  Author: Armin
 */ 

#include "adc.h"

//uint16_t AdcResult = 0;

void ADC_ConvStart(uint8_t channel) {
	//uint16_t result;
	
	ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0));
	ADMUX |= ((channel&0x08) << MUX3) | ((channel&0x04) << MUX2) | ((channel&0x02) << MUX1) | ((channel&0x01) << MUX0);
	ADCSRA |= (1 << ADSC);
	
	//while (!(ADCSRA&(1<<ADIF)));
	

	
	//return result;
}

void ADC_Init(uint8_t ref, uint8_t clock_prescale) {
	
	ADMUX |= ((ref&0x02) << REFS1) | ((ref&0x01) << REFS0) | (1 << ADLAR);
	
	ADCSRA |= (1<<ADEN) | ((clock_prescale&0x04) << ADPS2) | ((clock_prescale&0x02) << ADPS1) | ((clock_prescale&0x01) << ADPS0);
}

void ADC_EnableInterrupts() {
	ADCSRA |= (1 << ADIE);
	sei();
}

uint8_t ADC_IsInConversion() {
	return ADCSRA & (1 << ADIF);
}


/*
if (!ADC_IsInConversion()) {
	ADC_ConvStart(0x00);
}
*/

/*
ISR(ADC_vect) {
	AdcResult = ADC;
	AdcResult = AdcResult >> 2;
	AdcResult = AdcResult/10;
	temperature = AdcResult >> 2;
	ADCSRA &= ~(1<<ADIF);
}
*/