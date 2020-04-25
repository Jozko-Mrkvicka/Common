#include <avr/io.h>

void delay(unsigned int num) 
{
  unsigned int i,j;
  for (j = 0; j < 1000; j++)
    for (i = 0; i < num; i++)
      ;
}

int main (void)
{
  DDRB |= _BV(PB0); // DDR = "Data Direction Register"
  
  while (1) 
  {
    PORTB &= ~(_BV(PB0));
    delay(500);

    PORTB |= _BV(PB0);
    delay(500);
  }
	
  return 0;
}
