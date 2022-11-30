/*
 * adc.c
 *
 * Created: 30-Nov-22 22:13:35
 *  Author: Armin
 */ 

uint16_t ADC_conv_start(uint8_t channel) {
	uint16_t result;
	
	ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0));
	ADMUX |= ((channel&0x08) << MUX3) | ((channel&0x04) << MUX2) | ((channel&0x02) << MUX1) | ((channel&0x01) << MUX0);
	ADCSRA |= (1 << ADSC);
	
	while (!(ADCSRA&(1<<ADIF)));
	
	result = ADC;
	result = result >> 2;
	
	return result;
}

void ADC_init(uint8_t ref, uint8_t clock_prescale) {
	
	ADMUX |= ((ref&0x02) << REFS1) | ((ref&0x01) << REFS0) | (1 << ADLAR);
	
	ADCSRA |= (1<<ADEN) | ((clock_prescale&0x04) << ADPS2) | ((clock_prescale&0x02) << ADPS1) | ((clock_prescale&0x01) << ADPS0);
}