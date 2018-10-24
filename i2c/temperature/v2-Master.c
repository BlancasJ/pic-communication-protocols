#include <18f4550.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8000000)
#use i2c(master, sda=pin_b0, scl=pin_b1, slow)

#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#include <lcd.c>

float temp;
int8 data1;
//char data2;

int8 i2c_get(address)
{
   int8 data;
   i2c_start();
   i2c_write(address|1);
   data = i2c_read(0);
   i2c_stop();
   return (data);
}

void i2c_send(address,data)
{
   i2c_start();
   i2c_write(address);
   i2c_write(data);
   i2c_stop();
}

void main() 
{
   lcd_init();
   while(true) 
   {
      if(input(pin_a0)==1)
      {
         data1 = i2c_get(0xa0);
         temp = data1*0.4882;
         lcd_gotoxy(1,1);
         printf(lcd_putc,"\fTemperature: %f",temp);
         delay_ms(100);
      }
      if(input(pin_a1)==1)
      {
         data1 = i2c_get(0xa1);
         temp = data1*0.4882;
         lcd_gotoxy(1,1);
         printf(lcd_putc,"\fTemperature: %f",temp);
         delay_ms(100);
      }
      if(input(pin_a2)==1)
      {
         data1 = i2c_get(0xa2);
         temp = data1*0.4882;
         lcd_gotoxy(1,1);
         printf(lcd_putc,"\fTemperature: %f",temp);
         delay_ms(100);
      }
      if(input(pin_a3)==1)
      {
         data1 = i2c_get(0xa3);
         temp = data1*0.4882;
         lcd_gotoxy(1,1);
         printf(lcd_putc,"\fTemperature: %f",temp);
         delay_ms(100);
      }
      if(input(pin_a4)==1)
      {
         data1 = i2c_get(0xa4);
         temp = data1*0.4882;
         lcd_gotoxy(1,1);
         printf(lcd_putc,"\fTemperature: %f",temp);
         delay_ms(100);
      }
      if(input(pin_a5)==1)
      {
         data1 = i2c_get(0xa5);
         temp = data1*0.4882;
         lcd_gotoxy(1,1);
         printf(lcd_putc,"\fTemperature: %f",temp);
         delay_ms(100);
      }
   }
}

