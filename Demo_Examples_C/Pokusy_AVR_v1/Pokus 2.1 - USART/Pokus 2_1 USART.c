#include <mega8.h>

void USARTinit(void) {       
  SREG = 0x80;  // global interrupt enable
  
  UCSRA = (0 << U2X)    // double USART transmission speed - zakazane
        | (0 << MPCM);  // multi-processor mod - zakazany

  UCSRB = (1 << RXCIE)  // RX complete interrupt enable
        | (0 << TXCIE)  // TX complete interrupt enable - zakazane
        | (0 << UDRIE)  // USART UDR empty interrupt enable - zakazane
        | (1 << RXEN)   // reciever enable - povoleny
        | (1 << TXEN)   // transmitter enable - povoleny
        | (0 << UCSZ2); // v kombinacii s UCSZ1 a UCSZ0 urcuje dlzku prenasaneho znaku, 8 bitov 
        
  UCSRC = (1 << URSEL)  // register select - UCSRC a UBRRH "shares the same I/O location",
                        // preto sa s URSEL vybera do ktoreho registra sa bude zapisovat/citat,
                        // 1 = UCSRC, 0 = UBRRH
        | (0 << UMSEL)  // USART mode select, 0 = asynchronous, 1 = synchronous operation             
        | (0 << UPM1)   // parity mode, 0 = bez parity
        | (0 << UPM0)   // parity mode, 0 = bez parity
        | (0 << USBS)   // stop bit select, 0 = 1 stop bit
        | (1 << UCSZ1)  // character size, v kombinacii s UCSZ0 a UCSZ3 nastavuje dlzku znaku, 8 bitov
        | (1 << UCSZ0)  // character size, v kombinacii s UCSZ1 a UCSZ3 nastavuje dlzku znaku, 8 bitov
        | (0 << UCPOL); // clock polarity, pouziva sa iba v synchronnom mode
        
  UBRRH = 0x00;  // USART baud rate register, horna cast
  UBRRL = 0x19;  // USART baud rate register, dolna cast, 
                 // nastavenie plati pre 4 MHz krystal, U2X = 0 (obycajna rychlost) a 9600 baudov
}

void main(void)
{
  unsigned char znak = 'z';

  USARTinit();

  while (1)
  {
    if ((UCSRA & (1 << UDRE)) == 0x20)  // UDRE = 1, => je mozne zapisovat do UDR, tak ...
    {                             
      UDR = znak;
    }
  }
}