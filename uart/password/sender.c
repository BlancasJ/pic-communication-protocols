#include <18f4550.h>
//#device adc=10
#include <string.h>
#include <stdlib.h>
#include <math.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8000000)
#use rs232(uart1, baud=9600)

int cont=0;
char password[4],fake0[4],fake1[4],fake2[4],fake3[4],fake4[4],fake5[4],fake6[4],fake7[4],fake8[4],fake9[4];

#int_timer3
void send()
{
   cont++;
   if(cont==100)
   {
      strcpy(fake0,"5877");
      printf(fake0);
   }
   else if(cont==200)
   {
      strcpy(fake1,"3877");
      printf(fake1);
   }
   else if(cont==300)
   {
      strcpy(fake2,"2877");
      printf(fake2);
   }
   else if(cont==400)
   {
      strcpy(fake3,"3557");
      printf(fake3);
   }
   else if(cont==500)
   {
      strcpy(fake4,"2277");
      printf(fake4);
   }
   else if(cont==600)
   {
      strcpy(fake5,"3831");
      printf(fake5);
   }
   else if(cont==700)
   {
      strcpy(fake6,"3333");
      printf(fake6);
   }
   else if(cont==800)
   {
      strcpy(fake7,"5789");
      printf(fake7);
   }
   else if(cont==900)
   {
      strcpy(fake8,"3859");
      printf(fake8);
   }
   else if(cont==1000)
   {
      strcpy(fake9,"1129");
      printf(fake9);
   }
   else if(cont==1100)
   {
      strcpy(password,"5897");
      printf(password);
      cont=0;
   }
   clear_interrupt(int_timer3);
   set_timer3(45535);
}

//#int_ext
//void word1(void)
//{
//   strcpy(password,"5897");
//   printf(password);
//   while(input(pin_b0)==1)
//   {
//      output_high(pin_b3);
//   }
//   output_low(pin_b3);
//   clear_interrupt(int_ext);
//}

//#int_ext1
//void word2(void)
//{
//   strcpy(fake,"5877");
//   printf(fake);
//   while(input(pin_b1)==1)
//   {
//      output_high(pin_b3);
//   }
//   output_low(pin_b3);
//   clear_interrupt(int_ext1);
//}

void main()
{
   //ext_int_edge( 0, L_TO_H);
   //ext_int_edge( 1, L_TO_H);
   //clear_interrupt(int_ext);
   //enable_interrupts(int_ext);
   //clear_interrupt(int_ext1);
   //enable_interrupts(int_ext1);
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
   //output_low(pin_b3);
   
   while(true)
   {
      
   }
}
