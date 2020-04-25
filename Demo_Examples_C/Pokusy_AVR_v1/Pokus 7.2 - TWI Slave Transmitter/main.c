#include <mega8.h>
#include <delay.h>

#define I2C_MY_ADDRESS 0x02

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

#define Tla1 PIND.2

void init(void) {  
  DDRD.3 = 1;
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
  unsigned char data = 9;
        
  TWAR = I2C_MY_ADDRESS;                                                                    
  TWCR = (1 << TWEN) | (1 << TWEA) | (0 << TWSTA) | (0 << TWSTO);  // inicializuje slave mod
   
  init();  
  Dis1 = 1;                
  cislica(0); delay_ms(1000);
  while (1)
  {     
    while (!(TWCR & (1 << TWINT))) ; // caka na prijem svojej adresy

    if ((TWSR & 0xF8) == 0xA8)  // SLA+R prijata, ACK odoslany 
    {
      cislica(1); //delay_ms(1000);
      TWDR = data;
      TWCR = (1 << TWEN) | (0 << TWEA) | (1 << TWINT) | (0 << TWSTO);  // TWEA = 0 ... posiela sa posledny bajt
      while (!(TWCR & (1 << TWINT))) ; // caka na odoslanie dat
      
      if ((TWSR & 0xF8) == 0xB8)  // data bajt odoslany, ACK prijaty
      {
        cislica(2); //delay_ms(1000);
      }       
      
      if ((TWSR & 0xF8) == 0xC0)  // data bajt odoslany, NOT ACK prijaty
      {
        cislica(3); //delay_ms(1000);
      }
      
      if ((TWSR & 0xF8) == 0xC8)  // posledny bajt odoslany (TWEA = 0), ACK prijaty
      {
        cislica(4); //delay_ms(1000);        
      }
       
      TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT) | (0 << TWSTO) | (0 << TWSTA);
      while (!(TWCR & (1 << TWINT))) ; // caka na stop bit            
    }
  }                  
}