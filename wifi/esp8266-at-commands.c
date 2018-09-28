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

char at_command[] = "AT", response[16], expected_response[] = "OK";
int status, i = 0;

int8 find_substring(char *needle, char *haystack)
{
   int h = 0, n = 0;
   int needle_len = strlen(needle);
   int haystack_len = strlen(haystack);

   if (needle_len == 0 || haystack_len == 0)
      return 0;

   while (h <= haystack_len - needle_len)
   {
      n = 0;
      while (n < needle_len && haystack[h + n] == needle[n])
      {
         n++;
      }
      if (n == needle_len)
         return 1;
      h++;
   }
   return 0;
}

#int_rda
void esp_response()
{
   if (i < 15)
   {
      response[i] = getc();
      i++;
      response[i] = '\0';
   }
}

void send_at(char *cmd)
{
   i = 0;
   response[0] = '\0';
   printf("%s\r\n", cmd);
   delay_ms(1000);
   status = find_substring(expected_response, response);
}

void main()
{
   enable_interrupts(int_rda);
   enable_interrupts(global);
   clear_interrupt(int_rda);
   lcd_init();

   lcd_gotoxy(1, 1);
   printf(lcd_putc, "\fSending AT...");

   send_at(at_command);

   lcd_gotoxy(1, 1);
   if (status)
   {
      printf(lcd_putc, "\fESP8266: OK");
   }
   else
   {
      printf(lcd_putc, "\fESP8266: FAIL");
   }

   while(true)
   {
   }
}
