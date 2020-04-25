#define F_CPU 4000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/twi.h>
#include <stdio.h>
#include <stdlib.h>

#define TWI_MASK_PRESCALER_BITS 0xF8
#define TWI_SLAVE_READ 0x00
#define TWI_SLAVE_WRITE 0x01
#define TWI_SLAVE_ADDRESS_NAV1_DISPLAY ((0x39 << 1) | TWI_SLAVE_READ)

unsigned int counter_1;
int counter_2;

char A, B, C, D, A_last, B_last, C_last, D_last;

// unsigned char TWI_display_message;
// unsigned char TWI_buttons_message;

struct 
{
	int : 1;
	int : 7;
} TCR;



/////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////
void twi_init(void)
{
  	TWBR = 0x08;  // bit rate register - rychlost SCL
	TWCR = (1 << TWINT) | 
		   (1 << TWEN);
}

void twi_generate_start(void)
{
	TWCR |= (1 << TWSTA);
}

void twi_generate_stop(void)
{
	TWCR |= (1 << TWSTA);
}

void twi_wait_until_transmitted(void)
{
	while (!(TWCR & (1 << TWINT)))
		;
}

int twi_is_start_transmitted(void) 
{
	if ((TWSR & TWI_MASK_PRESCALER_BITS) == TW_START)
		return 1;
	else
		return 0;
}

int twi_is_address_W_transmitted(void)
{
	if ((TWSR & TWI_MASK_PRESCALER_BITS) == TW_MT_SLA_ACK)
		return 1;
	else
		return 0;
}

int twi_is_acknowledge_received(void)
{
	if ((TWSR & TWI_MASK_PRESCALER_BITS) == TW_MT_DATA_ACK)
		return 1;
	else
		return 0;
}

void twi_transmit_byte(void)
{
	TWCR |= (1 << TWINT);
}

int twi_transmit_data(unsigned char *array, unsigned char size, unsigned char slave_addr)
{
	unsigned char already_transmitted = 0;
	unsigned char i;

	if (size > 255)
		return already_transmitted;

	twi_generate_start();
	twi_wait_until_transmitted();

	if (twi_is_start_transmitted())
	{
		TWDR = slave_addr;
		twi_transmit_byte();
		twi_wait_until_transmitted();

		if (twi_is_address_W_transmitted())
		{
			for (i = 0; i < size; i++)
			{
				TWDR = array[i];
				twi_transmit_byte();
				twi_wait_until_transmitted();

				if (twi_is_acknowledge_received())
					already_transmitted++;
			}

			twi_generate_stop();
			twi_wait_until_transmitted();
		}
	}

	return already_transmitted;
}

/////////////////////////////////////////////////////////////////////
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
	// unsigned char i;
	// char str[9];

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

	twi_init();

	counter_1 = 5100;
	counter_2 = 9999;

	A_last = ((PIND & 0x01) >> 0);
	B_last = ((PIND & 0x02) >> 1);
	C_last = ((PINB & 0x02) >> 1);
	D_last = ((PINB & 0x04) >> 2);

struct
{
	unsigned char pulse_low_control;
	unsigned char pulse_high_control;

	unsigned char select_control_register;

	unsigned char pulse_low_display;
	unsigned char pulse_high_display;

	unsigned char select_display_register;	

	unsigned char data_byte_1;
	unsigned char pulse_low_1;
	unsigned char pulse_high_1;

	unsigned char data_byte_2;
	unsigned char pulse_low_2;
	unsigned char pulse_high_2;

	unsigned char data_byte_3;
	unsigned char pulse_low_3;
	unsigned char pulse_high_3;

	unsigned char data_byte_4;
	unsigned char pulse_low_4;
	unsigned char pulse_high_4;

	unsigned char data_byte_5;
	unsigned char pulse_low_5;
	unsigned char pulse_high_5;

	unsigned char data_byte_6;
	unsigned char pulse_low_6;
	unsigned char pulse_high_6;

	unsigned char data_byte_7;
	unsigned char pulse_low_7;
	unsigned char pulse_high_7;

	unsigned char data_byte_8;
	unsigned char pulse_low_8;
	unsigned char pulse_high_8;
} display_message;


#define NAV_DISPLAY_MODE_HIGH 0x10
#define NAV_DISPLAY_MODE_LOW 0xEF

#define NAV_DISPLAY_WRITE_HIGH 0x20
#define NAV_DISPLAY_WRITE_LOW 0xDF


display_message.pulse_low_control &= NAV_DISPLAY_WRITE_LOW;
display_message.pulse_high_control |= NAV_DISPLAY_WRITE_HIGH;

display_message.select_control_register |= NAV_DISPLAY_MODE_HIGH;

display_message.pulse_low_display &= NAV_DISPLAY_WRITE_LOW;
display_message.pulse_high_display |= NAV_DISPLAY_WRITE_HIGH;

display_message.select_display_register &= NAV_DISPLAY_MODE_LOW;

display_message.data_byte_1 = 1;
display_message.pulse_low_1 &= NAV_DISPLAY_WRITE_LOW;
display_message.pulse_high_1 |= NAV_DISPLAY_WRITE_HIGH;

display_message.data_byte_2 = 2;
display_message.pulse_low_2 &= NAV_DISPLAY_WRITE_LOW;
display_message.pulse_high_2 |= NAV_DISPLAY_WRITE_HIGH;

display_message.data_byte_3 = 3;
display_message.pulse_low_3 &= NAV_DISPLAY_WRITE_LOW;
display_message.pulse_high_3 |= NAV_DISPLAY_WRITE_HIGH;

display_message.data_byte_4 = 4;
display_message.pulse_low_4 &= NAV_DISPLAY_WRITE_LOW;
display_message.pulse_high_4 |= NAV_DISPLAY_WRITE_HIGH;

display_message.data_byte_5 = 5;
display_message.pulse_low_5 &= NAV_DISPLAY_WRITE_LOW;
display_message.pulse_high_5 |= NAV_DISPLAY_WRITE_HIGH;

display_message.data_byte_6 = 6;
display_message.pulse_low_6 &= NAV_DISPLAY_WRITE_LOW;
display_message.pulse_high_6 |= NAV_DISPLAY_WRITE_HIGH;

display_message.data_byte_7 = 7;
display_message.pulse_low_7 &= NAV_DISPLAY_WRITE_LOW;
display_message.pulse_high_7 |= NAV_DISPLAY_WRITE_HIGH;

display_message.data_byte_8 = 8;
display_message.pulse_low_8 &= NAV_DISPLAY_WRITE_LOW;
display_message.pulse_high_8 |= NAV_DISPLAY_WRITE_HIGH;


    while (1)
    {
		// generate_pulse_driver_1();

		// select_control_register();

		// generate_pulse_driver_1();
 
		// select_display_RAM();

		// // counter_1++;
		// sprintf(str, "%8d", counter_1);
		// for (i = 0; i < 8; i++)
		// {
		// 	data = (str[i]);
		// 	generate_pulse_driver_1();
		// }


		twi_transmit_data((unsigned char*) &display_message, 8, TWI_SLAVE_ADDRESS_NAV1_DISPLAY);


		//

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
