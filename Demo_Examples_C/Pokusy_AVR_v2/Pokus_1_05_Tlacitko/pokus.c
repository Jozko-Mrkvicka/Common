#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

char c;
bool stlacene = false;
int oneskorenie = 1;

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

	// tlacitko
	DDRB &= (0 << 0);
	PORTB = (1 << 0);

	c = 0x08;
    while (1)
    {

		if ((PINB & 0x01) == 1)
			stlacene = false;

    	if (((PINB & 0x01) == 0) && (!stlacene))
    	{
    		stlacene = true;

			if (c < 0x09)
				c++;
			else
				c = 0x00;
		}

		PORTD = 0x0F;
		PORTC = 0x00;
		PORTD = c;
		_delay_ms(oneskorenie);

		PORTD = 0x0F;
		PORTC = 0x01;
		PORTD = 0x09;
		_delay_ms(oneskorenie);

		PORTD = 0x0F;
		PORTC = 0x02;
		PORTD = 0x05;
		_delay_ms(oneskorenie);

		PORTD = 0x0F;
		PORTC = 0x03;
		PORTD = 0x04;
		_delay_ms(oneskorenie);

		PORTD = 0x0F;
		PORTC = 0x04;
		PORTD = 0x01;
		_delay_ms(oneskorenie);
    }
}
