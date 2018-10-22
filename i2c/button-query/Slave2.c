#include <18f4550.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8000000)
#use i2c(slave, sda=pin_b0, scl=pin_b1, address=0xb0, slow)

void main() 
{
   int8 letter=65;
   while (true) 
   {
      i2c_write(letter);
      letter++;
      if(letter==91)
      {
         letter=65;
      }
      delay_ms(100);
   }
}

