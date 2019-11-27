#include "16F877.h"
#fuses HS,NOWDT,NOPROTECT,PUT,BROWNOUT,NOLVP
#device ADC=10
#use delay(clock=14745600)
#use rs232(baud=115200, xmit=PIN_C6, rcv=PIN_C7,ERRORS)
#use i2c(SLAVE, SDA=PIN_C4, SCL=PIN_C3,FAST=100000, address=0xA0,FORCE_HW) 
 
int max_read = 7,max_written = 7;
int writeBuffer[7] = {0x01,0x06,0x58,0x61,0x68,0x12,0x23};
 
 
#int_SSP 
void i2c_interrupt() 
{
   int state;
   //Get state 
   int readBuffer[23]; 
   state = i2c_isr_state(); 
   if(state==0) //Address match received with R/W bit clear, perform i2c_read( ) to read the I2C address. 
      i2c_read(); 
 
   else if (state==0x80) //Address match received with R/W bit set; perform i2c_read( ) to read the I2C address, and use i2c_write( ) to pre-load the transmit buffer for the next transaction (next I2C read performed by master will read this byte). 
      i2c_read(2); 
 
   if(state>=0x80){ //Master is waiting for data    
      i2c_write(writeBuffer[state - 0x81]); //Write appropriate byte, based on how many have already been written 
      if ((state-0x80)==max_written){
         //printf("\nFull data sent\r\n");
      }
   } 
   else if(state<=0){ //Master has sent data; read. 
      readBuffer[state - 1] = i2c_read(); //LSB first and MSB secound 
      if (state==max_read){ 
         for(int i = 0;max_read;i++)
         {
            printf("%c",readBuffer[i]); 
         }
         printf("\r\n");
      } 
   }
} 
 
void main() {
   enable_interrupts(INT_SSP);
   enable_interrupts(GLOBAL);
   printf("SLAVE\r\n");
   while(true)
   {
 
   } 
}

