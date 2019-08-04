#include<18f4550.h>
#fuses pll1,nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8M)
#use fast_io(a)
#use rs232(invert,uart1, baud=9600)

//Variables
int8 status=0,cont=0;

#int_timer3
void readTemp()
{
   cont++;
   if(cont >= 40)
   {
      status = input_a();
      printf("%u\r\n",status);
      cont=0;
   }
   clear_interrupt(int_timer3);
   set_timer3(15535);
}

void main()
{
   setup_timer_3(T3_INTERNAL|T3_DIV_BY_1);
   set_timer3(15535);
   enable_interrupts(GLOBAL);
   enable_interrupts(int_timer3);
   clear_interrupt(int_timer3);
   set_tris_a(0b00001111);
   while(true)
   {
   }
}

