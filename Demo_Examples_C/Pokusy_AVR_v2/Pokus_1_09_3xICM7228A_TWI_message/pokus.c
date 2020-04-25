#define F_CPU 4000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/twi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TWI_ADDRESS_NAV1_WRITE (0x42 | TW_WRITE)
// #define TWI_ADDRESS_NAV1_READ  ((0x02 << 1) | TW_READ)
#define TWI_ADDRESS_NAV1_INPUTS 0x40

#define DIPLAY_DRIVER_DATA_SIZE			8
#define DIPLAY_DRIVER_STRING_SIZE 		5
#define DIPLAY_DRIVER_MESSAGE_SIZE		18
#define DIPLAY_DRIVER_MAX_DATA_VALUE	15

#define MODE_HIGH 				0x10
#define DRIVER_1_WRITE_HIGH 	0x80
#define DRIVER_2_WRITE_HIGH 	0x40
#define DRIVER_3_WRITE_HIGH 	0x20

#define ASCII_ZERO  	48
#define ASCII_MINUS 	45
#define ASCII_SPACE 	32
#define ASCII_H 		72
#define ASCII_h 		104
#define ASCII_E 		69
#define ASCII_e 		101
#define ASCII_L 		76
#define ASCII_l 		108
#define ASCII_P 		80
#define ASCII_p 		112

#define CHAR_DASH	10
#define CHAR_E 	  	11
#define CHAR_H    	12
#define CHAR_L    	13
#define CHAR_P    	14
#define CHAR_BLANK  15

#define	NACK 0
#define	ACK  1


/////////////////////////////////////////////////////////////////////
void twi_init(void)
{
	// set frequency of TWI SCL line
  	TWBR = 0x08;  // bit rate register
	TWSR = 0xFC;  // status register - prescaler bits
}


char twi_transmit_start(void)
{
	// generate start
    TWCR = (1 << TWINT) | (0 << TWEA) | (1 << TWSTA) | (0 << TWSTO) | (1 << TWEN); 

    // wait until transmitted
	while (!(TWCR & (1 << TWINT)))
		;

	return TW_STATUS;
}


char twi_transmit_stop(void)
{
    TWCR = (1 << TWINT) | (0 << TWEA) | (0 << TWSTA) | (1 << TWSTO) | (1 << TWEN);
	return TW_STATUS;
}


char twi_transmit_byte(char byte)
{
	TWDR = byte;

	// transmit byte
    TWCR = (1 << TWINT) | (0 << TWEA) | (0 << TWSTA) | (0 << TWSTO) | (1 << TWEN);

    // wait until transmitted
	while (!(TWCR & (1 << TWINT)))
		;

	return TW_STATUS;
}


char twi_receive_byte(char *byte, int respond)
{
	// Data byte will be received and ACK/NACK will be returned
	TWCR = (1 << TWINT) | (respond << TWEA) | (0 << TWSTA) | (0 << TWSTO) | (1 << TWEN);

    // wait until transmitted
	while (!(TWCR & (1 << TWINT)))
		;

	*byte = TWDR;

	return TW_STATUS;
}


int twi_is_data_acknowledge_received(void)
{
	if (TW_STATUS == TW_MT_DATA_ACK)
		return 1;
	else
		return 0;
}


int twi_transmit_data(char *data, int size, char slave_addr)
{
	int already_transmitted = 0;
	int i;

	twi_transmit_start();

	twi_transmit_byte(slave_addr);

	for (i = 0; i < size; i++)
	{
		twi_transmit_byte(data[i]);
		if (twi_is_data_acknowledge_received())
			already_transmitted++;
	}

	twi_transmit_stop();

	return already_transmitted;
}


int int_cnt = 0;
int overflow = 0;

void twi_receive_data(char *data, char slave_addr, char command)
{
	twi_transmit_start();

	twi_transmit_byte(slave_addr | TW_WRITE);

	// command byte to MCP23016 - which register to read/write
	twi_transmit_byte(command);

	// repeated start
	twi_transmit_start();

	twi_transmit_byte(slave_addr | TW_READ);

	twi_receive_byte(&data[0], ACK);

	twi_receive_byte(&data[1], NACK);
	
	twi_transmit_stop();
}


/////////////////////////////////////////////////////////////////////
void display_driver_trunc_data_to_max_value(char* data)
{
	int i;
	for (i = 0; i < DIPLAY_DRIVER_STRING_SIZE; i++)
		if (data[i] > DIPLAY_DRIVER_MAX_DATA_VALUE)
			data[i] = DIPLAY_DRIVER_MAX_DATA_VALUE;
}


int display_driver_select_write_signal(int disp_num)
{
	switch (disp_num)
	{
		case 1: return(DRIVER_1_WRITE_HIGH);
		case 2:	return(DRIVER_2_WRITE_HIGH);
		case 3:	return(DRIVER_3_WRITE_HIGH);
		default: return(DRIVER_1_WRITE_HIGH);
	}
}


void display_driver_create_message(char* message, char* data, int disp_num)
{
	char write_high;

	write_high = display_driver_select_write_signal(disp_num);
	display_driver_trunc_data_to_max_value(data);

	message[0] = MODE_HIGH;
	message[1] = MODE_HIGH | write_high;

	message[2] = data[0];
	message[3] = write_high;

	message[4] = data[1];
	message[5] = write_high;

	message[6] = data[2];
	message[7] = write_high;

	message[8] = data[3];
	message[9] = write_high;

	message[10] = data[4];
	message[11] = write_high;

	message[12] = data[5];
	message[13] = write_high;

	message[14] = data[6];
	message[15] = write_high;

	message[16] = data[7];
	message[17] = write_high; 
}


void display_driver_convert_char_to_num(char* str)
{
	int i;

	for (i = 0; i < DIPLAY_DRIVER_STRING_SIZE; i++)
	{
		switch (str[i])
		{
			case ASCII_H:
			case ASCII_h:      str[i] = CHAR_H; break;
			case ASCII_E:
			case ASCII_e:      str[i] = CHAR_E; break;
			case ASCII_L:
			case ASCII_l: 	   str[i] = CHAR_L; break;
			case ASCII_P:
			case ASCII_p: 	   str[i] = CHAR_P; break;
			case ASCII_MINUS:  str[i] = CHAR_DASH; break;
			case ASCII_SPACE:  str[i] = CHAR_BLANK; break;
			default:  		   str[i] -= ASCII_ZERO;
		}
	}
}


void display_driver_convert_data(char* str_1_input,
								 char* str_2_input,
								 char* str_3_input,
								 char* str_4_input,
								 char* data_1_out,
								 char* data_2_out,
								 char* data_3_out)
{
	char str_1[DIPLAY_DRIVER_STRING_SIZE + 1];
	char str_2[DIPLAY_DRIVER_STRING_SIZE + 1];
	char str_3[DIPLAY_DRIVER_STRING_SIZE + 1];
	char str_4[DIPLAY_DRIVER_STRING_SIZE + 1];

	strcpy(str_1, str_1_input);
	strcpy(str_2, str_2_input);
	strcpy(str_3, str_3_input);
	strcpy(str_4, str_4_input);

	display_driver_convert_char_to_num(str_1);
	display_driver_convert_char_to_num(str_2);
	display_driver_convert_char_to_num(str_3);
	display_driver_convert_char_to_num(str_4);

	data_1_out[0] = str_1[0];
	data_1_out[1] = str_1[1];
	data_1_out[2] = str_1[2];
	data_1_out[3] = str_1[3];
	data_1_out[4] = str_1[4];
	data_1_out[5] = str_2[0];
	data_1_out[6] = str_2[1];
	data_1_out[7] = str_2[2];

	data_2_out[0] = str_2[3];
	data_2_out[1] = str_2[4];
	data_2_out[2] = str_3[0];
	data_2_out[3] = str_3[1];
	data_2_out[4] = str_3[2];
	data_2_out[5] = str_3[3];
	data_2_out[6] = str_3[4];
	data_2_out[7] = str_4[0];

	data_3_out[0] = str_4[1];
	data_3_out[1] = str_4[2];
	data_3_out[2] = str_4[3];
	data_3_out[3] = str_4[4];
	data_3_out[4] = CHAR_BLANK;
	data_3_out[5] = CHAR_BLANK;
	data_3_out[6] = CHAR_BLANK;
	data_3_out[7] = CHAR_BLANK;
}


/////////////////////////////////////////////////////////////////////

char A_prev = 0;
char B_prev = 0;
char C_prev = 0;

void rotary_encoders_init()
{
	// Data Direction Register B - set as input
	DDRB = 0x00;

	// pull-ups enabled
	PORTB = 0xFF; 

	// Global Interrupt enabled
	sei();
	// Status Register
	// SREG |= (1 << I);

	// General Interrupt Control Register - INT0 enable
	GICR |= (1 << INT0);

	// MCU Control Register - interrupt on any logical changes on INT0
	MCUCR |= (0 << ISC01);
	MCUCR |= (1 << ISC00);

	// Timer/Counter Interrupt Mask Register
	TIMSK = 0x01;

	// iba pokus
	// Timer/Counter Control Register
	TCCR0 = 0x01;

	// iba pokus
	// Timer/Counter Register - initial value
	TCNT0 = 0x00;

	A_prev = ((PINB & 0x01) >> 0);
	B_prev = ((PIND & 0x04) >> 2);
	C_prev = ((PIND & 0x02) >> 1);
}


// char A, B, C;

char elma_inner_A;
char elma_inner_B;
char elma_outer_A; 
char elma_outer_B;



int comm_stby_dec;
int comm_stby_int = 0;


ISR (INT0_vect)
{
	int inc;

	// int_cnt++;

	// inc = 0;
	// if (overflow < 300)
	// 	inc = 5;

	// else if ((overflow >= 300) && (overflow < 400))
	// 	inc = 4;

	// else if ((overflow >= 400) && (overflow < 500))
	// 	inc = 3;

	// else if ((overflow >= 500) && (overflow < 600))
	// 	inc = 2;

	// else if ((overflow >= 600) /*&& (overflow < 600)*/)
		inc = 1;

	// overflow = 0;

	// B = ((PIND & 0x04) >> 2); 
	elma_outer_A = ((PINB & 0x01) >> 0);
	elma_outer_B = ((PINB & 0x02) >> 1);

	// if (elma_outer_B == 1) comm_stby_dec += inc;
	// if (elma_outer_B == 0) comm_stby_dec -= inc;

	// if ((A != A_prev) /*|| (B != B_prev)*/)
	// {
		if ((elma_outer_A == 0) && (elma_outer_B == 1)) comm_stby_dec += inc;
		if ((elma_outer_A == 1) && (elma_outer_B == 0)) comm_stby_dec += inc;

		if ((elma_outer_A == 1) && (elma_outer_B == 1)) comm_stby_dec -= inc;
		if ((elma_outer_A == 0) && (elma_outer_B == 0)) comm_stby_dec -= inc;
	// }

	// if ((C != C_prev) /*|| (B != B_prev)*/)
	// {
	// 	if ((C == 0) && (B == 1)) comm_stby_int += inc;
	// 	if ((C == 1) && (B == 0)) comm_stby_int += inc;

	// 	if ((C == 1) && (B == 1)) comm_stby_int -= inc;
	// 	if ((C == 0) && (B == 0)) comm_stby_int -= inc;
	// }

	// A_prev = A;
	// C_prev = C;
	// B_prev = B;
}


// ISR (TIMER0_OVF_vect)
// {
// 	if (overflow < 2000)
// 		overflow++;
// }


/////////////////////////////////////////////////////////////////////
int main(void) 
{
	char str_1[DIPLAY_DRIVER_STRING_SIZE + 1];
	char str_2[DIPLAY_DRIVER_STRING_SIZE + 1];
	char str_3[DIPLAY_DRIVER_STRING_SIZE + 1];
	char str_4[DIPLAY_DRIVER_STRING_SIZE + 1];

	char data_1[DIPLAY_DRIVER_DATA_SIZE];
	char data_2[DIPLAY_DRIVER_DATA_SIZE];
	char data_3[DIPLAY_DRIVER_DATA_SIZE];

	char message[DIPLAY_DRIVER_MESSAGE_SIZE];

  	twi_init();

  	// rotary_encoders_init();

	strcpy(str_1, "-----");
	strcpy(str_2, "-----");
	strcpy(str_3, "-----");
	strcpy(str_4, "-----");



	// char mess1[3];
	// mess1[0] = 0x06; // access to IODIR0
	// mess1[1] = 0x00; // set PORT0 as output
	// mess1[2] = 0x00; // set PORT1 as output

	// char mess2[3];
	// mess2[0] = 0x00; // access to GP0
	// mess2[1] = 3;	 // data to GP0
	// mess2[2] = 7;	 // data to GP1

	char received_data[2] = {7, 8};

	char command = 0x00; // access to GP0

	// wait for MCP23016 hardware inicialization
	_delay_ms(200);
	//twi_transmit_data(mess1, 3, (TWI_ADDRESS_NAV1_INPUTS | TW_WRITE));

    while (1)
    {
    	// conversion int to string
		sprintf(str_1, "%5d", comm_stby_int);
		sprintf(str_2, "%5d", comm_stby_dec);
		sprintf(str_3, "%5d", int_cnt);
		sprintf(str_4, "%5d", overflow);

    	display_driver_convert_data(str_1, str_2, str_3, str_4, data_1, data_2, data_3);

		display_driver_create_message(message, data_1, 1);
		twi_transmit_data(message, DIPLAY_DRIVER_MESSAGE_SIZE, TWI_ADDRESS_NAV1_WRITE);

		display_driver_create_message(message, data_2, 2);
		twi_transmit_data(message, DIPLAY_DRIVER_MESSAGE_SIZE, TWI_ADDRESS_NAV1_WRITE);

		display_driver_create_message(message, data_3, 3);
		twi_transmit_data(message, DIPLAY_DRIVER_MESSAGE_SIZE, TWI_ADDRESS_NAV1_WRITE);

		// twi_transmit_data(mess2, 3, TWI_ADDRESS_NAV1_WRITE_2);

		twi_receive_data(received_data, TWI_ADDRESS_NAV1_INPUTS, command);

comm_stby_int++;

		comm_stby_dec = received_data[0];
		int_cnt = received_data[1];

		_delay_ms(10);
    }
}

