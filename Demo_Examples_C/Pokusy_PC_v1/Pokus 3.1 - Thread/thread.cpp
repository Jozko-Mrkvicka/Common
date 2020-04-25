// thread.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <windows.h>
#include <conio.h>
#include <stdio.h>

// ak chces procedure vlakna poslat viac ako 1 int, musis jej dat pointer na
// strukturu
typedef struct
{
	int wait_seconds;

} THREAD_STRUCT;


// Procedura vlakna MUSI mat taky prototyp (mozes menit akurat nazov funkcie)
UINT WINAPI ThreadProcedure(LPVOID pParam);


UINT WINAPI ThreadProcedure(LPVOID pParam)
{
	// pretypuj pointer na pointer na svoju struckturu
	THREAD_STRUCT* pStruct = (THREAD_STRUCT*) pParam;

	for(int i = 0; i < pStruct->wait_seconds; i++)
	{
		Sleep(1000);
		printf("#");
	}

	return 0;
}


int main(int argc, char **argv)
{
	THREAD_STRUCT thrs;
	thrs.wait_seconds = 5;

	printf("Starting the thread...\n");

	DWORD dwTID;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcedure, &thrs, NULL, &dwTID);

	for(int i = 0; i < 20; i++)
	{
		printf(".");
		Sleep(250);
	}

	WaitForSingleObject(hThread, INFINITE);
	printf("The other thread has finished\n");

	getch();

	return 0;
}

