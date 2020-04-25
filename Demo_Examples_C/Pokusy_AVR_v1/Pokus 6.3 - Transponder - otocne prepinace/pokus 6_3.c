#include <mega8.h>
#include <delay.h>

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

#define Tlac1_1 PIND.4
#define Tlac1_2 PIND.3
#define Tlac2_1 PIND.2
#define Tlac2_2 PIND.1
#define Tlac3_1 PIND.0
#define Tlac3_2 PINC.6
#define Tlac4_1 PIND.5
#define Tlac4_2 PIND.6

void init(void) {
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
  
  DDRC.6 = 0;  // porty nastavene ako vstupne
  DDRD.0 = 0;
  DDRD.1 = 0;
  DDRD.2 = 0;
  DDRD.3 = 0;
  DDRD.4 = 0;
  DDRD.5 = 0;
  DDRD.6 = 0;   
  
  PORTC.6 = 1;  // zapinanie pull-up odporov 
  PORTD.0 = 1;
  PORTD.1 = 1;
  PORTD.2 = 1;
  PORTD.3 = 1;
  PORTD.4 = 1;
  PORTD.5 = 0;
  PORTD.6 = 0;
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
    case 0: c0(); break;
    case 1: c1(); break;
    case 2: c2(); break;
    case 3: c3(); break;
    case 4: c4(); break;
    case 5: c5(); break;
    case 6: c6(); break;
    case 7: c7(); break;
    case 8: c8(); break;
    case 9: c9(); break;
  }
} 

typedef struct {
  int T1, T2, T3, T4; 
} TLACITKO; 

int i,a,b,c,d;
TLACITKO stav, PredoslyStav;

void main(void)
{              
  init();
  
  a = 0; b = 0; c = 0; d = 0;  // cislo ktore sa zobrazi na displayi
  
  i = 5;        // pri i > 5 dochadza ku blikaniu
  
  PredoslyStav.T1 = 0;
  PredoslyStav.T2 = 0;
  PredoslyStav.T3 = 0;
  PredoslyStav.T4 = 0;
  
  while (1)     // vlastny multiplexing - postupne pripaja napatia ku displejom 1 az 4
    { 
      Dis1 = 1;
      Dis2 = 0;
      Dis3 = 0;
      Dis4 = 0;
      cislica(a);   // nastavi segmenty displayou na pozadovanu cislicu
      delay_ms(i);   
      
      Dis1 = 0;
      Dis2 = 1;
      Dis3 = 0;
      Dis4 = 0;
      cislica(b);
      delay_ms(i);
      
      Dis1 = 0;
      Dis2 = 0;
      Dis3 = 1;
      Dis4 = 0;
      cislica(c);
      delay_ms(i);
                                                               
      Dis1 = 0;
      Dis2 = 0;
      Dis3 = 0;
      Dis4 = 1;
      cislica(d);
      delay_ms(i);   
      
      // vyhodnotenie stavu prveho otocneho prepinaca
      if (Tlac1_1 == 0)                     stav.T1 = 3;
      if (Tlac1_2 == 0)                     stav.T1 = 2; 
      if ((Tlac1_1 == 1) && (Tlac1_2 == 1)) stav.T1 = 1; 
            
      if ((PredoslyStav.T1 == 1) && (stav.T1 == 2)) a = a + 1;
      if ((PredoslyStav.T1 == 2) && (stav.T1 == 3)) a = a + 1;
      if ((PredoslyStav.T1 == 3) && (stav.T1 == 1)) a = a + 1;
      
      if ((PredoslyStav.T1 == 2) && (stav.T1 == 1)) a = a - 1;
      if ((PredoslyStav.T1 == 3) && (stav.T1 == 2)) a = a - 1;
      if ((PredoslyStav.T1 == 1) && (stav.T1 == 3)) a = a - 1;
      
      // vyhodnotenie stavu druheho otocneho prepinaca
      if (Tlac2_1 == 0)                     stav.T2 = 3;
      if (Tlac2_2 == 0)                     stav.T2 = 2; 
      if ((Tlac2_1 == 1) && (Tlac2_2 == 1)) stav.T2 = 1; 
            
      if ((PredoslyStav.T2 == 1) && (stav.T2 == 2)) b = b + 1;
      if ((PredoslyStav.T2 == 2) && (stav.T2 == 3)) b = b + 1;
      if ((PredoslyStav.T2 == 3) && (stav.T2 == 1)) b = b + 1;
      
      if ((PredoslyStav.T2 == 2) && (stav.T2 == 1)) b = b - 1;
      if ((PredoslyStav.T2 == 3) && (stav.T2 == 2)) b = b - 1;
      if ((PredoslyStav.T2 == 1) && (stav.T2 == 3)) b = b - 1;
      
      // vyhodnotenie stavu tretieho otocneho prepinaca
      if (Tlac3_1 == 0)                     stav.T3 = 3;
      if (Tlac3_2 == 0)                     stav.T3 = 2; 
      if ((Tlac3_1 == 1) && (Tlac3_2 == 1)) stav.T3 = 1; 
            
      if ((PredoslyStav.T3 == 1) && (stav.T3 == 2)) c = c + 1;
      if ((PredoslyStav.T3 == 2) && (stav.T3 == 3)) c = c + 1;
      if ((PredoslyStav.T3 == 3) && (stav.T3 == 1)) c = c + 1;
      
      if ((PredoslyStav.T3 == 2) && (stav.T3 == 1)) c = c - 1;
      if ((PredoslyStav.T3 == 3) && (stav.T3 == 2)) c = c - 1;
      if ((PredoslyStav.T3 == 1) && (stav.T3 == 3)) c = c - 1;

      // vyhodnotenie stavu stvrteho otocneho prepinaca
      if (Tlac4_1 == 0)                     stav.T4 = 3;
      if (Tlac4_2 == 0)                     stav.T4 = 2; 
      if ((Tlac4_1 == 1) && (Tlac4_2 == 1)) stav.T4 = 1; 
            
      if ((PredoslyStav.T4 == 1) && (stav.T4 == 2)) d = d + 1;
      if ((PredoslyStav.T4 == 2) && (stav.T4 == 3)) d = d + 1;
      if ((PredoslyStav.T4 == 3) && (stav.T4 == 1)) d = d + 1;
      
      if ((PredoslyStav.T4 == 2) && (stav.T4 == 1)) d = d - 1;
      if ((PredoslyStav.T4 == 3) && (stav.T4 == 2)) d = d - 1;
      if ((PredoslyStav.T4 == 1) && (stav.T4 == 3)) d = d - 1;

      
      if (a == 10) a = 0;  // ochrana pred pretecenim
      if (a == -1) a = 9;
      if (b == 10) b = 0;  
      if (b == -1) b = 9;
      if (c == 10) c = 0;  
      if (c == -1) c = 9;
      if (d == 10) d = 0;  
      if (d == -1) d = 9;
      
      PredoslyStav.T1 = stav.T1;
      PredoslyStav.T2 = stav.T2;
      PredoslyStav.T3 = stav.T3;
      PredoslyStav.T4 = stav.T4;
    }
}