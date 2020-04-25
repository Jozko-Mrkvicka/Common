#include <windows.h>
#include <stdio.h>
#include "conio.h"

char pole[] = "Vyzbroj tvorily dva 30 mm kanony NR-30 v nabeznych hranach kridel pri jeho koreni. Pro kazdy kanon bylo k dispozici 70 naboju. "
	          "Letoun mohl nest nerizene rakety a bomby. V prvnich verzich mel letoun jen dva zavesniky pod kridly s nosnosti 500kg, pozdeji zvysene na 750kg." 
			  "Dalsi dva zavesniky byly pod trupem s nosnosti po 500 kg.\n\n";

HANDLE port, hPort;
char text[11];
int PocetZnakov;
DWORD dwRead, dwWritten;

HANDLE OpenPort() {	
  DCB dcb;
  hPort = CreateFile("COM1", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

  dcb.DCBlength = sizeof(DCB);
  dcb.BaudRate = 9600;
  dcb.ByteSize = 8;
  dcb.Parity = NOPARITY;
  dcb.StopBits = ONESTOPBIT;
 
  SetCommState(hPort, &dcb);
  return hPort;
}

void main(void) {
  printf("Toto je take malicke demo na overenie funkcnosti serioveho portu.\n");
  printf("Najprv zapni na druhom pocitaci HyperTerminal \na potom spust tento program este raz.\n");
  printf("Parametre HyperTerminalu : 9600 baudov, 8 bitov, 1 stopbit, ziadna parita\n\n");
  printf("Vies o ake lietadlo sa jedna ? ;-)\n\n");
  PocetZnakov = strlen(pole);
  port = OpenPort();
  WriteFile(port, pole, PocetZnakov, &dwWritten, NULL);  // dwWritten/dwRead - vrati pocet odoslanych/prijatych znakov 
  ReadFile(port, text, PocetZnakov, &dwRead, NULL);		 // PocetZnakov - kolko toho sa ma poslat/prijat
  printf("%s\n", text);
  CloseHandle(hPort);
  getchar();
}

