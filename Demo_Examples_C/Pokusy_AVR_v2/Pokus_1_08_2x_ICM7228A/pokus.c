#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>

void generate_pulse_driver_1(void)
{
	// write low
	PORTC &= 0xFE;
	_delay_ms(1);

	// write high;
	PORTC |= 0x01;
	_delay_ms(1);
}

void generate_pulse_driver_2(void)
{
	// write low
	PORTC &= 0xFB;
	_delay_ms(1);

	// write high;
	PORTC |= 0x04;
	_delay_ms(1);
}

void select_control_register(void)
{
	// mode high
	PORTC |= 0x02;
	_delay_ms(1);	
}

void select_display_RAM(void)
{
	// mode low
	PORTC &= 0xFD;
	_delay_ms(1);
}

int main(void) 
{
	char i;
	DDRD = 0xFF;
	DDRC = 0x07;

	generate_pulse_driver_1();

	select_control_register();

	generate_pulse_driver_1();

	select_display_RAM();

	for (i = 0; i < 8; i++)
	{
		// ID0 to ID3 + ID7 for DP (digit 1 to 8)
		PORTD = i;
		_delay_ms(1);

		generate_pulse_driver_1();
	}

	generate_pulse_driver_2();

	select_control_register();

	generate_pulse_driver_2();

	select_display_RAM();

	for (i = 8; i < 16; i++)
	{
		// ID0 to ID3 + ID7 for DP (digit 1 to 8)
		PORTD = i;
		_delay_ms(1);

		generate_pulse_driver_2();
	}


	DDRB = 0xFF;
    while (1)
    {
    	PORTB = 0x00;
		_delay_ms(250);
    	PORTB = 0x01;
		_delay_ms(250);
    }
}
