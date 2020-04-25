#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

void generate_pulse_driver_1(void)
{
	// write low
	PORTC &= 0xFE;

	// write high;
	PORTC |= 0x01;
}

void generate_pulse_driver_2(void)
{
	// write low
	PORTC &= 0xFB;

	// write high;
	PORTC |= 0x04;
}

void select_control_register(void)
{
	// mode high
	PORTC |= 0x02;
}

void select_display_RAM(void)
{
	// mode low
	PORTC &= 0xFD;
}


int main(void) 
{
	char i;
	int counter_1;
	int counter_2;
	char str[9];

	DDRD = 0xFF;
	DDRC = 0x07;
	DDRB = 0xFF;


	counter_1 = 0;
	counter_2 = 9999;
    while (1)
    {
		generate_pulse_driver_1();

		select_control_register();

		generate_pulse_driver_1();

		select_display_RAM();

		counter_1++;
		sprintf(str, "%5d000", counter_1);

		for (i = 0; i < 8; i++)
		{
			PORTD = str[i];
			generate_pulse_driver_1();
		}

		generate_pulse_driver_2();

		select_control_register();

		generate_pulse_driver_2();

		select_display_RAM();

		counter_2--;
		sprintf(str, "%4d0000", counter_2);

		for (i = 0; i < 8; i++)
		{
			PORTD = str[i];
			generate_pulse_driver_2();
		}

		_delay_ms(1000);
    }
}
