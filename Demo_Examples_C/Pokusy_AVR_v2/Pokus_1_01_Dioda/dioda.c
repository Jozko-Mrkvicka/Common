// #define __AVR_ATmega8__
#define __OPTIMIZE__
#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>

int main (void) 
{
	// nastavi port C ako vystupny, ( ff = vystup, 00 = vstup )
	DDRB = 0xff;  
 	while (1) 
 	{
    	PORTB = 0x00;
    	_delay_ms(500);

    	PORTB = 0xff;
    	_delay_ms(500);
	}

	return 0;
}
