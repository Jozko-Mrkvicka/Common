#include <mega8.h>
#include <delay.h>
#include <stdio.h>

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

unsigned char pole[6], DME1_DME2, a, b, c, d, e, f;

void InitDisplayeTlacitka(void) {
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

  a = '-'; 
  b = '-'; 
  c = '-'; 
  d = '-'; 
  e = '-'; 
  f = '-';
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
  switch (i) {                   // rozhodne aky znak sa ma zobrazit a podla toho nastavy 
    case '0': c0(); break;       // vystupne piny - segmenty displayov
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
/*    
    default:                     // iba pre testovacie ucely - v pripade ze bajt
        Seg10 = i & 0x1;         // nie je mozne rozpoznat, tak z neho vykresli aspon 
        Seg1 = (i>>1) & 0x1;     // 6 bitov
        Seg2 = (i>>2) & 0x1;
        Seg4 = (i>>3) & 0x1;
        Seg6 = (i>>4) & 0x1;
        Seg7 = (i>>5) & 0x1;
        Seg9 = (i>>6) & 0x1;
        break;
*/
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

interrupt [12] void USART_RX_Hotovo(void) 
{ 
  gets(pole, 6);      // prerusenie sa zavola v pripade ze linka Rx detekuje signal,
  a = pole[0];        // to znamena ze USART prijal znak,
  b = pole[1];        // do "pola" sa ulozi 6 prijatych znakov 
  c = pole[2];   
  d = pole[3];
  e = pole[4];
  f = pole[5];      
}
                                                                                            
void main(void) 
{
  int oneskorenie = 1;  
    
/*  
  // USART initialization
  // Communication Parameters: 8 Data, 1 Stop, No Parity
  // USART Receiver: On
  // USART Transmitter: On
  // USART Mode: Asynchronous
  // USART Baud Rate: 9600
*/  
  SREG = 0x80;   // 10000000 - povoluje Global Interrupt Enable
  UCSRA = 80;    // 10000000 - generuje Recieve Complete Interrupt  
  UCSRB=0x98;    // 10011000 - povolenie prerusenia na USART Rx   
  UCSRC=0x86;
  UBRRH=0x00;
  UBRRL=25;      // 00011001 
  
  InitDisplayeTlacitka(); 
  while (1)                          
  {   
    if (Tla1 == 0)          // ked je spinac v hornej polohe, zariadenie zobrazuje udaje 
      DME1_DME2 = '1';      // z 1. priimaca DME, v dolnej polohe z 2. priimaca
    else 
      DME1_DME2 = '2';
    
    if (f == '2') f = '3';  // nefunguje mi segment 1 na displayi 6 :-(, 
                            // preto z dvojky robi trojku
 
    // vlastny multiplexing - postupne pripaja napatia ku displejom 1 az 6   
    
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