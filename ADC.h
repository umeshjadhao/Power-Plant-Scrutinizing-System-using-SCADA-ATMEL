#include<avr/io.h>
#ifndef ADC_H
#define ADC_H
void adc_init(unsigned char);
uint16_t  adc_read(void);
#endif
