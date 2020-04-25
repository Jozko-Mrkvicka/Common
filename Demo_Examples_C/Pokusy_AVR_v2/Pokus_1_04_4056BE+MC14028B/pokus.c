#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void) 
{

	// segmenty
	DDRD |= (1 << 0);
	DDRD |= (1 << 1);
	DDRD |= (1 << 2);
	DDRD |= (1 << 3);

	// napajania
	DDRC |= (1 << 0);
	DDRC |= (1 << 1);
	DDRC |= (1 << 2);

    while (1)
    {
		PORTC = 0x00;
	    PORTD = 0x05;
	    _delay_ms(1);

		PORTC = 0x01;
		PORTD = 0x06;
		_delay_ms(1);

		PORTC = 0x02;
		PORTD = 0x07;
		_delay_ms(1);

		PORTC = 0x03;
		PORTD = 0x08;
		_delay_ms(1);

		PORTC = 0x04;
		PORTD = 0x09;
        _delay_ms(1);
    }
}
