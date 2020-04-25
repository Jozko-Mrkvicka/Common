#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "fsuipc_user.h"

DWORD Result, COM1_freq, COM1Stb_freq, COM2_freq, COM2Stb_freq, NAV1_freq, NAV1Stb_freq, NAV2_freq, NAV2Stb_freq;

void main (void) {
  printf("Toto je demonstracia komunikacie medzi MS FS 2004\na externym programom pomocou FSUIPC.dll\n\n");

  if (FSUIPC_Open(SIM_FS2K4, &Result)==FALSE){ 
	printf("DAJAKY PROBLEM, viz fsuipc_user.h\n");  // do "Result" sa ulozi chybova hodnota
    getchar();										// jej vyznam sa da najst v fsuipc_user.h
  }
  else { 														   
	printf("SPOJENIE S MS FS 2004 V PORIADKU\n");
	printf("\nCOM1    COM1Stb  NAV1    NAV1Stb  COM2    COM2Stb  NAV2    NAV2Stb\n");
	while (!_kbhit()) {
	  FSUIPC_Read(0x034e, 2, &COM1_freq, &Result);
	  FSUIPC_Read(0x311a, 2, &COM1Stb_freq, &Result);

	  FSUIPC_Read(0x3118, 2, &COM2_freq, &Result);
	  FSUIPC_Read(0x311c, 2, &COM2Stb_freq, &Result);

	  FSUIPC_Read(0x0350, 2, &NAV1_freq, &Result);
	  FSUIPC_Read(0x311e, 2, &NAV1Stb_freq, &Result);

	  FSUIPC_Read(0x0352, 2, &NAV2_freq, &Result);
	  FSUIPC_Read(0x3120, 2, &NAV2Stb_freq, &Result);

      FSUIPC_Process(&Result);
	
      printf("1%d%d.%d%d  ", (COM1_freq & 0xf000) >> 12, (COM1_freq & 0x0f00) >> 8, (COM1_freq & 0x00f0) >> 4, (COM1_freq & 0x000f));
	  printf("1%d%d.%d%d   ", (COM1Stb_freq & 0xf000) >> 12, (COM1Stb_freq & 0x0f00) >> 8, (COM1Stb_freq & 0x00f0) >> 4, (COM1Stb_freq & 0x000f));
	
	  printf("1%d%d.%d%d  ", (NAV1_freq & 0xf000) >> 12, (NAV1_freq & 0x0f00) >> 8, (NAV1_freq & 0x00f0) >> 4, (NAV1_freq & 0x000f));
	  printf("1%d%d.%d%d   ", (NAV1Stb_freq & 0xf000) >> 12, (NAV1Stb_freq & 0x0f00) >> 8, (NAV1Stb_freq & 0x00f0) >> 4, (NAV1Stb_freq & 0x000f));
	
	  printf("1%d%d.%d%d  ", (COM2_freq & 0xf000) >> 12, (COM2_freq & 0x0f00) >> 8, (COM2_freq & 0x00f0) >> 4, (COM2_freq & 0x000f));
	  printf("1%d%d.%d%d   ", (COM2Stb_freq & 0xf000) >> 12, (COM2Stb_freq & 0x0f00) >> 8, (COM2Stb_freq & 0x00f0) >> 4, (COM2Stb_freq & 0x000f));
	
	  printf("1%d%d.%d%d  ", (NAV2_freq & 0xf000) >> 12, (NAV2_freq & 0x0f00) >> 8, (NAV2_freq & 0x00f0) >> 4, (NAV2_freq & 0x000f));
	  printf("1%d%d.%d%d\r", (NAV2Stb_freq & 0xf000) >> 12, (NAV2Stb_freq & 0x0f00) >> 8, (NAV2Stb_freq & 0x00f0) >> 4, (NAV2Stb_freq & 0x000f));
    }
  }
  FSUIPC_Close();
}
