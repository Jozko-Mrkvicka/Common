#include <mega8.h>
#include <delay.h>

#define DME_ADDRESS 0x02

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
    case '0': c0(); break;
    case '1': c1(); break;
    case '2': c2(); break;
    case '3': c3(); break;
    case '4': c4(); break;
    case '5': c5(); break;
    case '6': c6(); break;
    case '7': c7(); break;
    case '8': c8(); break;
    case '9': c9(); break;
    case '-': cNIC(); break;
  }
} 

void VypniDisplaye(void)  // odpoji napajanie vsetkych displayov 
{  
    Dis1 = 0;
    Dis2 = 0;
    Dis3 = 0;
    Dis4 = 0;
    Dis5 = 0;
    Dis6 = 0;
}

void main(void)
{
  unsigned char hodnota[] = "-1-1-1";
  int i, oneskorenie = 1;
        
  TWAR = DME_ADDRESS;                                                                    
  TWCR = (1 << TWEN) | (1 << TWEA) | (0 << TWSTA) | (0 << TWSTO);  // inicializovany slave mod
   
  init();  
  while (1)
  { 
    if (TWCR & (1 << TWINT))  // caka na prijem svojej adresy
    { 
      switch (TWSR & 0xF8)
      {
        case 0xA8 :  // SLA+R prijata, ACK odoslany
        { 
          if (Tla1 == 0)   // odosle informaciu o polohe prepinaca
            TWDR = '1';      
          else 
            TWDR = '2';
          
          TWCR = (1 << TWEN) | (0 << TWEA) | (1 << TWINT) | (0 << TWSTO);  // TWEA = 0 ... posiela sa posledny bajt
          while (!(TWCR & (1 << TWINT))) ; // caka na odoslanie dat
        
          switch (TWSR & 0xF8)
          {
            case 0xB8 : break;  // data bajt odoslany, ACK prijaty
            case 0xC0 : break;  // data bajt odoslany, NOT ACK prijaty
            case 0xC8 : break;  // posledny bajt odoslany (TWEA = 0), ACK prijaty
          }
                
          TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
          while (!(TWCR & (1 << TWINT))) ; // caka na stop bit            
        } break;
            
        case 0x60 :  // bola prijata adresa SLA+W, ACK odoslany
        { 
          for (i = 0; i <= 5; i++)
          {     
            TWCR = (1 << TWEA) | (1 << TWEN) | (0 << TWSTO) | (1 << TWINT);
            while (!(TWCR & 0x80)) ;  // caka na prijatie dat      
            hodnota[i] = TWDR;
          }
         
          switch (TWSR & 0xF8) 
          { 
            case 0x80 :  // data prijate, ACK odoslany
            {                                                                        
              TWCR = (1 << TWEA) | (1 << TWEN) | (0 << TWSTO) | (1 << TWINT);  // zhodi flag
              while (!(TWCR & 0x80)) ; // caka na stop bit
              if ((TWSR & 0xF8) == 0xA0)  // stop bit alebo repeated start prijaty 
              {                                                      
                TWCR = (1 << TWEA) | (1 << TWEN) | (0 << TWSTA) | (0 << TWSTO) | (1 << TWINT); // zhodi flag
              }
            } break;
           
            case 0x88 :  // data prijate, NOT ACK odoslany 
            {                                                       
              // dostal sa do neadresovaneho slave modu, rozpoznavanie vlastnej SLA adresy zapnute
              TWCR = (1 << TWEA) | (1 << TWEN) | (0 << TWSTA) | (0 << TWSTO);  // zhodi flag          
            } break;
          }                                                                     
        } break;      
      }                         
    }
    if (hodnota[5] == '0') hodnota[5] = '1';  // nefunguje mi segment 1 na displayi 6 :-(,
    if (hodnota[5] == '2') hodnota[5] = '3';  // preto z dvojky robi trojku a z nuly jednotku 
                             
    // vlastny multiplexing - postupne pripaja napatia ku displejom 1 az 6   
    
    VypniDisplaye();        // odpoji napajanie od vsetkych displayov
    Dis1 = 1;               // pripoji napajanie ku pozadovanemu displayu
    cislica(hodnota[0]);    // nastavi segmenty displayov na pozadovanu cislicu
    delay_ms(oneskorenie);  // pri i > 5 dochadza ku blikaniu 
      
    VypniDisplaye();
    Dis2 = 1;
    cislica(hodnota[1]);
    delay_ms(oneskorenie);
    
    VypniDisplaye();  
    Dis3 = 1;
    cislica(hodnota[2]);
    delay_ms(oneskorenie);
    
    VypniDisplaye();  
    Dis4 = 1;
    cislica(hodnota[3]);
    delay_ms(oneskorenie);
    
    VypniDisplaye();  
    Dis5 = 1;
    cislica(hodnota[4]);
    delay_ms(oneskorenie);
    
    VypniDisplaye();  
    Dis6 = 1;
    cislica(hodnota[5]);
    delay_ms(oneskorenie); 
  }
}      