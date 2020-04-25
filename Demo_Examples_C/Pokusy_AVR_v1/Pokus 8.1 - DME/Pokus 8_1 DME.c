#include <mega8.h>
#include <delay.h>

#define Dis1 PORTD.3 
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

void VypniDisplaye(void) {
    Dis1 = 0;
    Dis2 = 0;
    Dis3 = 0;
    Dis4 = 0;
    Dis5 = 0;
    Dis6 = 0;
}
                                                                                                   
void main(void) {
  unsigned char oneskorenie, a, b, c, d, e, f;   
  
  init();    
  oneskorenie = 1;
  
  while (1)                // vlastny multiplexing - postupne pripaja napatia ku displejom 1 az 6
  { 
    if (Tla1 == 0) {
      a = 2; b = 4; c = 1; d = 2; e = 8; f = 3;   // cislo ktore sa zobrazi na displayi
    }  
    else {
      a = '-'; b = '-'; c = '-'; d = 3; e = 7; f = 2;  
    };
    
    if (f == 2) f = 3;      // nefunguje mi segment 1 na displayi 6 :-(, preto z dvojky robi trojku
    
    VypniDisplaye();        // odpoji napajanie od vsetkych displayov
    Dis1 = 1;               // pripoji napajanie ku pozadovanemu displayu
    cislica(a);             // nastavi segmenty displayov na pozadovanu cislicu
    delay_ms(oneskorenie);  // pri i > 5 dochadza ku blikaniu 
      
    VypniDisplaye();
    Dis2 = 1;
    cislica(b);
    delay_ms(oneskorenie);
    
    VypniDisplaye();  
    Dis3 = 1;
    cislica(c);
    delay_ms(oneskorenie);
    
    VypniDisplaye();  
    Dis4 = 1;
    cislica(d);
    delay_ms(oneskorenie);
    
    VypniDisplaye();  
    Dis5 = 1;
    cislica(e);
    delay_ms(oneskorenie);
    
    VypniDisplaye();  
    Dis6 = 1;
    cislica(f);
    delay_ms(oneskorenie);
  }   
}