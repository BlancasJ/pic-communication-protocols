#include <18F4550.h>
//#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL4,CPUDIV1,VREGEN,MCLR,NOPBADEN
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,PLL2,CPUDIV1
#use delay(clock=48000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#include <MLCD.c>

char rxString[20];
char answer[3]={'E','A','P'};

void read_rs(char* answer_esp, int16 wait_time, int8 lenghtstr)
{
   int8 i=0;
   int16 t1=0,t2=0,t_cont=0;
   
   //Lee la cadena de caracteres hasta que se acabe el tiempo o el número de caracteres de la cadena receptora
   //Para calcular el tiempo de espera se considera:
   //un reloj de 48MHz=> tc=20.8333ns;   4 pulsos de reloj por instrucción => ti=tc * 4 = 83,33ns
   //y que un loop del while utiliza aproximadamente 20 instrucciones de ensamblador => tl = ti * 20 = 1.66 us
   //para llegar a una decima de segundo se requieren: 0.1s/1.66us = 60,000 cuentas.
   while((t_cont < wait_time) && (i<(lenghtstr-1)))
   {
      if (kbhit()) 
      {
         answer_esp[i]= getc(); 
         i++; 
      }
      t1++;
      if(t1>60000)
      {
         t2++; 
         t1=0;
         if(t2>10) 
         {
            t_cont ++; 
            t2=0;
         }
      }
   }
   //Rellena el resto de la cadena con 0s para el fin de línea
   answer_esp[i]=0;
   for (i=i ;i<lenghtstr;i++)
   {
      answer_esp[i]=0;
   }
   if(answer_esp[0]!=0)
   {
      lcd_putc("\f");
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%s",rxString);
    
      if(rxString[0]==answer[0])
      {
         output_low(pin_a4);
      }
      if(rxString[0]==answer[1])
      {
         output_high(pin_a4);
      }
      if(rxString[0]==answer[2])
      {
         output_low(pin_a4);
         delay_ms(10);
         output_high(pin_a4);
         delay_ms(500);
      }
      if(rxString[1]=="HOLA")
      {
         output_low(pin_a4);
         delay_ms(500);
         output_high(pin_a4);
         delay_ms(500);
         output_low(pin_a4);
         delay_ms(500);
         output_high(pin_a4);
         delay_ms(500);
      }
   }
   
}

void main()
{
   lcd_init();
   while(true)
   {
   
   read_rs(rxString,1,20);
     
   }
}
