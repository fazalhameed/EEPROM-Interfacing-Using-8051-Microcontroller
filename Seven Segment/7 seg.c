#include<reg51.h>
#include "mainn.h"
#include<intrins.h>   //For using [_nop_()]

sbit scl=P2^1;
sbit sda=P2^0;

bit ack;

char i=0,ii=0,j=0,jj=0,k;
unsigned long Cntr=0x70;
unsigned char count_flag=0;
unsigned char Read_var=0x01;
unsigned char message[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,};
unsigned char values[8];


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

	for(i=0;i<8;i++)
	{
		sda=value/128;			//extracting MSB
		value=value<<1;			//shiftng left
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
	unsigned long rd=0;
	sda=1;
	for(i=0;i<8;i++)
	{
		rd=rd<<1;
		scl=1;
		_nop_();
		_nop_();
		if(sda==1)
			rd++;
		scl=0;
	}
	sda=0;
	return rd;				//Returns 8 bit data here
}	

void save(unsigned char Data, unsigned char Add, unsigned char page)					//save in EEPROM
{
	start();
	send_byte(0xA0|(page<<1));						//device address
	aknowledge();
	send_byte(Add);						//word address
	aknowledge();
	send_byte(Data);							//send data
	aknowledge();
	stop();		
  delay(10);	
}
unsigned char Read(unsigned char Add, unsigned char page)
{
	unsigned long Data_var;
		start();
	send_byte(0xA0|(page<<1));
	aknowledge();
	send_byte(Add);
	aknowledge();
	start();
	send_byte(0xA1|(page<<1));					 //device address
	aknowledge();
	Data_var=read_byte();
	stop();
	delay(10);
	return Data_var;
}

void delay(unsigned int count)
{
	int y,z;
	for(y=0;y<count;y++)
		for(z=0;z<1275;z++);
}

 void timer_init(){
	 TMOD=0x01;
	TH0 = 0xF7;
	 TL0 = 0x15;
	 TR0 = 1; /* Start timer */
	 IE = 0x80;
	 ET0=1;
	 TF0=1;
 }
 
void main()
{
  timer_init();
  Cntr=Read(0,0);
  display_num_7seg(Cntr);
	while(1)
	{
		if(Read_var==0x01)
		{
		save(Cntr,0,0);
		delay(10);
	  display_num_7seg(Cntr);
		Read_var=0x00;
		}
		else if(Read_var==0x01 && count_flag==1)
		{
		save(Cntr,1,0);
		delay(10);
	  display_num_7seg(Cntr);
		Read_var=0x00;
		}
	}
}

void display_num_7seg(unsigned char num)
{
for(k=2;k>=0;k--)
 {
  values[k]=message[num%10];
	 num=num/10;
 }
 }
 void timer1_interrupt(void) interrupt 1   //ISR 2.5 ms
 {
	 TH0 = 0xF0;
	 TL0 = 0x15;
 	 P2 |=0x0C;
	 P2 &= ~(jj<<2);
	 P0 = values[jj];
	 jj++;
	 if(jj==3){
		 jj=0;
		 j++;
		 
	 }
	 if(j==10){
		 Cntr++;
		 j=0;
		 Read_var=0x01;
		 if(Cntr>=256)
		 {
		 count_flag=1;
		 }
	 }

}