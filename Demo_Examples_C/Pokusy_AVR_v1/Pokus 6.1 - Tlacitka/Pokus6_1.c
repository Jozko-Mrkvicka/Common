/* 
  Dioda je pripojena medzi pin C5 (5V) a zem (0V), 
  tlacitko je pripojene medzi pin B1 (0V) a 5V,
  dioda svieti kym nie je stisnute tlacitko 
*/
#include <mega8.h>
/*
void main(void) {
  DDRB.1 = 0;    // port B inicializovany ako vstupny
  DDRC.5 = 1;    // port C inicializovany ako vystupny
  
  PORTB.1 = 0;

  while (1) {                                 
    if (PINB.1 == 0) PORTC.5 = 1;  // svieti
    if (PINB.1 == 1) PORTC.5 = 0;  // nesvieti 
  }
}
*/

void main(void) {
  DDRB.1 = 0;    // port B inicializovany ako vstupny
  DDRC.5 = 1;    // port C inicializovany ako vystupny
  
  PORTB.1 = 1;

  while (1) {                                 
    if (PINB.1 == 1) PORTC.5 = 1;  // svieti
    if (PINB.1 == 0) PORTC.5 = 0;  // nesvieti 
  }
}
 