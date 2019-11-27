#include <18f4550.h>
//#device adc=10
#include <string.h>
#include <math.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8000000)
#use rs232(uart1, baud=9600)

int cont=0;

#int_timer3
void send()
{
   cont++;
   if(cont==100)
   {
      printf("1520");
      output_toggle(pin_d1);
      cont=0;
   }
   clear_interrupt(int_timer3);
   set_timer3(45535);
}

void main()
{
   enable_interrupts(global);
   setup_timer_3(T3_INTERNAL|T3_DIV_BY_1);
   enable_interrupts(int_timer3);
   clear_interrupt(int_timer3);
   set_timer3(45535);
   
   while(true)
   {

   }
}
