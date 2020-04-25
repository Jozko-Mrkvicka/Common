#include <mega8.h>

unsigned char znak;

interrupt [12] void USART_RX_PRERUSENIE(void) 
{ 
  znak = UDR;
  UDR = znak;    
}

void main(void)
{
   SREG = 0x80;   // 10000000 - povoluje Global Interrupt Enable
   UCSRA = 80;    // 10000000 - generuje Recieve Complete Interrupt  
   UCSRB = 0x98;    // 10011000 - povolenie prerusenia na USART Rx   
   UCSRC = 0x86;
   UBRRH = 0x00;
   UBRRL = 25;      // 00011001 

  while (1) ;
}
