#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "fsuipc_user.h"

DWORD Result, IAS;
int VSI, ALT;
double HDG;

void main (void) {
  printf("Malicka ukazka c.2 pre Honzika - letove pristroje\n");
  printf("Toto je demonstracia komunikacie medzi MS FS 2004\na externym programom pomocou FSUIPC.dll\n\n");

  if (FSUIPC_Open(SIM_FS2K4, &Result)==FALSE){ 
	printf("DAJAKY PROBLEM, viz fsuipc_user.h\n");  // do "Result" sa ulozi chybova hodnota
    getchar();										// jej vyznam sa da najst v fsuipc_user.h
  }
  else { 														   
	printf("SPOJENIE S MS FS 2004 V PORIADKU\n");
	
	printf("\nIAS[knots]  VSI[ft/min]  ALT[ft]  HDG[degrees]  \n");
	while (!_kbhit()) {
	  
	  FSUIPC_Read(0x02bc, 4, &IAS, &Result);
	  FSUIPC_Read(0x02c8, 4, &VSI, &Result);
	  FSUIPC_Read(0x3324, 4, &ALT, &Result);
	  FSUIPC_Read(0x2b00, 8, &HDG, &Result);
	  
      FSUIPC_Process(&Result);
	  
      printf("%3d          ", IAS/128);          // prepocet - viz FSUIPC Offsets Status.pdf
	  printf("%4.0f        ", VSI*0.7689);
	  printf("%5d        ", ALT);
	  printf("%3.0f      \r", HDG);
	}
  }
  FSUIPC_Close();
}

/*
   1 byte = char
   2 byte = WORD
   4 byte = int, float, DWORD
   8 byte = double 
*/