#include <18f4550.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8000000)
#use i2c(master, sda=pin_b0, scl=pin_b1, slow)

#define use_portb_kbd
#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7

#include <lcd.c>
#include <kbd4x4.c>

float temp;
int8 data1;
char data2;
char k;

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

#int_timer3
void read_keyboard()
{
   k = kbd_getc();
   
   clear_interrupt(int_timer3);
   set_timer3(45535);
}

void main() 
{
   port_b_pullups(TRUE);
   setup_timer_3(T3_INTERNAL|T3_DIV_BY_1);
   set_timer3(45535);
   enable_interrupts(GLOBAL);
   enable_interrupts(int_timer3);
   clear_interrupt(int_timer3);
   lcd_init();
   kbd_init();
   while(true) 
   {
   
      if(k!=0)
      {
         switch (k) 
         {
   
            case 0:
               printf(lcd_putc,"0");
               break; 
   
            case 1:
               data2 = i2c_get(0xa0);
               lcd_gotoxy(1,1);
               printf(lcd_putc,"\fData: %c",data2);
              break;
              
            case 2:
               data1 = i2c_get(0xa1);
               temp = data1*0.4882;
               lcd_gotoxy(1,1);
               printf(lcd_putc,"\fTemperature: %f",temp);
               break;
               
            case 3:
               data2 = i2c_get(0xa2);
               lcd_gotoxy(1,1);
               printf(lcd_putc,"\fData: %c",data2);
              break;
              
            case 4:
               data1 = i2c_get(0xa3);
               temp = data1*0.4882;
               lcd_gotoxy(1,1);
               printf(lcd_putc,"\fTemperature: %f",temp);
               break;
   
            case 5:
               data2 = i2c_get(0xb0);
               lcd_gotoxy(1,1);
               printf(lcd_putc,"\fData: %c",data2);
              break;
              
            case 6:
               data1 = i2c_get(0xb1);
               temp = data1*0.4882;
               lcd_gotoxy(1,1);
               printf(lcd_putc,"\fTemperature: %f",temp);
               break;
               
            case 7:
               data2 = i2c_get(0xb2);
               lcd_gotoxy(1,1);
               printf(lcd_putc,"\fData: %c",data2);
              break;
              
            case 8:
               data1 = i2c_get(0xb3);
               temp = data1*0.4882;
               lcd_gotoxy(1,1);
               printf(lcd_putc,"\fTemperature: %f",temp);
               break;
            
            case 9:
               data2 = i2c_get(0xc0);
               lcd_gotoxy(1,1);
               printf(lcd_putc,"\fData: %c",data2);
              break;
              
            case 'A':
               lcd_gotoxy(1,1);
               printf(lcd_putc,"\fKey pressed:",);
               lcd_gotoxy(0,0);
               lcd_putc(k);
               break;
            
            case 'B':
               lcd_gotoxy(1,1);
               printf(lcd_putc,"\fKey pressed:",);
               lcd_gotoxy(0,0);
               lcd_putc(k);
               break;
               
            case 'C':
               lcd_gotoxy(1,1);
               printf(lcd_putc,"\fKey pressed:",);
               lcd_gotoxy(0,0);
               lcd_putc(k);
               break;
               
             case 'D':
               lcd_gotoxy(1,1);
               printf(lcd_putc,"\fKey pressed:",);
               lcd_gotoxy(0,0);
               lcd_putc(k);
               break;
               
            default:
               printf(lcd_putc,"Waiting...");
               break; 
         }
     
      }

   }
}

