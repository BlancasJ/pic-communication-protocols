#include<18f4550.h>
#fuses pll1,nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8M)
#use rs232(uart1, baud=9600)
#include <string.h>

#define LCD_ENABLE_PIN  PIN_D1
#define LCD_RS_PIN      PIN_D2
#define LCD_RW_PIN      PIN_D3
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D5
#define LCD_DATA6       PIN_D6
#define LCD_DATA7       PIN_D7     
#include <lcd.c>

// Esta funcion recibe como parametros el comando AT, ciertos valores para sacar un tiempo de espera, el pic esperara cierto tiempo la respuesta del ESP y regresa la respuesta de este
void read_kbhit_uart( char* answer_esp, int16 wait_time, int8 lenghtstr)
{
   int8 i=0;
   int16 t1=0,t2=0,t_cont=0;

   //printf(at_command);
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
      IF (t1>5000)
      {
         t2++; t1=0;
         IF (t2>10) 
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
}

char string[120];

void main()
{
   lcd_init();
   lcd_gotoxy(1,1);

   while(true)
   {
      printf("¿Que onda?");
      delay_ms(1000);
      printf("What's up?");
      delay_ms(1000);
   } 
}
