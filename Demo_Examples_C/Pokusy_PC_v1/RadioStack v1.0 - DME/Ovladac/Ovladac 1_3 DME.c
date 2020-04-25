#include <windows.h>
#include <stdio.h>
#include "fsuipc_user.h"
#include <string.h>
#include <conio.h>

HANDLE port, hPort;
char CisloPortu[7] = "COM4";
 
HANDLE OpenPort()  // vytvori pristup na seriovy port
{	
  DCB dcb;
  hPort = CreateFile(CisloPortu, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

  if(hPort == INVALID_HANDLE_VALUE)	printf("CHYBA: NIE JE MOZNE OTVORIT PORT\n");

  memset(&dcb, 0x00, sizeof(DCB));  // vynuluje celu strukturu DCB

  dcb.DCBlength = sizeof(DCB);
  dcb.BaudRate = 9600;			   // rychlost prenosu 9600 baudou
  dcb.ByteSize = 8;				   // 8 bitov na znak
  dcb.Parity = NOPARITY;		   // ziadna parita	
  dcb.StopBits = ONESTOPBIT;	   // jeden stop bit
 
  if(!SetCommState(hPort, &dcb))   // funkcia nastavi pozadovane parametre prenosu
  {
	  printf("CHYBA: NIE JE MOZNE NAKONFIGUROVAT PORT\n");
	  CloseHandle(hPort);
	  hPort = INVALID_HANDLE_VALUE;
  }

  return hPort;
}

int main(void) 
{
  DWORD Result, dwRead, dwWritten; 
  unsigned char DME1_Dis[] = "0-0-0",
				DME1_Spd[] = "0-0-0", 
				DME2_Dis[] = "0-0-0", 
				DME2_Spd[] = "0-0-0",
				adresa = 0x81,
				NoveData[] = "------", 
				DMEaktivne[] = "2";
  
  int pocitadlo = 0;	  

  printf("Prepojovaci program MSFStoRS\nVerzia 1.0 - Distance Measuring Equipment\n\n");
  
  if (FSUIPC_Open(SIM_FS2K4, &Result) == FALSE)  // funkcia nadvazuje spojenie s Flight Simulator 2004
  { 
	printf("CHYBA: SPOJENIE S MS FS 2004 NEUSPESNE, POZRI fsuipc_user.h\n\n");   // do "Result" sa ulozi chybova hodnota,
	printf("Stlac lubovolnu klavesu ...");		   								 // jej vyznam sa da najst v fsuipc_user.h
	getch();
	return 0x01;
  }
  else 
  { 														   
    printf("Zadaj cislo serioveho portu (v tvare COMx, kde 'x' je cislo portu): ");
    //scanf("%s", CisloPortu);  // nacita cislo serioveho portu, pomocou ktoreho sa chceme pripojit ku RadioStacku
	printf("\n");

	port = OpenPort();
	if(hPort == INVALID_HANDLE_VALUE)  // port sa nepodarilo otvorit, pravdepodobne ho pouziva iny program
	{								   // alebo v PC takyto port neexistuje
	  printf("CHYBA: OTVARANIE PORTU ZLYHALO\n\n");
	  printf("Stlac lubovolnu klavesu ...");
	  getch();
	  return 0x02;
	}

    printf("Parametre seriovej linky : 9600 baudov, 8 bitov, 1 stopbit, ziadna parita\n\n");	  
	printf("Spojenie s MS FS 2004 nadviazane\n\n");
	printf("Program sa ukonci stlacenim lubovolnej klavesy ...\n\n\n\n\n");
	printf("DME1_Dis  DME1_Spd | DME2_Dis  DME2_Spd | DMEaktivne\n");

	while (!_kbhit())  // slucka sa ukoncuje stlacenim klavesy
	{ 
/*
    0C29 5 DME1 distance as character string, either "nn.n" or "nnn." (when > 99.9 nm). 
           The 5th character may be a zero or a space. Don't rely on it.

    0C2E 5 DME1 speed as character string, "nnn" followed by either space then zero or just zero.

    0C33 5 DME2 distance as character string, either "nn.n" or "nnn." (when > 99.9 nm). 
	       The 5th character may be a zero or a space. Don't rely on it.

    0C38 5 DME2 speed as character string, "nnn" followed by either space then zero or just zero.
*/
	  FSUIPC_Read(0x0c29, 5, &DME1_Dis, &Result);  // "ziadost" o precitanie udajov z FS
	  FSUIPC_Read(0x0c2E, 5, &DME1_Spd, &Result);
	  FSUIPC_Read(0x0c33, 5, &DME2_Dis, &Result);
	  FSUIPC_Read(0x0c38, 5, &DME2_Spd, &Result);
	  
	  DMEaktivne[0] = DMEaktivne[0] - '0';				 // premenna musi byt celociselna, nie znak, preto odpocita '0'
	  FSUIPC_Write(0x0378, 2, &DMEaktivne[0], &Result);  // "ziadost" o zapis udajov do FS	    
	  DMEaktivne[0] = DMEaktivne[0] + '0';				 // 0378 2 DME1 or DME2 select (1=DME1, 2=DME2)

      FSUIPC_Process(&Result);  // skutocne precita/zapise udaje z/do FS

	  DME1_Dis[4] = '0';  // vynuluje posledne znaky z precitanej hodnoty DME, aby nerobili problem, pre istotu
	  DME1_Spd[3] = '0';
	  DME1_Spd[4] = '0';	  
	  DME2_Dis[4] = '0';
	  DME2_Spd[3] = '0';
	  DME2_Spd[4] = '0';

 	  if ( (strcmp(DME1_Dis, "00.00") == 0) && (strcmp(DME1_Spd, "00000") == 0)) 
	  { 
		strcpy(DME1_Dis, "----");  // ak je rychlost a vzdialenost od DME nulova, tak 	
		strcpy(DME1_Spd, "----");  // na displejoch sa zobrazia pomlcky, to znamena ze nie je signal
	  }

	  if ( (strcmp(DME2_Dis, "00.00") == 0) && (strcmp(DME2_Spd, "00000") == 0)) 
	  { 
		strcpy(DME2_Dis, "----");
		strcpy(DME2_Spd, "----");
	  }

	  // kontrolny vystup hodnot na obrazovku PC
	  printf("%.4s nm   %.3s kt    %.4s nm   %.3s kt     %c   ", DME1_Dis, DME1_Spd, DME2_Dis, DME2_Spd, DMEaktivne[0]);

	  if (DMEaktivne[0] == '1')		// podla polohy prepinaca precitanej zo serioveho portu sa odoslu hodnoty
	  {								// z DME1 alebo DME2 vysielaca
		adresa = 0x81;
	    NoveData[0] = DME1_Dis[0];
	    NoveData[1] = DME1_Dis[1];
	    if (DME1_Dis[2] == '.')  
		  NoveData[2] = DME1_Dis[3];
		else 
		  NoveData[2] = DME1_Dis[2];
	    NoveData[3] = DME1_Spd[0];
	    NoveData[4] = DME1_Spd[1];
	    NoveData[5] = DME1_Spd[2];
	  }
	  
	  if (DMEaktivne[0] == '2') 
	  {
		adresa = 0x82;
	    NoveData[0] = DME2_Dis[0];
	    NoveData[1] = DME2_Dis[1];
	    if (DME2_Dis[2] == '.')  
		  NoveData[2] = DME2_Dis[3];
		else 
		  NoveData[2] = DME2_Dis[2];
	    NoveData[3] = DME2_Spd[0];
	    NoveData[4] = DME2_Spd[1];
	    NoveData[5] = DME2_Spd[2];
	  }
	  	  
	  if (pocitadlo == 100)  // "raz za cas" posle aktualne hodnoty do RadioStacku, odlahcuje "provoz" na linke
	  {						 // a pri kazdom prijme dat zo seriaku displeje v RadioStacku bliknu, tymto to je osetrene 
		pocitadlo = 0;  
        WriteFile(port, &adresa, 1, &dwWritten, NULL);	 // posiela data na seriovy port
        WriteFile(port, NoveData, 6, &dwWritten, NULL);	 // dwWritten/dwRead - vrati pocet odoslanych/prijatych znakov       	  	  	  
	  }
	  ReadFile(port, &DMEaktivne, 1, &dwRead, NULL);	 // prijima data zo serioveho portu, zastavi program a caka	  
														 // kym nepridu data - obnovovacia frekvencia dat je preto riadena
														 // zakladnou doskou v RadioStacku

	  printf("%d\r", pocitadlo);  // pocitadlo na overenie behu programu, ze nie je zaseknuty 
	  pocitadlo++;				  // na ReadFile / WriteFile
	}	  
  }
  FSUIPC_Close();	   // ukonci spojenie s FS
  CloseHandle(hPort);  // ukonci pristup na seriovy port
  return 0x00;
}

/*
	Chicago - O'Hare  
	  VOR/DME - 113.90 MHz
	
	Chicago - DUPAGE
	  VOR/DME - 108.40 MHz

	NORTHBROOK
	  VOR/DME - 113.00 MHz
*/

