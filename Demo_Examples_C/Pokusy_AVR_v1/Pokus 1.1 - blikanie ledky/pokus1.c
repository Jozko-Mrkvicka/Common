#include <mega8.h>
#include <delay.h>

void main (void) {
  DDRC=0xff;  // nastavi port C ako vystupny, ( ff = vystup, 00 = vstup )
  while (1) {
    PORTC=0x00;
    delay_ms(500);
    PORTC=0xff;
    delay_ms(500);
  } 
}