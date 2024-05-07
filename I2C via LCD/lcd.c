#include<reg51.h>
#include "main2.h"

#define LCD_data P0

sbit En=P2^7;
sbit Rs=P2^6;
sbit Wr=P2^5;


void lcd_init()
{
	LCD_Command(0x38);		  // for using 8-bit 2 row LCD 
	delay(5);
	LCD_Command(0x0F);        // for display on, cursor blinking
	delay(5);
	LCD_Command(0x80);
	delay(5);

}
void lcd_string(unsigned char *lcd_data)
{
   while(*lcd_data)
   {
   lcd_write(*lcd_data++);
   }

}

void LCD_Command (unsigned char cmd)	
{
	LCD_data= cmd;
	Rs=0;				/* command reg. */
	Wr=0;				/* Write operation */
	En=1; 
	delay(1);
	En=0;
	delay(5);
}
void lcd_write (unsigned char lcd_data)
{
LCD_data=lcd_data;
Rs=1;
Wr=0;
En=1;
delay(1);
En=0;
delay(5);
}
void delay(unsigned int count)
{
	int i,j;
	for(i=0;i<count;i++)
		for(j=0;j<1275;j++);
}