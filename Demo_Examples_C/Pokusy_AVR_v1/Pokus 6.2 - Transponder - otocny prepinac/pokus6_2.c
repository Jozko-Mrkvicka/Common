#include <mega8.h>
#include <delay.h>

// displaye
#define Dis1 PORTD.7  // napajania displayov 1 az 4
#define Dis2 PORTB.0 
#define Dis3 PORTB.2
#define Dis4 PORTB.1

#define Seg1 PORTC.1  // jednotlive segmenty 
#define Seg2 PORTC.2
#define Seg4 PORTC.3
#define Seg6 PORTB.3
#define Seg7 PORTB.4
#define Seg9 PORTB.5
#define Seg10 PORTC.0

// spinace - napajanie
#define Spinac_1_VCC PORTD.4
#define Spinac_2_VCC PORTD.3
#define Spinac_4_VCC PORTD.2 
#define Spinac_3_VCC PORTD.1

#define Spinac_Data_1 PIND.5  // otocny spinac - vonkajsi "okruh"
#define Spinac_Data_2 PIND.6  // otocny spinac - vnutorny "okruh"

void init(void) {
  // displaye
  DDRD.7 = 1;  // port D7 nastaveny ako vystupny
  DDRB.0 = 1;  // porty B0 az B5 nastavene ako vystupne 
  DDRB.1 = 1;
  DDRB.2 = 1;
  DDRB.3 = 1;
  DDRB.4 = 1;
  DDRB.5 = 1;
  DDRC.0 = 1;  // porty C0 az C3 nastavene ako vystupne
  DDRC.1 = 1;
  DDRC.2 = 1;
  DDRC.3 = 1;    
  
  // spinace
  DDRD.1 = 1;
  DDRD.2 = 1;    // spinac 4 VCC
  DDRD.3 = 1;
  DDRD.4 = 1;
  
  DDRD.5 = 0;    // spinac data 1
  DDRD.6 = 0;    // spinac data 2
  
  //PORTC.6 = 1;  // zapinanie pull-up odporov 
  //PORTD.0 = 1;
  //PORTD.1 = 1;
  //PORTD.2 = 1;
  //PORTD.3 = 1;
  //PORTD.4 = 1;
  PORTD.5 = 1;   // na vstupnom pine je 5V, spina do zeme
  PORTD.6 = 1;
}

void c0(void) {  
  Seg10 = 1; Seg1 = 0; Seg2 = 0; Seg4 = 0; Seg6 = 0; Seg7 = 0; Seg9 = 0; // nula
}
void c1(void) {  
  Seg10 = 1; Seg1 = 1; Seg2 = 1; Seg4 = 0; Seg6 = 0; Seg7 = 1; Seg9 = 1; // jeden
}
void c2(void) {  
  Seg10 = 0; Seg1 = 0; Seg2 = 0; Seg4 = 1; Seg6 = 0; Seg7 = 0; Seg9 = 1; // dva
}
void c3(void) {  
  Seg10 = 0; Seg1 = 1; Seg2 = 0; Seg4 = 0; Seg6 = 0; Seg7 = 0; Seg9 = 1; // tri
}
void c4(void) {  
  Seg10 = 0; Seg1 = 1; Seg2 = 1; Seg4 = 0; Seg6 = 0; Seg7 = 1; Seg9 = 0; // styri
}
void c5(void) {  
  Seg10 = 0; Seg1 = 1; Seg2 = 0; Seg4 = 0; Seg6 = 1; Seg7 = 0; Seg9 = 0; // pat
}
void c6(void) {  
  Seg10 = 0; Seg1 = 0; Seg2 = 0; Seg4 = 0; Seg6 = 1; Seg7 = 0; Seg9 = 0; // sest
}
void c7(void) {  
  Seg10 = 1; Seg1 = 1; Seg2 = 1; Seg4 = 0; Seg6 = 0; Seg7 = 0; Seg9 = 1; // sedem
}
void c8(void) {  
  Seg10 = 0; Seg1 = 0; Seg2 = 0; Seg4 = 0; Seg6 = 0; Seg7 = 0; Seg9 = 0; // osem
}
void c9(void) {  
  Seg10 = 0; Seg1 = 1; Seg2 = 0; Seg4 = 0; Seg6 = 0; Seg7 = 0; Seg9 = 0; // devat
}

void cislica(int i) {     
  switch (i) {
    case '0': c0(); break;
    case '1': c1(); break;
    case '2': c2(); break;
    case '3': c3(); break;
    case '4': c4(); break;
    case '5': c5(); break;
    case '6': c6(); break;
    case '7': c7(); break;
    case '8': c8(); break;
    case '9': c9(); break;
  }
} 

void VypniDisplaye(void)  // odpoji napajanie vsetkych displayov 
{  
    Dis1 = 0;
    Dis2 = 0;
    Dis3 = 0;
    Dis4 = 0;
}

void main(void)
{              
  int oneskorenie = 5, SucasnyStav, PredoslyStav = 0;
  unsigned char hodnota[] = "1234";

  init();    
  while (1)                  // vlastny multiplexing - postupne pripaja napatia ku displejom 1 az 4
  { 
    VypniDisplaye();
    Dis1 = 1;
    cislica(hodnota[0]);   // nastavi segmenty displayou na pozadovanu cislicu
    delay_ms(oneskorenie);   
      
    VypniDisplaye();
    Dis2 = 1;
    cislica(hodnota[1]);
    delay_ms(oneskorenie);
      
    VypniDisplaye();
    Dis3 = 1;
    cislica(hodnota[2]);
    delay_ms(oneskorenie);
                                                               
    VypniDisplaye();
    Dis4 = 1;
    cislica(hodnota[3]);
    delay_ms(oneskorenie);   
    
    Spinac_1_VCC = 1;
    Spinac_2_VCC = 0;
    Spinac_3_VCC = 1;
    Spinac_4_VCC = 1;
    
    hodnota[0] = '0';
    hodnota[1] = '0';
    hodnota[2] = '0';
    
    if (Spinac_Data_1 == 0)                           hodnota[0] = '1';
    if (Spinac_Data_2 == 0)                           hodnota[1] = '2';
    if ((Spinac_Data_1 != 0) && (Spinac_Data_2 != 0)) hodnota[2] = '3';
                               
      
/*      
    if ((PredoslyStav == 1) && (SucasnyStav == 2)) hodnota[4]++;
    if ((PredoslyStav == 2) && (SucasnyStav == 3)) hodnota[4]++;
    if ((PredoslyStav == 3) && (SucasnyStav == 1)) hodnota[4]++;
      
    if ((PredoslyStav == 2) && (SucasnyStav == 1)) hodnota[4]--;
    if ((PredoslyStav == 3) && (SucasnyStav == 2)) hodnota[4]--;
    if ((PredoslyStav == 1) && (SucasnyStav == 3)) hodnota[4]--;

    if (hodnota[4] == 10) hodnota[4] = 0;  // pretecenie
    if (hodnota[4] == -1) hodnota[4] = 9;
      
    PredoslyStav = SucasnyStav;
*/
  }
}


/*
void main(void) {
  DDRC.2 = 1;
  DDRB.4 = 1;
  DDRD.1 = 0;
  DDRD.2 = 0;
  
  PORTD.1 = 1;
  PORTD.2 = 1;
  
  while (1) {
    //PORTC.2 = 0;
    //PORTB.4 = 0;
    
    if (PIND.1 == 0) PORTC.2 = 1;
    if (PIND.2 == 0) PORTB.4 = 1;
   // delay_ms(10);
  }
}
*/
 /*  
      if ((Tlac3_1 == 1) && (Tlac3_2 == 0)) stav = 2;
      if ((Tlac3_1 == 0) && (Tlac3_2 == 1)) stav = 1;
      if ((Tlac3_1 == 0) && (Tlac3_2 == 0)) stav = 0;
      
      
    */
   