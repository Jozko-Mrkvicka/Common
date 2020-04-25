#include <mega8.h>
#include <delay.h>

#define TRANSPONDER_ADDRESS 0x04

#define SpinacVonk0 PINB.4 
#define SpinacVnut0 PINB.3
#define SpinacVonk1 PINB.1
#define SpinacVnut1 PINB.2
#define SpinacVonk2 PINC.3
#define SpinacVnut2 PINC.2
#define SpinacVonk3 PINC.0
#define SpinacVnut3 PINC.1
#define SpinacStred PORTB.5

int hodnota[4], PredoslyStav[4];

void init(void)
{
  DDRD = 0xFF;  // cele D je vystup - displaye
  
  DDRB.5 = 1;  // stredy od spinacov - vystup
  
  DDRC.0 = 0;  // spinace - vstupy
  DDRC.1 = 0;
  DDRC.2 = 0;
  DDRC.3 = 0;
  DDRB.1 = 0;
  DDRB.2 = 0;
  DDRB.3 = 0;
  DDRB.4 = 0;
  
  PORTC.3 = 1;  // na vstupnych pinoch v kludovom stave nastavenych 5V
  PORTC.2 = 1;
  PORTC.0 = 1;
  PORTC.1 = 1;
  PORTB.4 = 1;
  PORTB.3 = 1;
  PORTB.1 = 1;
  PORTB.2 = 1;
  
  SpinacStred = 0;
    
  hodnota[0] = 7;
  hodnota[1] = 5;
  hodnota[2] = 0;
  hodnota[3] = 0;
  
  PredoslyStav[0] = 0;
  PredoslyStav[1] = 0;
  PredoslyStav[2] = 0;
  PredoslyStav[3] = 0;
}

void PrepniDisplej(int i)
{
  switch (i) 
  {
    case 0 : 
    {
      PORTD.5 = 0;
      PORTD.6 = 0;       
    } break;

    case 1 : 
    {
      PORTD.5 = 1;
      PORTD.6 = 0;       
    } break;

    case 2 : 
    {
      PORTD.5 = 0;
      PORTD.6 = 1;       
    } break;

    case 3 : 
    {
      PORTD.5 = 1;
      PORTD.6 = 1;       
    } break;
  }
}

void main(void)                
{
  int i, j = 0, k,
      oneskorenie = 5, 
      stav[4];

  TWAR = TRANSPONDER_ADDRESS;                                                                    
  TWCR = (1 << TWEN) | (1 << TWEA) | (0 << TWSTA) | (0 << TWSTO);  // inicializovany slave mod

  init();
  while (1)
  {    
    for (k = 0; k < 4; k++)
    {

    if (TWCR & (1 << TWINT))  // caka na prijem svojej adresy
    { 
      if ((TWSR & 0xF8) == 0xA8)  // SLA+R prijata, ACK odoslany
      { 
        for (i = 0; i < 4; i++)
        {
          TWDR = hodnota[i];
          TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT) | (0 << TWSTO);  // TWEA = 0 ... posiela sa posledny bajt
          while (!(TWCR & (1 << TWINT))) ; // caka na odoslanie dat
        }
                
        TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
        while (!(TWCR & (1 << TWINT))) ; // caka na stop bit            
      }                         
    }  

    j++;
    if (j > 10)
    {
      j = 0;    
      if (SpinacVonk0 == 0) stav[0] = 1;
      if (SpinacVnut0 == 0) stav[0] = 2;
      if ((SpinacVnut0 == 1) && (SpinacVonk0 == 1)) stav[0] = 3;

      if (SpinacVonk1 == 0) stav[1] = 1;
      if (SpinacVnut1 == 0) stav[1] = 2;
      if ((SpinacVnut1 == 1) && (SpinacVonk1 == 1)) stav[1] = 3;

      if (SpinacVonk2 == 0) stav[2] = 1;
      if (SpinacVnut2 == 0) stav[2] = 2;
      if ((SpinacVnut2 == 1) && (SpinacVonk2 == 1)) stav[2] = 3;

      if (SpinacVonk3 == 0) stav[3] = 1;
      if (SpinacVnut3 == 0) stav[3] = 2;
      if ((SpinacVnut3 == 1) && (SpinacVonk3 == 1)) stav[3] = 3;
    }         
    

      if (((PredoslyStav[k] - stav[k]) == -1) || ((PredoslyStav[k] - stav[k]) == 2))
        hodnota[k]++;
      if (((PredoslyStav[k] - stav[k]) == 1) || ((PredoslyStav[k] - stav[k]) == -2))
        hodnota[k]--;         
      
      if (hodnota[k] > 7) hodnota[k] = 0;
      if (hodnota[k] < 0) hodnota[k] = 7;
     
      PredoslyStav[k] = stav[k];

      PORTD = hodnota[k];
      PrepniDisplej(k);
      //delay_ms(oneskorenie);
    }
  }
} 