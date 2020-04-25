#include <mega8.h>
#include <delay.h>

#define DME_ADDRESS_SR 0x02;  // slave reciever, master transmitter
#define DME_ADDRESS_ST 0x03;  // slave transmitter, master reciever

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

unsigned char DME1[] = "------",  // hodnoty zodpovedajuce radiu NAV1
              DME2[] = "------",  // hodnoty zodpovedajuce radiu NAV2
              DMEspinac = '1',    // poloha spinaca zariadenia DME
              TypDat;             // idetifikuje prijimane data zo serioveho portu

void NacitajData(int PocetBajtov, unsigned char* pDest)  // prijme z USARTU urceny pocet znakov
{
  int i;
  
  for (i = 0; i < PocetBajtov; i++) 
  {
    while (!(UCSRA & (1 << RXC))) ;
    pDest[i] = UDR;        
  }
}
              
interrupt [12] void USART_RX_Hotovo(void)  // prerusenie sa zavola ked sa v UDR nachadza znak 
{                                            
  while (!(UCSRA & (1 << RXC))) ;
  TypDat = UDR;  // prvy bajt prenasanych dat je adresa, urcuje kam patria (DME, NAV, COM ...)
  
  switch (TypDat)
  {
    case 0x81 : NacitajData(6, DME1); break;  // DME 1   
    case 0x82 : NacitajData(6, DME2); break;  // DME 2
  }
}

void main(void) 
{
  int i;

  TWBR = 0x00;  // TW bit rate register - rychlost SCL       
  USARTinit();
  while (1) 
  {                                                              
    delay_ms(10);  // rychlost odosielania dat na seriovy port
    if ((UCSRA & (1 << UDRE)) == 0x20)  // ak UDRE = 1, tak je mozne zapisovat do UDR
    {                             
      UDR = DMEspinac;  // odosle polohu spinaca cez seriovy port
    }                                                
    
    TWCR = (1 << TWINT) | (1 << TWSTA) | (0 << TWSTO) | (1 << TWEN);  // start bit       
    while (!(TWCR & (1 << TWINT))) ;  // caka na odoslanie startu
    
    if ((TWSR & 0xF8) == 0x08)  // start bol odoslany
    {
      TWDR = DME_ADDRESS_ST;  // nahraje adresu slejva
      TWCR = (1 << TWINT) | (0 << TWSTA) | (0 << TWSTO) | (1 << TWEN);  // posle adresu slejva
      while (!(TWCR & (1 << TWINT))) ;  // caka na odoslanie adresy
      
      if ((TWSR & 0xF8) == 0x40)  // SLA+R odoslana, ACK prijaty
      {                          
        // zhodi vlajku, TWEA = 0 znamena ze sa ocakava prijatie posledneho bajtu
        TWCR = (1 << TWEN) | (0 << TWSTA) | (0 << TWSTO) | (1 << TWINT) | (0 << TWEA);  
        while (!(TWCR & (1 << TWINT)));  // caka na prijatie dat
        DMEspinac = TWDR;  // ulozi prijate data                 
        
        if ((TWSR & 0xF8) == 0x50)  // data prijate, ACK odoslany
        { }                                                        
        if ((TWSR & 0xF8) == 0x58)  // data prijate, NOT ACK odoslany
        { }                                                        
        
        TWCR = (1 << TWINT) | (0 << TWSTA) | (1 << TWSTO) | (1 << TWEN);  // posle stop bit
        TWCR = (1 << TWINT) | (1 << TWSTA) | (0 << TWSTO) | (1 << TWEN);  // posle start bit
        while (!(TWCR & (1 << TWINT))) ;
           
        TWDR = DME_ADDRESS_SR;  // nahraje adresu slejva
        TWCR = (1 << TWINT) | (0 << TWSTA) | (0 << TWSTO) | (1 << TWEN);  // posle adresu slejva        
        while (!(TWCR & (1 << TWINT))) ;  // caka na odoslanie adresy
              
        if ((TWSR & 0xF8) == 0x18)  // SLA+W poslany, ACK prijaty
        {                    
          for (i = 0; i <= 5; i++)
          {            
            if (DMEspinac == '1')  // nahraje data
              TWDR = DME1[i]; 
            else
              TWDR = DME2[i];
                         
            TWCR = (1 << TWINT) | (0 << TWSTA) | (0 << TWSTO) | (1 << TWEN);  // posle data
            while (!(TWCR & (1 << TWINT))) ;  // caka na odoslanie dat
           
            if ((TWSR & 0xF8) == 0x28)  // data odoslane, ACK prijaty
            { }                            
            if ((TWSR & 0xF8) == 0x30)  // data odoslane, NOT ACK prijaty
            { }
          }
          TWCR = (1 << TWEN) | (0 << TWSTA) | (1 << TWSTO) | (1 << TWINT);  // posle stop bit                                    
        }
          
        if ((TWSR & 0xF8) == 0x20)  // SLA+W poslany, NOT ACK prijaty                 
        {
          TWCR = (1 << TWEN) | (0 << TWSTA) | (1 << TWSTO) | (1 << TWINT);  // posle stop bit
        }                                                                                                                           
      }

      if ((TWSR & 0xF8) == 0x48)  // SLA+R odoslana, NOT ACK prijaty
      {
        TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);  // posle stop bit
      }      
    }    
  }
}