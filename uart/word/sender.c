#include <18f4550.h>
//#device adc=10
#include <string.h>
#include <stdlib.h>
#include <math.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8000000)
#use rs232(uart1, baud=9600)

int cont=0;
char word[]="Que onda",word1[]="What'sup";

#int_timer3
void send()
{
   cont++;
   if(cont==100)
   {
      printf(word);
   }
   else if(cont==200)
   {
      printf(word1);
      cont=0;
   }
   set_timer3(45535);
   clear_interrupt(int_timer3);
}

void main()
{
   setup_timer_3(T3_INTERNAL|T3_DIV_BY_1);
   set_timer3(45535);
   enable_interrupts(int_timer3);
   //enable_interrupts(int_rda);
   enable_interrupts(global);
   //clear_interrupt(int_rda);
   clear_interrupt(int_timer3);
   //setup_adc(ADC_CLOCK_INTERNAL);
   //setup_adc_ports(AN0);
   //set_adc_channel(0);
   //lcd_init();
   
   while(true)
   {
      
   }
}
