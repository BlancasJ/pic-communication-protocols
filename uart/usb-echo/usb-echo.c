#include <18F4550.h> 
#fuses INTRC_IO,NOLVP,NOWDT,NOPROTECT,NOCPD,NOMCLR 
//#use delay(clock=20000000) 
#use delay(clock=4000000) 
//#use rs232(baud=9600, xmit=PIN_D6, rcv=PIN_D5,STREAM=PUER_PIC)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7, STREAM=PUER_PC)
#define LCD_ENABLE_PIN PIN_B0
#define LCD_RS_PIN PIN_B1
#define LCD_RW_PIN PIN_B2
#define LCD_DATA4 PIN_D7
#define LCD_DATA5 PIN_B5
#define LCD_DATA6 PIN_B6
#define LCD_DATA7 PIN_B7
#include <lcd.c>

//#DEFINE LED1 PIN_B3 
static short recibir=false; 

void recibir_pc(){ 
int i3=0; 
i3= fgetc(PUER_PC); 
Fprintf(PUER_PC,"%C",i3);} 



void main() { 
//output_high (LED1); 
//delay_ms(1000); 
//output_low (LED1); 
lcd_init();
lcd_gotoxy(1,1);
printf(lcd_putc,"Connecting...");
delay_ms(1000);
printf(lcd_putc,"Connecting.....");


while(TRUE) { 

if(kbhit(PUER_PC)){ 
recibir=true; 
} 

if (recibir==true){ 
recibir=false; 
//delay_ms(1);//SIN DELAY_MS(1) ANDA BIEN ,SI SE LO AGREGO y NO ANDA!! 
recibir_pc(); 
} 
} 
}


