#include <18F4550.h>
#DEVICE ADC=10
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN,NOPBADEN
#use delay(clock=48000000)
#include <usb/usb_bootloader.h>
#include <JACSS_CDC.c>
#USE RS232(baud=9600,xmit=pin_c6, rcv=pin_c7,bits=8,parity=N, stream=DATO)

#DEFINE LCD_RS_PIN PIN_D0
#DEFINE LCD_RW_PIN PIN_D1
#DEFINE LCD_ENABLE_PIN PIN_D2
#DEFINE LCD_DATA4 PIN_D4
#DEFINE LCD_DATA5 PIN_D5
#DEFINE LCD_DATA6 PIN_D6
#DEFINE LCD_DATA7 PIN_D7
#INCLUDE <LCD.c>

#include <stdlib.h>
float lectura=0.0;
float milivolt=0.0;
float temperatura=0.0;

char wifi_buff[20];            
int16 n = 0;
INT1 timeout_error;
INT8 timeout_error_count = 0;                                                                                                                                                                           

int16 Rx=0.0;
                                                  
void clear_mem(void) 
{
   for (int16 mem_loop = 0; mem_loop < 512; mem_loop++) {
      if (wifi_buff[mem_loop] == '\0')
      break;           
      else
      wifi_buff[mem_loop] = '\0';
   }
   n = 0;             
}
char timed_getc() {
   LONG timeout;
   timeout_error = FALSE;
   timeout = 0;

   WHILE(!kbhit() && (++timeout < 50000)) //0.5 second
   delay_us(10);

   IF(kbhit())    
   RETURN(fgetc());                     

   ELSE
   {
      timeout_error = TRUE;
      RETURN(0);
   }
}
void WIFI_CONNECT()
{
   //AT+CWJAP="ssid","password"
   int1 OK = False;
   char *oks = "On";
   char *fail = "Off";
   int loop=0;
   //for (int loop = 0; loop < 11; loop++) {
   do{
      loop++;
      timeout_error_count = 0;
      //printf(usbWrite, "Connecting to: %s Lan %u \r\n", ssid, loop);
      clear_mem();
      
      Long LONG timeout;
      timeout = 0; 

      WHILE(!kbhit() && (++timeout < 3000000)) //30 second         
      {       
         delay_us(10);   
         if (timeout % 3000 == 0) {
            timeout_error_count++;
            //lcd_gotoxy(10, 2);
            int pos = timeout_error_count % 4;
            if (pos == 0){
            printf(".");
            }
            if (pos == 1){                 
            printf(".");
            }
            if (pos == 2){
            printf(".");
            }
            if (pos == 3){
            printf(".\r\n");
            }
         }               
      }
      for (int mem_loop = 0; mem_loop < 150; mem_loop++) {
         wifi_buff[n] = timed_getc();
         n++;
         if (n > 150) n = 0;
         if (timeout_error)
         break;
      }
      /*
      char *pch = strstr(wifi_buff, oks);
      char *pch2 = strstr(wifi_buff, fail);
      IF(pch) {
         OK = TRUE;
         output_low(pin_a4);
         //return OK;
         //printf(usbWrite, "Connected to: %s Loop=%u \r\n", ssid, loop);
         break;
      }
      ELSE IF(pch2)
      {
         OK=FALSE;
         output_high(pin_a4);
         //return OK;
         //printf(usbWrite, "Connecting to: %s Error! \r\n", ssid);
         break;
      }*/
      delay_ms(100);
      break;
   }
   WHILE(OK==FALSE);
}

void main()
{
   delay_ms(500);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0);
   lcd_init();
   while(true)
   {
   
      set_adc_channel(0);
      delay_us(10);
      lectura=read_adc();
      milivolt=(lectura*5000.0)/1023.0;
      //temperatura=milivolt/10.0;
      temperatura=(milivolt-600.0)/10.0;
      printf("TEMPERATURA: %f",temperatura);
      //printf("PIC1: ");
      lcd_putc("\f");
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%f",temperatura);
      //printf("%f",temperatura);
      WIFI_CONNECT();
      Rx=atol(wifi_buff);
      output_low(pin_a4);
      delay_ms(Rx);
      output_high(pin_a4);
      printf("\r\n");
      //delay_ms(1000);
      
      
   }
   
   
}
