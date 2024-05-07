#include<reg51.h>
#include "main2.h"
#include<intrins.h>   //For using [_nop_()]

sbit scl=P2^1;
sbit sda=P2^0;
bit ack;
unsigned char reead,write,i,j;

void main()
{
	lcd_init();
	lcd_string("Send :");
	LCD_Command(0xC0);
	lcd_string("Read :");
	while(1)
	{
		save();
		Read();
	}
}
void aknowledge()	  //acknowledge condition
{
	scl=1;
	_nop_();
	_nop_();
	scl=0;
} 

void start()		//start condition
{
	sda=1;
	scl=1;
	_nop_();         //No operation
	_nop_();
	sda=0;
	scl=0;
}

void stop()			//stop condition
{
	sda=0;
	scl=1;
	_nop_();
	_nop_(); 
	sda=1;
	scl=0;
}

void send_byte(unsigned char value)	//send byte serially
{ 
	unsigned int i;
	unsigned char send;
	send=value;
	for(i=0;i<8;i++)
	{
		sda=send/128;			//extracting MSB
		send=send<<1;			//shiftng left
		scl=1;
		_nop_();
		_nop_();
		scl=0;
	}
   ack=sda;					//reading acknowledge
   sda=0;
}

unsigned char read_byte()			//reading from EEPROM serially
{
	unsigned int i;
	sda=1;
	reead=0;
	for(i=0;i<8;i++)
	{
		reead=reead<<1;
		scl=1;
		_nop_();
		_nop_();
		if(sda==1)
			reead++;
		scl=0;
	}
	sda=0;
	return reead;				//Returns 8 bit data here
}	

void save()					//save in EEPROM
{
	start();
	send_byte(0xA0);						//device address
	aknowledge();
	send_byte(0x00);						//word address
	aknowledge();
	send_byte(70);							//send data
	aknowledge();
	send_byte(65);
	aknowledge();
	stop();							   
	if(ack==0)
	{
		delay(100);
		LCD_Command(0x86);
		lcd_write('F');
		LCD_Command(0x87);
		lcd_write('A');
		
		

	}
	else
	aknowledge();
}
void Read()
{
	start();
	send_byte(0xA0);
	aknowledge();
	send_byte(0x00);
	aknowledge();
	start();
	send_byte(0xA1);					 //device address
	aknowledge();
	i=read_byte();
	aknowledge();
	j=read_byte();
	aknowledge();
	stop();
	delay(100);
	LCD_Command(0xC6);
    if(i<10)
  	{
	     lcd_write(i+48);	
	   }
	else{
   	lcd_write(i);	
  	 }

		LCD_Command(0xC7);
     if(j<10)
  	{
	     lcd_write(j+48);	
	   }
	else{
   	lcd_write(j);	
  	 }
	aknowledge();
}

