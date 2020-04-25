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
 
  SetCommState(hPort, &dcb);

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
  DWORD dwRead, dwWritten;
  int PocetZnakovPrijem, PocetZnakovVysielanie, 
      pocitadlo = 0;   
      
  unsigned char PrijatyZnak[] = "-", 
                NoveData[6],
                adresa = 0x81;
  
  DWORD dwCommModemStatus;
  
  NoveData[0] = 1;
  NoveData[1] = 2;
  NoveData[2] = 1;
  NoveData[3] = 2;
  NoveData[4] = 1;
  NoveData[5] = 2;
     
  printf("Ovladac 1.2 DME\n");

  port = OpenPort();
  if(hPort == INVALID_HANDLE_VALUE)
  {
    printf("CHYBA: otvorenie portu zlyhalo");
    getch();
    return 0x01;
  }
  
  SetCommMask (port, EV_RXCHAR);  // nastavuje na aku udalost (event) sa bude reagovat

  PocetZnakovPrijem = strlen(PrijatyZnak);
  PocetZnakovVysielanie = strlen(NoveData);
  
  while (!kbhit()) 
  {     
    printf("pocitadlo = %d %c\r", pocitadlo, PrijatyZnak);

//    WriteFile(port, &adresa, 1, &dwWritten, NULL); 
//    WriteFile(port, NoveData, PocetZnakovVysielanie, &dwWritten, NULL); 

    WaitCommEvent (port, &dwCommModemStatus, 0);     // caka kym nepride po seriaku dajaky znak
    ReadFile(port, &PrijatyZnak, 1, &dwRead, NULL);	 // precita znak zo seriaku
    
    pocitadlo++;
    Sleep(1);
  }
  CloseHandle(hPort);
  return 0x00;
}

