/*
	Zapoj ATmega8 s krystalom 4MHz (2x keramicky kondenzator 22[p/n ???], 
	1x elektrolyticky kondenzator 47uF medzi napajanie +/-). 
	Port C (PC0 az PC3) pripoj na 4056BE (piny 2 az 5, pozor na poradie!).
	Ku 4056BE pripoj 7-segmentovy display.
*/

#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void) 
{
	DDRC |= (1 << 0);
	DDRC |= (1 << 1);
	DDRC |= (1 << 2);
	DDRC |= (1 << 3);

    while (1)
    {
		PORTC = 0x00;
	    _delay_ms(500);

		PORTC = 0x01;
		_delay_ms(500);

		PORTC = 0x02;
		_delay_ms(500);

		PORTC = 0x03;
		_delay_ms(500);

		PORTC = 0x04;
        _delay_ms(500);
    }
}
