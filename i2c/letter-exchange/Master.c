#include <18f4550.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8000000)
#use i2c(master, sda=pin_b0, scl=pin_b1, slow)

int cont;
int letter=65;

void i2c_send(address,data)
{
   i2c_start();
   i2c_write(address);
   i2c_write(data);
   i2c_stop();
}

#int_timer3
void send()
{
   cont++;
   if(cont==40)
   {
      i2c_send(0xa0,letter);
      letter++;
      if(letter==91)
      {
         letter=65;
      }
      cont=0;
   }
   clear_interrupt(int_timer3);
   set_timer3(15535);
}

void main() 
{
   setup_timer_3(T3_INTERNAL|T3_DIV_BY_1);
   set_timer3(15535); //20ms
   enable_interrupts(GLOBAL);
   enable_interrupts(int_timer3);
   clear_interrupt(int_timer3);
   
   while (true) 
   {
   }
}

