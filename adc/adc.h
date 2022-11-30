/*
 * adc.h
 *
 * Created: 30-Nov-22 22:13:42
 *  Author: Armin
 */ 


#ifndef ADC_H_
#define ADC_H_

void ADC_init(uint8_t ref, uint8_t clock_prescale);		// ADC_init(0x00, 0x07);
uint16_t ADC_conv_start(uint8_t channel);

// tmp = ADC_conv_start(0x00);
// tmp = tmp/10;
// temperature = tmp >> 2;


#endif /* ADC_H_ */