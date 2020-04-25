/*
	Zapoj ATmega8 s krystalom 4MHz (2x keramicky kondenzator 22[p/n ???], 
	1x elektrolyticky kondenzator 47uF medzi napajanie +/-). 
	Port C (PC0 az PC3) pripoj na 4056BE (piny 2 az 5, pozor na poradie!).
	Ku 4056BE pripoj 7-segmentovy display.
*/

#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// char input = 0x00;
// int interrupt = 0;
char i = 0;

ISR (INT0_vect)
{
	// input = PIND;
	// interrupt = 1;

	if ((PIND & 0x01) == 1)
		i++;
	else
		i--;

	if (i > 9)
		i = 0;

	if (i < 0)
		i = 9;

	PORTC = i;
}

int main(void) 
{

	// char A, B;

	// Global Interrupt enabled
	sei();
	// Status Register
	// SREG |= (1 << I);

	// General Interrupt Control Register - INT0 enable
	GICR |= (1 << INT0);

	// MCU Control Register
	//
	// 7  6   5   4   3     2     1     0
	// SE SM2 SM1 SM0 ISC11 ISC10 ISC01 ISC00
	//
	// 0 0 - The low level of INT0 generates an interrupt request.
	// 0 1 - Any logical change on INT0 generates an interrupt request.
	// 1 0 - The falling edge of INT0 generates an interrupt request.
	// 1 1 - The rising edge of INT0 generates an interrupt request.	
	MCUCR |=  (1 << ISC01);
	MCUCR &= ~(1 << ISC00);

	// Data Direction Register C - set as output
	DDRC = 0x0F;

	// Data Direction Register D - set as input
	DDRD = 0x00;

    while (1)
    {
  //   	if (interrupt == 1)
  //   	{
	 //    	A = (input & 0x08) >> 3; 
	 //    	B = (input & 0x01) >> 0;

		// 	if ((B == 0) && (A == 1)) i++;
		// 	if ((B == 1) && (A == 0)) i++;

		// 	if ((B == 1) && (A == 1)) i--;
		// 	if ((B == 0) && (A == 0)) i--;

		// 	interrupt = 0;
		// }
    	// ak prisiel pulz ...
    	// if ((input & 0x01) == 0)
    	// {
    	// 	// ak tocim do jednej strany ...
    	// 	if ((input & 0x02) == 0)
    	// 		i--;
    	// 	else
    	// 		i++;
    	// }


    	// i = (input & 0x03);

	    // _delay_ms(2);
    }
	return 0;
}
