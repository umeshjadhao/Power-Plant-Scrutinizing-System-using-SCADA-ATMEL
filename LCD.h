void lcd_init(void);                         //Initialize LCD
void lcdcmd(unsigned char);                  //Send Command to LCD
void lcddata(unsigned char);                 //Send Data to LCD
void lcd_str(const char *s);
void LCDWriteInt(int,unsigned int);
                 // Display String
void delayms(uint16_t millis);

void delayms(uint16_t millis)              /*Delay Function*/
{
	while(millis)
	{
		_delay_ms(1);
		millis--;
	}
}


	void lcdcmd(unsigned char value)
	{
		PORTC=value;             /*Send values to PortC*/
		PORTB=0x01;             /*RS=0,RW=0,En=1   (001)*/
		delayms(1);
		PORTB=0x00;				/*RS=0,RW=0,EN=0   (000)*/
		return;
	}

	void lcddata(unsigned char value)
	{
		PORTC=value;				
		PORTB=0x05;				/*RS=1, RW=0,EN=1   (101)*/
		delayms(1);
		PORTB=0x04;				/*RS=1, RW=0,EN=0    (100)*/
		return ;
	} 


	void lcd_str(const char *s)
	{
		while(*s)
		{
			lcddata(*s++);
		}
			return;
	}

	void lcd_init(void)
	{
	
		lcdcmd(0x38);         /*2 lines and 5x2 matrix */
		delayms(1);
	
		lcdcmd(0x0C);         /*Display on Cursor Blinking*/
		delayms(1);

	
		lcdcmd(0x01);         /*Clear Display Screen*/
		delayms(1);

	
		lcdcmd(0x06);         /*Increement Cursor(Shift Cursor to right)*/
		delayms(1);

	
		lcdcmd(0x80);         /*Force Cursor to beginning of Line*/
		delayms(1);         /* Put C0 to force cursor to second line*/
	}

void LCDWriteInt(int val,unsigned int field_length)
{	
	
		
	char str[5]={0,0,0,0,0};
	int i=4,j=0;
	while(val)
	{
	str[i]=val%10;
	val=val/10;
	i--;
	}
	if(field_length==-1)
		while(str[j]==0) j++;
	else
		j=5-field_length;

	if(val<0) lcddata('-');
	for(i=j;i<5;i++)
	{
	lcddata(48+str[i]);
	}
	
}







