#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>

void set_control_word(void)
{
	// ID4 (shutdown) high = normal operation
	PORTD |= 0x10;

	// ID5 (decode) low = decode
	PORTD &= 0xDF;

	// ID6 (hexa/code B) high = hexadecimal decoding 
	PORTD |= 0x40;

	// ID7 (data coming) high = data coming
	PORTD |= 0x80;

	// write low = send control word
	PORTC &= 0xFE;
	_delay_ms(1);

	// write high;
	PORTC |= 0x01; 
	_delay_ms(1);

}

int main(void) 
{
	DDRD = 0xFF;
	DDRC = 0x03;

	// write high;
	PORTC |= 0x01; 
	_delay_ms(1);

	// mode high = select control register
	PORTC |= 0x02;
	_delay_ms(1);	

	set_control_word();

	// mode low = select display RAM
	PORTC &= 0xFD;
	_delay_ms(1);

	char i;
	for (i = 0; i < 8; i++)
	{
		// ID0 to ID3 + ID7 for DP (digit 1 to 8)
		PORTD = i;
		_delay_ms(1);

		// write low = send data word
		PORTC &= 0xFE;
		_delay_ms(1);

		// write high;
		PORTC |= 0x01; 
		_delay_ms(1);
	}

	DDRB = 0xFF;
    while (1)
    {
    	PORTB = 0X00;
		_delay_ms(500);
    	PORTB = 0X01;
		_delay_ms(500);
    }
}
