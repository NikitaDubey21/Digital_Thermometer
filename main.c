// ***********************************************************
// Project:   Digital Thermometer
// Author:    Nikita Dubey
// Module description: Digital Thermometer that displays temperature in both Celsius And Farenheit
// ***********************************************************
#include <reg51.h>

sfr lcd=0xA0;    // P2=LCD Data pins
sbit rs=P3^4;
sbit en=P3^5;

sfr adc=0x90;    //P1=ADC DATA PINS
sbit RD_adc=P3^0;
sbit WR_adc=P3^1;
sbit INTR=P3^2;

void lcd_cmd(unsigned char x);
void lcd_data(unsigned char w);
void lcd_string(unsigned char *str);
void lcd_ini(void);
void delay(unsigned int);
void celsius(signed int);
void farenheit(float);

void main()
{
	//unsigned char a;
	float value;
	lcd_ini();
	lcd_cmd(0x80);
	lcd_string("Temp: ");
	/*a=0xDF;
	lcd_data(a);
	lcd_data('C');
	lcd_data(':');*/
	lcd_cmd(0xc0);
	lcd_string("Temp: ");
	/*lcd_data(a);
	lcd_data('F');
	lcd_data(':');*/
	adc=0xFF;
	lcd=0x00;
	INTR=1;
	RD_adc=1;
	WR_adc=1;
	
	while(1)
	{
		WR_adc=0;
		delay(1);
		WR_adc=1;
		while(INTR==1);
		RD_adc=0;
		value=adc;
		celsius(value);
		delay(100);
		RD_adc=1;
	}
}

void celsius(signed int value)
{
	signed int z,x1,x2,x3,x4;
	lcd_cmd(0x87);
	z=value/10;
	x1=value%10;
	x1=x1+(0x30);
	x2=z%10;
	x2=x2+(0x30);
	x3=z/10;
	x3=x3+(0x30);
	x4=0xDF;
	lcd_data(x3);
	lcd_data(x2);
        lcd_data(x1);
	lcd_data(x4);
	lcd_data('C');
	farenheit(value);
	
}

void farenheit(float value1)
{
	float f;
	signed int g,h,y1,y2,y3,y4,y5,y6;
	lcd_cmd(0xC7);
	f = (value1*9/5)+32;
	g=f*10;
	h=g/10;
	y1=g%10;
	y1=y1+(0x30);
	y2=h%10;
	y2=y2+(0x30);
	y3=h/10;
	y4=y3%10;
	y4=y4+(0x30);
	y5=y3/10;
	y5=y5+(0x30);
	y6=0xDF;
        lcd_data(y5);
	lcd_data(y4);
	lcd_data(y2);
	lcd_data('.');
	lcd_data(y1);
	lcd_data(y6);
	lcd_data('F');
}
void lcd_cmd(unsigned char x)
{
	lcd=x;
	rs=0;
	en=1;
	delay(1);
	en=0;
	return;
}

void lcd_data(unsigned char w)
{
	lcd=w;
	rs=1;
	en=1;
	delay(1);
	en=0;
	return;
}
void lcd_string(unsigned char *str)
{
	while(*str!='\0')
 {
  lcd_data(*str);
  str++;
 }
}
void lcd_ini()
{
	delay(20);
	lcd_cmd(0x38);
	lcd_cmd(0x0C);
	lcd_cmd(0x06);
	lcd_cmd(0x01);
	lcd_cmd(0x02);
}

void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
	for(j=0;j<922;j++);
}
