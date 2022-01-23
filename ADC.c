#include<avr/io.h>
#include"ADC.h"

//Initialize the ADC to 128 prescalar
void adc_init(unsigned char input)
{

   ADMUX=input;

   ADCSRA |= (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz

   // Set ADC reference to AVCC

	input=adc_read();

}


uint16_t  adc_read(void)
{

	char i;
	int ADC_temp;
	int ADCr=0;


	ADCSRA |= (1 << ADEN);

	ADCSRA |= (1 << ADSC);

	while(!ADCSRA & 0x10);
	for(i=0;i<8;i++)
	{

		ADCSRA |= (1 << ADSC);
		while(!ADCSRA & 0x10);

		ADC_temp=ADCL;

		ADC_temp += (ADCH<<8);
		ADCr =ADCr + ADC_temp;
	}

		ADCr= ADCr >>3;

	//	ADCSRA|=(1<<ADIF);

		return(ADCr);
}
