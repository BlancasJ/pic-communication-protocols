#include <18f4550.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8000000)
#use i2c(slave, sda=pin_b0, scl=pin_b1, address=0xa5, slow)

void main()
{  
   int8 lm35v;
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0);
   set_adc_channel(0); 
   while(true) 
   {
      lm35v = read_adc();
      i2c_write(lm35v);
      delay_ms(100);
   }
}

