#include "16F877.h"
#device ADC=16
#FUSES NOWDT, NOBROWNOUT, NOLVP                    
#use delay(crystal=14745600)
#use rs232(baud=115200,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1)
#use i2c(Master,Fast,sda=PIN_C4,scl=PIN_C3)
 
#define SLAVE_WRITE_ADDR 0xA0
#define SLAVE_READ_ADDR  0xA1
 
void write_slave(int address, int *buffer, int n_read)
{
   int n_byte = 0;
   i2c_start();
   i2c_write(address);
   for(n_byte = 0;n_read;n_byte++)
   {
      i2c_write(buffer[n_byte]);
   }
   i2c_stop();
}
 
void read_slave(int address, int *buffer, int n_read){
   int n_byte = 0;
   i2c_start();
   i2c_write(address);
   for(n_byte = 0;n_read-1;n_byte++)
   {
      buffer[n_byte] = i2c_read();
   }
   buffer[n_byte] = i2c_read(0);
   i2c_stop();
}
 
void print_buffer(int *buffer, int length){
   int n_byte;
   for(n_byte = 0;length;n_byte++)
   {
         printf("%c",buffer[n_byte]);
   }
    printf("\r\n");
}
 
void main()
{
   int n_read = 7,n_write = 7;
   int writeBuffer[7] = {0x01,0x06,0x58,0x61,0x68,0x12,0x23}; //"Por el Slave todo bien"
   int readBuffer[7];
   printf("MASTER\r\n");
   while(true)
   {
      write_slave(SLAVE_WRITE_ADDR, writeBuffer, n_write);
      delay_ms(100);
      read_slave(SLAVE_READ_ADDR, readBuffer, n_read);
      print_buffer(readBuffer,n_read);
      delay_ms(100);
   }
}

