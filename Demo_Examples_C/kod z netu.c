
C Functions

    DigitTo7SegEncoder()
    StringToHex()

Digit to Seven Segment Display Encoder - DigitTo7SegEncoder()
The DigitTo7SegEncoder() Function
The following function DigitTo7SegEncoder() takes a decimal digit and returns an encoded value used to display the digit on a Seven Segment Display. Please see the comments at the top of the function for a more detail explanation.

/*
* Author: AVR Tutorials
* AVR-Tutorials.com
*
* Compiler: AVR GNU C Compiler (GCC) 
*
* Function Description:
* Encode a Decimal Digit 0-9 to its Seven Segment Equivalent.
*
* Function Arguments:
* digit - Decimal Digit to be Encoded
* common - Common Anode (0), Common Cathode(1)
* SegVal - Encoded Seven Segment Value 
*
* Connections:
* Encoded SegVal is return in the other G-F-E-D-C-B-A that is A is the least
* significant bit (bit 0) and G bit 6.
*/
unsigned char DigitTo7SegEncoder(unsigned char digit, unsigned char common)
{
	unsigned char SegVal;
 
	switch(digit)	
	{	
		case 0:	if(common == 1)	SegVal = 0b00111111;
				else			SegVal = ~0b00111111;
				break;
		case 1:	if(common == 1)	SegVal = 0b00000110;
				else			SegVal = ~0b00000110;
				break;
		case 2:	if(common == 1)	SegVal = 0b01011011;
				else			SegVal = ~0b01011011;
				break;
		case 3:	if(common == 1)	SegVal = 0b01001111;
				else			SegVal = ~0b01001111;
				break;
		case 4:	if(common == 1)	SegVal = 0b01100110;
				else			SegVal = ~0b01100110;
				break;
		case 5:	if(common == 1)	SegVal = 0b01101101;
				else			SegVal = ~0b01101101;
				break;
		case 6:	if(common == 1)	SegVal = 0b01111101;
				else			SegVal = ~0b01111101;
				break;
		case 7:	if(common == 1)	SegVal = 0b00000111;
				else			SegVal = ~0b00000111;
				break;
		case 8:	if(common == 1)	SegVal = 0b01111111;
				else			SegVal = ~0b01111111;
				break;
		case 9:	if(common == 1)	SegVal = 0b01101111;
				else			SegVal = ~0b01101111;		
	}		
	return SegVal;
}

