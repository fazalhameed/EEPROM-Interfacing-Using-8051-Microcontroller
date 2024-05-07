#ifndef Main_H
#define Main_H

// EEPROM
void save();
void start();
void stop();
void aknowledge();
void send_byte(unsigned char);
void Read();
unsigned char read_byte();
void lcd_init(void);
void lcd_write(unsigned char);
void LCD_Command (unsigned char);
void delay(unsigned int);
void lcd_string(unsigned char *);

#endif