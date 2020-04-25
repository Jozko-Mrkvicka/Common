#define F_CPU 4000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int counter_1;
int counter_2;

char A, B, C, D, A_last, B_last, C_last, D_last;

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

ISR(INT0_vect)
{ 
	counter_1++;

	A = ((PIND & 0x01) >> 0);
	B = ((PIND & 0x02) >> 1);

	C = ((PINB & 0x02) >> 1);
	D = ((PINB & 0x04) >> 2);

	// counter_1 = 0;

/*	if (A_last != A) 
	{
		if (A == 1)
			counter_1 += 1000;
		A_last = A;
	}

	if (B_last != B)
	{
		if (B == 1) 
			counter_1 += 100;
		B_last = B;
	}
	
	if (C_last != C)
	{
		if (C == 1)
			counter_1 += 10;
		C_last = C;
	}

	if (D_last != D)
	{
		if (D == 1)
			counter_1 += 1;
		D_last = D;
	}
*/		

	if ((A != A_last) || (C != C_last))
	{	
		if ((A == 0) && (C == 1)) counter_1++;
		if ((A == 1) && (C == 0)) counter_1++;

		if ((A == 1) && (C == 1)) counter_1--;
		if ((A == 0) && (C == 0)) counter_1--;

		A_last = A;
		C_last = C;
	}	
	
	if ((B != B_last) || (D != D_last))
	{	
		if ((B == 0) && (D == 1)) counter_1 += 1000;
		if ((B == 1) && (D == 0)) counter_1 += 1000;

		if ((B == 1) && (D == 1)) counter_1 -= 1000;
		if ((B == 0) && (D == 0)) counter_1 -= 1000;

		B_last = B;
		D_last = D;
	}

	// if ((A == 0) && (C == 1)) counter_1++;
	// if ((A == 1) && (C == 0)) counter_1++;

	// if ((A == 1) && (C == 1)) counter_1--;
	// if ((A == 0) && (C == 0)) counter_1--;

	// if ((B == 0) && (D == 1)) counter_1++;
	// if ((B == 1) && (D == 0)) counter_1++;

	// if ((B == 1) && (D == 1)) counter_1--;
	// if ((B == 0) && (D == 0)) counter_1--;


}

int main(void) 
{
	unsigned char i;
	char str[9];

	DDRD = 0xF0;
	DDRC = 0x07;
	DDRB = 0xF0;

	SREG |= 0x80;   // 10000000 - povoluje Global Interrupt Enable

	// MCUCR = 0x05;
	MCUCR &= ~(1 << 3); // prerusenie bude reagovat na akukolvek hranu (falling/rising)
	MCUCR |=  (1 << 2);
	MCUCR &= ~(1 << 1);
	MCUCR |=  (1 << 0);

	GICR |= (1 << 7); // external int request 1,2 enabled
	GICR |= (1 << 6); // int0

	// tlacitko
	PORTD |= (1 << 0);
	PORTD |= (1 << 1);
	PORTD |= (1 << 2);
	PORTD |= (1 << 3);

	// tlacitko
	PORTB |= (1 << 1);
	PORTB |= (1 << 2);

	counter_1 = 5100;
	counter_2 = 9999;

	A_last = ((PIND & 0x01) >> 0);
	B_last = ((PIND & 0x02) >> 1);
	C_last = ((PINB & 0x02) >> 1);
	D_last = ((PINB & 0x04) >> 2);

    while (1)
    {
		generate_pulse_driver_1();

		select_control_register();

		generate_pulse_driver_1();
 
		select_display_RAM();

		// counter_1++;
		sprintf(str, "%8d", counter_1);
		for (i = 0; i < 8; i++)
		{
			PORTD = (str[i] << 4);
			generate_pulse_driver_1();
		}

/*
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
*/
		_delay_ms(10);
    }
}
