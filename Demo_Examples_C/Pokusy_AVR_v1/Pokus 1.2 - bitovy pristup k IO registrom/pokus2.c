#include <mega8.h>
#include <delay.h>

void main (void) 
{
  int oneskorenie = 10;

  DDRB.1 = 1;    // nastavi bit 7 na porte B ako vystup (o = vstup, 1 = vystup)
  
  DDRD = 0;      // nastavi cely port D ako vstup
  PORTD = 0xFF;  // na vstupnom pine je v kludovom stave 1 (5V) - spina sa do zeme 
  
  while (1)
  {
    if (PIND.5 == 0) 
      oneskorenie = 50;
    else               
      oneskorenie = 250;
      
    PORTB.1 = 0;
    delay_ms(oneskorenie);     
    PORTB.1 = 1;
    delay_ms(oneskorenie);  
  }  
}