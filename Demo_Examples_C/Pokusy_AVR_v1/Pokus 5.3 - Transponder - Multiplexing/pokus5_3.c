#include <mega8.h>
#include <delay.h>

#define Dis1 PORTD.7 
#define Dis2 PORTB.0 
#define Dis3 PORTB.2
#define Dis4 PORTB.1

#define Seg1 PORTC.1
#define Seg2 PORTC.2
#define Seg4 PORTC.3
#define Seg6 PORTB.3
#define Seg7 PORTB.4
#define Seg9 PORTB.5
#define Seg10 PORTC.0

void init(void) {
  DDRD.7 = 1;  // port D7 nastaveny ako vystupny
  
  DDRB.0 = 1;  // porty B0 az B5 nastavene ako vystupne 
  DDRB.1 = 1;
  DDRB.2 = 1;
  DDRB.3 = 1;
  DDRB.4 = 1;
  DDRB.5 = 1;
  
  DDRC.0 = 1;  // porty C0 az C3 nastavene ako vystupne
  DDRC.1 = 1;
  DDRC.2 = 1;
  DDRC.3 = 1;
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

void cislica(int i) {     
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
  }
} 

void VypniDisplaye(void)  // odpoji napajanie vsetkych displayov 
{  
    Dis1 = 0;
    Dis2 = 0;
    Dis3 = 0;
    Dis4 = 0;
}

void main(void)
{              
  int oneskorenie = 5;
  unsigned char hodnota[] = "1234";
  
  init();
  while (1)     // vlastny multiplexing - postupne pripaja napatia ku displejom 1 az 4
    { 
       
      VypniDisplaye();
      Dis1 = 1;
      cislica(hodnota[0]);            // nastavi segmenty displayou na pozadovanu cislicu
      delay_ms(oneskorenie);          // pri i > 5 dochadza ku blikaniu
       
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
    }
}