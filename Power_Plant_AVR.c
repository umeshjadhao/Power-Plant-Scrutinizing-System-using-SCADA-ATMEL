#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<inttypes.h>
#include"LCD.h"
#include"USART.h"
#include"ADC.h"

void delayms(uint16_t millis); 
unsigned char data_1[20],data_2[20],data_3[100];
int result_1,result_2;

void buzzer_on()
{
	PORTB |= 0x10;
}
void buzzer_off()
{
	PORTB |= 0x00;
}

int main(void)
{
	
	DDRB=0xFF; DDRC=0xFF;
	MCUCSR=0x80;             //Disables JTAG and makes C port as I/O port 
	MCUCSR=0x80;
	lcd_init();
	USART_Init(12);
	USART_Txstr("_______________________________________");
	USART_Transmit(0x0D);
	USART_Txstr("  Temperature    Voltage    Frequency " );
	USART_Transmit(0x0D);
	USART_Txstr("      oC           mV            Hz  ");
	USART_Transmit(0x0D);
	USART_Txstr("_______________________________________");
	USART_Transmit(0x0D);
	while(1)
	{
	
		adc_init(0);		
		result_1=adc_read();
		result_1 = (float)result_1 * 4.8875;
		sprintf(data_1,"V=%dmV",result_1);
		lcdcmd(0x80);
		lcd_str(data_1);
		adc_init(1);		
		result_2=adc_read()/2;
		sprintf(data_2,"T= %d C",result_2);
		lcdcmd(0xC0);		
		lcd_str(data_2);
		lcdcmd(0x8A);		
		lcd_str("F=50Hz");
		sprintf(data_3,"    %d            %d          50 ",result_2,result_1);
		USART_Transmit(0x0D);
	//	USART_Transmit(0x0D);
		USART_Txstr(data_3);
		USART_Transmit(0x0D);
		_delay_ms(100);

		if(result_1>4500 || result_2>40)
		{
			buzzer_on();
			_delay_ms(500);
			buzzer_off();
		}
	}
}


