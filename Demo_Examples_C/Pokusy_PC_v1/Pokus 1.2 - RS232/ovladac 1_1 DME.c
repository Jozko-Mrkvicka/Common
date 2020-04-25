/*
  Testovaci program na overenie funkcnosti serioveho portu.
  Program vysiela adresu (1 bajt) a po nej pole siestich znakov na seriovy port. 
*/
#include <windows.h>
#include <stdio.h>
#include <string.h>

HANDLE port, hPort;
 
HANDLE OpenPort() 
{	
  DCB dcb;
  hPort = CreateFile("COM4", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

  if(hPort == INVALID_HANDLE_VALUE)
    printf("CHYBA: nie je mozne otvorit port");
  else
    printf("Pristup na port v poriadku\n\n");

  memset(&dcb, 0x0, sizeof(DCB));  // nastavy vsetky prvky struktory na 0

  dcb.DCBlength = sizeof(DCB);
  dcb.BaudRate = 9600;
  dcb.ByteSize = 8;
  dcb.Parity = NOPARITY;
  dcb.StopBits = ONESTOPBIT;
 
  if(!SetCommState(hPort, &dcb))
  {
    printf("CHYBA: neda sa nakonfigurovat port");
	CloseHandle(hPort);
	hPort = INVALID_HANDLE_VALUE;
  }
  return hPort;
}

int main(void) 
{
  DWORD Result, dwRead, dwWritten; 
   
  int PocetZnakovVysielanie, 
      pocitadlo = 0;
      
  unsigned char NoveData[6],
                adresa = 0x81;
                
  printf("Parametre seriovej linky : 9600 baudov, 8 bitov, 1 stopbit, ziadna parita\n\n");
  
  port = OpenPort();
  if(hPort == INVALID_HANDLE_VALUE)
  {
    printf("CHYBA: otvorenie portu zlyhalo");
    getch();
    return 0x01;
  }

  while (!_kbhit()) 
  { 		  
    NoveData[0] = 1;
    NoveData[1] = 2;
    NoveData[2] = 1;
    NoveData[3] = 2;
    NoveData[4] = 1;
    NoveData[5] = 2;

    PocetZnakovVysielanie = strlen(NoveData);

    WriteFile(port, &adresa, 1, &dwWritten, NULL);
    WriteFile(port, NoveData, PocetZnakovVysielanie, &dwWritten, NULL);  // dwWritten/dwRead - vrati pocet odoslanych/prijatych znakov 

    printf("pocitadlo = %d\r", pocitadlo);
    Sleep(1000);	  
    pocitadlo++;
  }	    
  CloseHandle(hPort);
  return 0x00;
}
