#include <mega8.h>

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

void main(void) {

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

  Dis1 = 1;  // napajania displejov nastavene na 1 (5V)
  Dis2 = 1;
  Dis3 = 1;
  Dis4 = 1;
  
  Seg1 = 0;  // segmenty nastavene na 0 (0V) - vsetky su rozsvietene
  Seg2 = 0;
  Seg4 = 0;
  Seg6 = 0;
  Seg7 = 0;
  Seg9 = 0;
  Seg10 = 0;
  
  while (1) {
  }
}