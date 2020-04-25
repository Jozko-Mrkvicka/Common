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

				if (twi_is_data_acknowledge_received())
					already_transmitted++;
			}
			twi_generate_stop();
		}
	}
	return already_transmitted;
}

int main(void) 
{
  	#define SLAVE_ADDRESS_SR 0x40
  	DDRD = 0xFF;

	// struct
	// {
	// 	unsigned char byte_0;
	// 	unsigned char byte_1;
	// 	unsigned char byte_2;
	// 	unsigned char byte_3;
	// } data;

	// data.byte_0 = 0;
	// data.byte_1 = 1;
	// data.byte_2 = 2;
	// data.byte_3 = 3;

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

display_message.pulse_low_control = 0;
display_message.pulse_high_control = 0;
display_message.pulse_low_display = 0;
display_message.pulse_high_display = 0;
display_message.select_control_register = 0;
display_message.select_display_register = 0;
display_message.pulse_low_1 = 0;
display_message.pulse_low_2 = 0;
display_message.pulse_low_3 = 0;
display_message.pulse_low_4 = 0;
display_message.pulse_low_5 = 0;
display_message.pulse_low_6 = 0;
display_message.pulse_low_7 = 0;
display_message.pulse_low_8 = 0;
display_message.pulse_high_1 = 0;
display_message.pulse_high_2 = 0;
display_message.pulse_high_3 = 0;
display_message.pulse_high_4 = 0;
display_message.pulse_high_5 = 0;
display_message.pulse_high_6 = 0;
display_message.pulse_high_7 = 0;
display_message.pulse_high_8 = 0;

  	// twi_init();

	while (1) 
	{   
		
display_message.pulse_low_control = NAV_DISPLAY_WRITE_LOW;
PORTD &= display_message.pulse_low_control;
display_message.pulse_high_control = NAV_DISPLAY_WRITE_HIGH;
PORTD |= display_message.pulse_high_control;

display_message.select_control_register = NAV_DISPLAY_MODE_HIGH;
PORTD |= display_message.select_control_register;

display_message.pulse_low_display = NAV_DISPLAY_WRITE_LOW;
PORTD &= display_message.pulse_low_display;
display_message.pulse_high_display = NAV_DISPLAY_WRITE_HIGH;
PORTD |= display_message.pulse_high_display;

display_message.select_display_register = NAV_DISPLAY_MODE_LOW;
PORTD &= display_message.select_display_register;

display_message.data_byte_1 = 7;
PORTD = display_message.data_byte_1;
display_message.pulse_low_1 = NAV_DISPLAY_WRITE_LOW;
PORTD &= display_message.pulse_low_1;
display_message.pulse_high_1 = NAV_DISPLAY_WRITE_HIGH;
PORTD |= display_message.pulse_high_1;

display_message.data_byte_2 = j;
PORTD = display_message.data_byte_2;
display_message.pulse_low_2 = NAV_DISPLAY_WRITE_LOW;
PORTD &= display_message.pulse_low_2;
display_message.pulse_high_2 = NAV_DISPLAY_WRITE_HIGH;
PORTD |= display_message.pulse_high_2;

display_message.data_byte_3 = j;
PORTD = display_message.data_byte_3;
display_message.pulse_low_3 = NAV_DISPLAY_WRITE_LOW;
PORTD &= display_message.pulse_low_3;
display_message.pulse_high_3 = NAV_DISPLAY_WRITE_HIGH;
PORTD |= display_message.pulse_high_3;

display_message.data_byte_4 = j;
PORTD = display_message.data_byte_4;
display_message.pulse_low_4 = NAV_DISPLAY_WRITE_LOW;
PORTD &= display_message.pulse_low_4;
display_message.pulse_high_4 = NAV_DISPLAY_WRITE_HIGH;
PORTD |= display_message.pulse_high_4;

display_message.data_byte_5 = j;
PORTD = display_message.data_byte_5;
display_message.pulse_low_5 = NAV_DISPLAY_WRITE_LOW;
PORTD &= display_message.pulse_low_5;
display_message.pulse_high_5 = NAV_DISPLAY_WRITE_HIGH;
PORTD |= display_message.pulse_high_5;

display_message.data_byte_6 = j;
PORTD = display_message.data_byte_6;
display_message.pulse_low_6 = NAV_DISPLAY_WRITE_LOW;
PORTD &= display_message.pulse_low_6;
display_message.pulse_high_6 = NAV_DISPLAY_WRITE_HIGH;
PORTD |= display_message.pulse_high_6;

display_message.data_byte_7 = j;
PORTD = display_message.data_byte_7;
display_message.pulse_low_7 = NAV_DISPLAY_WRITE_LOW;
PORTD &= display_message.pulse_low_7;
display_message.pulse_high_7 = NAV_DISPLAY_WRITE_HIGH;
PORTD |= display_message.pulse_high_7;

display_message.data_byte_8 = j;
PORTD = display_message.data_byte_8;
display_message.pulse_low_8 = NAV_DISPLAY_WRITE_LOW;
PORTD &= display_message.pulse_low_8;
display_message.pulse_high_8 = NAV_DISPLAY_WRITE_HIGH;
PORTD |= display_message.pulse_high_8;

		data++;
		twi_transmit_data((unsigned char *)&display_message, 30, TWI_SLAVE_ADDRESS_NAV1_DISPLAY);
		_delay_ms(1000);
	}
}


/*
  	// TWCR = (1 << TWINT) | (1 << TWSTA) | (0 << TWSTO) | (1 << TWEN);  // start bit
  	twi_generate_start();
    while (!(TWCR & (1 << TWINT))) ;   // caka na odoslanie startu
    PORTD |= 0x01;

    if ((TWSR & 0xF8) == 0x08)  // start bol odoslany
    {
      PORTD |= 0x02;
      
      TWDR = SLAVE_ADDRESS_SR;  // nahraje adresu slejva
      TWCR = (1 << TWINT) | (0 << TWSTA) | (0 << TWSTO) | (1 << TWEN);  // posle adresu slejva
      while (!(TWCR & (1 << TWINT))) ;   // caka na odoslanie adresy
      
      PORTD |= 0x04;

      if ((TWSR & 0xF8) == 0x18)  // SLA+W poslany, ACK prijaty
      {        
      	PORTD |= 0x08;

        TWDR = data;  // nahraje data 
        TWCR = (1 << TWINT) | (0 << TWSTA) | (0 << TWSTO) | (1 << TWEN);  // posle data
        while (!(TWCR & (1 << TWINT))) ;   // caka na odoslanie dat
      }
      
      if ((TWSR & 0xF8) == 0x20)  // SLA+W poslany, NOT ACK prijaty
      {
		PORTD |= 0x10;      	
      }

      // TWCR = (1 << TWINT) | (0 << TWSTA) | (1 << TWSTO) | (1 << TWEN);  // posle stop bit a novy start bit, musia byt obidva      
      twi_generate_stop();
    }    
*/
