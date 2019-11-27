#include <18f4550.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8000000)
#use i2c(slave, sda=pin_b0 , scl=pin_b1, address=0xa0, slow)

#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#include <lcd.c>

void main()
{
   int8 data;
   float temp;
   lcd_init(); 
   lcd_gotoxy(1,1);
   printf(lcd_putc,"\fHowdi");
   while(true) 
   {
      if(i2c_poll()) 
      {
         data=i2c_read();
         temp = data*0.4882;
         lcd_gotoxy(1,1);
         printf(lcd_putc,"\fTemperature: %f",temp);             
      }
   }
}
