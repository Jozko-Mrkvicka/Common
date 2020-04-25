// #define __AVR_ATmega8__
#define __OPTIMIZE__
#define F_CPU 1000000UL

#include <util/delay.h>

// #define Dis1 PORTD.7 
// #define Dis2 PORTB.0 
// #define Dis3 PORTB.2
// #define Dis4 PORTB.1

// #define Seg1 PORTC.1
// #define Seg2 PORTC.2
// #define Seg4 PORTC.3
// #define Seg6 PORTB.3
// #define Seg7 PORTB.4
// #define Seg9 PORTB.5
// #define Seg10 PORTC.0

int main(void) 
{
    // Dis1 = 1;  // napajania displejov nastavene na 1 (5V)
    // Dis2 = 1;
    // Dis3 = 1;
    // Dis4 = 1;

    // Seg1 = 0;  // segmenty nastavene na 0 (0V) - vsetky su rozsvietene
    // Seg2 = 0;
    // Seg4 = 0;
    // Seg6 = 0;
    // Seg7 = 0;
    // Seg9 = 0;
    // Seg10 = 0;

    // set_pin_direction(DDR_B, PB0, OUT);  // funguje
    set_port_direction(DDR_B, OUT);      // funguje
    
    while (1)
    {
        // set_port_low(PORT_B);       // funguje
        set_pin_val(PORT_B, PB0, LOW);
        _delay_ms(1000);

        // set_port_high(PORT_B);      // funguje
        set_pin_val(PORT_B, PB0, HIGH);
        _delay_ms(1000);
    }
}
