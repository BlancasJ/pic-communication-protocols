#include <18f4550.h>
#include <string.h>
#include <stdlib.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8000000)
#use rs232(uart1, baud=9600)

#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#include <lcd.c>

char received[9], expected[9];
int comparator, cont = 0;

#int_timer3
void compare()
{
   cont++;
   if (cont == 100)
   {
      cont = 0;
      strcpy(expected, "5897");
      comparator = strcmp(expected, received);
      printf(lcd_putc, "\f");
      lcd_gotoxy(1, 1);
      if (comparator == 0)
      {
         printf(lcd_putc, "Both are equal");
      }
      else if (comparator < 0)
      {
         printf(lcd_putc, "Second is bigger");
      }
      else
      {
         printf(lcd_putc, "First is bigger");
      }
   }
   set_timer3(45535);
   clear_interrupt(int_timer3);
}

void main()
{
   setup_timer_3(T3_INTERNAL | T3_DIV_BY_1);
   set_timer3(45535);
   enable_interrupts(int_timer3);
   enable_interrupts(global);
   clear_interrupt(int_timer3);
   lcd_init();
   strcpy(received, "5897");
   while(true)
   {
   }
}
