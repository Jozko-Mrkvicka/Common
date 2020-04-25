#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>

int c;
// bool stlacene = false;
int oneskorenie = 1;

ISR (INT0_vect)
{
	if ((PIND & 0x02) == 1)
		c++;
	else
		c--;

	if (c > 0x09)
		c = 0x00;

	if (c < 0x00)
		c = 0x09;
}

int main(void) 
{
	// segmenty
	DDRB |= (1 << 0);
	DDRB |= (1 << 1);
	DDRB |= (1 << 2);
	DDRB |= (1 << 3);

	// napajania
	DDRC |= (1 << 0);
	DDRC |= (1 << 1);
	DDRC |= (1 << 2);

	// enkoder
	DDRD &= (0 << 1);
	DDRD &= (0 << 2);
	PORTD |= (1 << 1);
	PORTD |= (1 << 2);

	// global interrupt enable
	sei();
	// SREG |= (1 << I);

	// INT0 enable
	GICR |= (1 << INT0);

	// nabezna hrana na pine INT0 vyvola prerusenie
	MCUCR |= (1 << ISC00);
	MCUCR |= (1 << ISC01);

    while (1)
    {

		PORTB = 0x0F;
		PORTC = 0x00;
		PORTB = c;
		_delay_ms(oneskorenie);

		PORTB = 0x0F;
		PORTC = 0x01;
		PORTB = 0x09;
		_delay_ms(oneskorenie);

		PORTB = 0x0F;
		PORTC = 0x02;
		PORTB = 0x05;
		_delay_ms(oneskorenie);

		PORTB = 0x0F;
		PORTC = 0x03;
		PORTB = 0x04;
		_delay_ms(oneskorenie);

		PORTB = 0x0F;
		PORTC = 0x04;
		PORTB = 0x01;
		_delay_ms(oneskorenie);
    }
}
