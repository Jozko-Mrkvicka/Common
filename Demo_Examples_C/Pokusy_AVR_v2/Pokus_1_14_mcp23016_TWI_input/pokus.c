#define F_CPU 4000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/twi.h>
#include <stdio.h>
#include <stdlib.h>

#define TWI_SLAVE_ADDRESS_NAV1_DISPLAY ((0x20 << 1) | TW_WRITE)

/////////////////////////////////////////////////////////////////////
void twi_init(void)
{
	// set frequency of TWI SCL line
  	TWBR = 0x08;  // bit rate register
	TWSR = 0xFC;  // status register - prescaler bits
}

void twi_generate_start(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (0 << TWSTO) | (1 << TWEN);
}

void twi_generate_stop(void)
{
    TWCR = (1 << TWINT) | (0 << TWSTA) | (1 << TWSTO) | (1 << TWEN);
}

void twi_transmit_byte(void)
{
    TWCR = (1 << TWINT) | (0 << TWSTA) | (0 << TWSTO) | (1 << TWEN);
}

void twi_wait_until_transmitted(void)
{
	while (!(TWCR & (1 << TWINT)))
		;
}

int twi_is_start_transmitted(void) 
{
	if (TW_STATUS == TW_START)
		return 1;
	else
		return 0;
}

int twi_is_address_W_transmitted(void)
{
	if (TW_STATUS == TW_MT_SLA_ACK)
		return 1;
	else
		return 0;
}

int twi_is_data_acknowledge_received(void)
{
	if (TW_STATUS == TW_MT_DATA_ACK)
		return 1;
	else
		return 0;
}

int twi_transmit_data(unsigned char *data, int size, unsigned char slave_addr)
{
	int already_transmitted = 0;
	int i;

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
				TWDR = data[i];
				twi_transmit_byte();
				twi_wait_until_transmitted();

				if (twi_is_data_acknowledge_received())
					already_transmitted++;
			}
			twi_generate_stop();
		}
	}
	return already_transmitted;
}


void generate_pulse_driver_1(void)
{
	// write low
	PORTD &= 0xEF;

	// write high;
	PORTD |= 0x10;

}

void select_control_register(void)
{
	// mode high
	PORTD |= 0x20;
}

void select_display_RAM(void)
{
	// mode low
	PORTD &= 0xDF;
}


int main(void) 
{
_delay_ms(500);
	char j = 0;


struct
{
	unsigned char pulse_low_control;
	unsigned char pulse_high_control;
	unsigned char select_control_register;

	unsigned char pulse_low_display;
	unsigned char pulse_high_display;
	unsigned char select_display_register;	

	unsigned char data_byte_1;
	unsigned char pulse_high_1;

	unsigned char data_byte_2;
	unsigned char pulse_high_2;

	unsigned char data_byte_3;
	unsigned char pulse_high_3;

	unsigned char data_byte_4;
	unsigned char pulse_high_4;

	unsigned char data_byte_5;
	unsigned char pulse_high_5;

	unsigned char data_byte_6;
	unsigned char pulse_high_6;

	unsigned char data_byte_7;
	unsigned char pulse_high_7;

	unsigned char data_byte_8;
	unsigned char pulse_high_8;
} display_message;

display_message.pulse_low_control = 0;
display_message.pulse_high_control = 0;
display_message.pulse_low_display = 0;
display_message.pulse_high_display = 0;
display_message.select_control_register = 0;
display_message.select_display_register = 0;
display_message.pulse_high_1 = 0;
display_message.pulse_high_2 = 0;
display_message.pulse_high_3 = 0;
display_message.pulse_high_4 = 0;
display_message.pulse_high_5 = 0;
display_message.pulse_high_6 = 0;
display_message.pulse_high_7 = 0;
display_message.pulse_high_8 = 0;

	// DDRD = 0xFF;
  	twi_init();

#define NAV_DISPLAY_MODE_HIGH 0x20
#define NAV_DISPLAY_MODE_LOW 0xDF
	// mode high
	// PORTB |= 0x02;
	// PORTD |= 0x20;

	// mode low
	// PORTB &= 0xFD;
	// PORTD &= 0xDF;

#define NAV_DISPLAY_WRITE_HIGH 0x10
#define NAV_DISPLAY_WRITE_LOW 0xEF
	// write low
	// PORTB &= 0xFE;
	// PORTD &= 0xEF;

	// write high;
	// PORTB |= 0x01;
	// PORTD |= 0x10;


    while (1)
    {
    	j++;
    	// j = 5;

    	if (j > 9)
    		j = 0;

display_message.pulse_low_control = NAV_DISPLAY_WRITE_LOW;
// PORTD = display_message.pulse_low_control;
display_message.pulse_high_control = NAV_DISPLAY_WRITE_HIGH;
// PORTD = display_message.pulse_high_control;
display_message.select_control_register = NAV_DISPLAY_MODE_HIGH;
// PORTD |= display_message.select_control_register;

display_message.pulse_low_display = NAV_DISPLAY_WRITE_LOW;
// PORTD = display_message.pulse_low_display;
display_message.pulse_high_display = NAV_DISPLAY_WRITE_HIGH;
// PORTD = display_message.pulse_high_display;
display_message.select_display_register = NAV_DISPLAY_MODE_LOW;
// PORTD &= display_message.select_display_register;


display_message.data_byte_1 = 3 & NAV_DISPLAY_WRITE_LOW;
// PORTD = display_message.data_byte_1;
display_message.pulse_high_1 = /*8 |*/ NAV_DISPLAY_WRITE_HIGH;
// PORTD = display_message.pulse_high_1;

display_message.data_byte_2 = j & NAV_DISPLAY_WRITE_LOW;
// PORTD = display_message.data_byte_2;
display_message.pulse_high_2 = /*j |*/ NAV_DISPLAY_WRITE_HIGH;
// PORTD = display_message.pulse_high_2;

display_message.data_byte_3 = j & NAV_DISPLAY_WRITE_LOW;
// PORTD = display_message.data_byte_3;
display_message.pulse_high_3 = /*j |*/ NAV_DISPLAY_WRITE_HIGH;
// PORTD = display_message.pulse_high_3;

display_message.data_byte_4 = j & NAV_DISPLAY_WRITE_LOW;
// PORTD = display_message.data_byte_4;
display_message.pulse_high_4 = /*j |*/ NAV_DISPLAY_WRITE_HIGH;
// PORTD = display_message.pulse_high_4;

display_message.data_byte_5 = j & NAV_DISPLAY_WRITE_LOW;
// PORTD = display_message.data_byte_5;
display_message.pulse_high_5 = /*j |*/ NAV_DISPLAY_WRITE_HIGH;
// PORTD = display_message.pulse_high_5;

display_message.data_byte_6 = j & NAV_DISPLAY_WRITE_LOW;
// PORTD = display_message.data_byte_6;
display_message.pulse_high_6 = /*j |*/ NAV_DISPLAY_WRITE_HIGH;
// PORTD = display_message.pulse_high_6;

display_message.data_byte_7 = j & NAV_DISPLAY_WRITE_LOW;
// PORTD = display_message.data_byte_7;
display_message.pulse_high_7 = /*j |*/ NAV_DISPLAY_WRITE_HIGH;
// PORTD = display_message.pulse_high_7;

display_message.data_byte_8 = j & NAV_DISPLAY_WRITE_LOW;
// PORTD = display_message.data_byte_8;
display_message.pulse_high_8 = /*j |*/ NAV_DISPLAY_WRITE_HIGH;
// PORTD = display_message.pulse_high_8;

		unsigned char at = twi_transmit_data((unsigned char *)&display_message, 22, TWI_SLAVE_ADDRESS_NAV1_DISPLAY);
		/*
		if (at == 22)
			at = 1;
		else
			at = 2;
*/
		// twi_transmit_data((unsigned char *)&at, 1, TWI_SLAVE_ADDRESS_NAV1_DISPLAY);
		_delay_ms(500);
    }
}
