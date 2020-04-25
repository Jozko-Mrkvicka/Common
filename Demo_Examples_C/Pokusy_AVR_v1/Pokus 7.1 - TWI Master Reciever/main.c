#include <mega8.h>
#include <delay.h>

#define DME_ADDRESS_SR 0x02;  // slave reciever, master transmitter
#define DME_ADDRESS_ST 0x03;  // slave transmitter, master reciever

#define Dis1 PORTD.3   // portom MCU su priradene 'inteligentne' nazvy
#define Dis2 PORTD.4 
#define Dis3 PORTD.5
#define Dis4 PORTD.6
#define Dis5 PORTD.7
#define Dis6 PORTB.0

#define Seg1 PORTB.1
#define Seg2 PORTB.2
#define Seg4 PORTB.3
#define Seg6 PORTB.4
#define Seg7 PORTB.5
#define Seg9 PORTC.0
#define Seg10 PORTC.1

void init(void) {
  DDRD.3 = 1;                      // piny D3 az D7 nastavene ako vystupne
  DDRD.4 = 1;
  DDRD.5 = 1;
  DDRD.6 = 1;
  DDRD.7 = 1;
  
  DDRB.0 = 1;                      // piny B0 az B5 nastavene ako vystupne 
  DDRB.1 = 1;
  DDRB.2 = 1;
  DDRB.3 = 1;
  DDRB.4 = 1;
  DDRB.5 = 1;
  
  DDRC.0 = 1;                      // piny C0 a C1 nastavene ako vystupne
  DDRC.1 = 1;

  DDRD.2 = 0;                      // pin D2 nastaveny na vstup
  PORTD.2 = 1;                     // na vstupnom pine je v kludovom stave 1 (5V) - spina sa do zeme 
}

void c0(void) {  
    Seg10 = 1; Seg1 = 0; Seg2 = 0; Seg4 = 0; Seg6 = 0; Seg7 = 0; Seg9 = 0; // nula
  }
void c1(void) {  
    Seg10 = 1; Seg1 = 1; Seg2 = 1; Seg4 = 0; Seg6 = 0; Seg7 = 1; Seg9 = 1; // jeden
  }
void c2(void) {  
    Seg10 = 0; Seg1 = 0; Seg2 = 0; Seg4 = 1; Seg6 = 0; Seg7 = 0; Seg9 = 1; // dva
  }
void c3(void) {  
    Seg10 = 0; Seg1 = 1; Seg2 = 0; Seg4 = 0; Seg6 = 0; Seg7 = 0; Seg9 = 1; // tri
  }
void c4(void) {  
    Seg10 = 0; Seg1 = 1; Seg2 = 1; Seg4 = 0; Seg6 = 0; Seg7 = 1; Seg9 = 0; // styri
  }
void c5(void) {  
    Seg10 = 0; Seg1 = 1; Seg2 = 0; Seg4 = 0; Seg6 = 1; Seg7 = 0; Seg9 = 0; // pat
  }
void c6(void) {  
    Seg10 = 0; Seg1 = 0; Seg2 = 0; Seg4 = 0; Seg6 = 1; Seg7 = 0; Seg9 = 0; // sest
  }
void c7(void) {  
    Seg10 = 1; Seg1 = 1; Seg2 = 1; Seg4 = 0; Seg6 = 0; Seg7 = 0; Seg9 = 1; // sedem
  }
void c8(void) {  
    Seg10 = 0; Seg1 = 0; Seg2 = 0; Seg4 = 0; Seg6 = 0; Seg7 = 0; Seg9 = 0; // osem
  }
void c9(void) {  
    Seg10 = 0; Seg1 = 1; Seg2 = 0; Seg4 = 0; Seg6 = 0; Seg7 = 0; Seg9 = 0; // devat
  }
void cNIC(void) {
    Seg10 = 0; Seg1 = 1; Seg2 = 1; Seg4 = 1; Seg6 = 1; Seg7 = 1; Seg9 = 1; // '-', nic, pomlcka  
  }

void cislica(unsigned char i) {     
  switch (i) {
    case 0: c0(); break;
    case 1: c1(); break;
    case 2: c2(); break;
    case 3: c3(); break;
    case 4: c4(); break;
    case 5: c5(); break;
    case 6: c6(); break;
    case 7: c7(); break;
    case 8: c8(); break;
    case 9: c9(); break;
    case '-': cNIC(); break;
  }
} 

void main(void)
{
  unsigned char data = '-';
     
  init(); 
  Dis1 = 1;
  cislica(0); delay_ms(1000);
  while (1) 
  {   
    TWCR = (1 << TWEN) | (1 << TWSTA) | (0 << TWSTO) | (1 << TWINT);  // generuje start
    while (!(TWCR & (1 << TWINT)));  // caka na odoslanie start bitu   

    if ((TWSR & 0xF8) == 0x08)  // start bol odoslany
    {
      cislica(1); //delay_ms(100);
      TWDR = DME_ADDRESS_ST;  // nahraje adresu slejva
      TWCR = (1 << TWEN) | (0 << TWSTA) | (0 << TWSTO) | (1 << TWINT);  // odosle adresu 
      while (!(TWCR & (1 << TWINT)));  // caka na odoslanie adresy
      
      if ((TWSR & 0xF8) == 0x40)  // SLA+R odoslana, ACK prijaty
      {                          
        //cislica(2); //delay_ms(50);
        // TWEA = 0 znamena ze sa ocakava prijatie posledneho bajtu
        TWCR = (1 << TWEN) | (0 << TWSTA) | (0 << TWSTO) | (1 << TWINT) | (0 << TWEA);  
        while (!(TWCR & (1 << TWINT)));  // caka na prijatie dat
        data = TWDR;   //ulozi prijate data                 
        
        if ((TWSR & 0xF8) == 0x50)  // data prijate, ACK odoslany
        { 
          //cislica(3); delay_ms(50);
          cislica(data); delay_ms(50);
        }                                                        

        if ((TWSR & 0xF8) == 0x58)  // data prijate, NOT ACK odoslany
        {
          //cislica(4); delay_ms(50);
          cislica(data); delay_ms(50);
        }                                                        
        
        TWCR = (1 << TWEN) | (0 << TWSTA) | (1 << TWSTO) | (1 << TWINT);  // posle stop bit
      }

      if ((TWSR & 0xF8) == 0x48)  // SLA+R odoslana, NOT ACK prijaty
      {
        cislica(5); delay_ms(1000);  // tu by sa to nemalo dostat, preto velky delay
      }
    }                                                                   
  }
}