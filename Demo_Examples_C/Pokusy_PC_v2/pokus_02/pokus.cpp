#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#include "SimConnect.h"

void vario_request_handling(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData);
void simobject_data_handling(SIMCONNECT_RECV* pData);
void CALLBACK my_dispatch(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext);
void main_loop(void);
void close_connection(void);
void open_connection(void);
void init_variables(void);
void exception_handling(void);
void event_handling(void);
void quit_handling(void);
void open_handling(void);
void nav_active_freq_1_request_handling(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData);

HANDLE  hSimConnect = NULL;

static enum DATA_DEFINE_ID {
    DEFINITION_PDR,
};

static enum DATA_NAMES {
	NAV_ACTIVE_FREQUENCY_1,
    DATA_VERTICAL_SPEED,
    DATA_PITOT_HEAT,
};

static enum EVENT_PDR {
    EVENT_SIM_START,
};

static enum REQUEST_ENUM 
{
    VARIO_REQUEST,
	NAV_ACTIVE_FREQ_1_REQUEST
};

static enum DEFINITION_ENUM 
{
    DEFINITION,
};

struct StructOneDatum {
    int        id;
    float    value;
};

struct ReceivedData 
{
    float hodnota_1;
	float hodnota_2;
};

struct ReceivedData_int 
{
	char freq[16];
};

int main(void)
{
	open_connection();

	init_variables();
	
	main_loop();

	close_connection();

	return 0;
}

void init_variables(void)
{
    //SimConnect_AddToDataDefinition(hSimConnect, DEFINITION, "Vertical Speed", "feet/minute", SIMCONNECT_DATATYPE_FLOAT32, 0, DATA_VERTICAL_SPEED);
	SimConnect_AddToDataDefinition(hSimConnect, DEFINITION, "NAV ACTIVE FREQUENCY:1", "MHz", SIMCONNECT_DATATYPE_FLOAT64, 0, NAV_ACTIVE_FREQUENCY_1);

	//SimConnect_RequestDataOnSimObject(hSimConnect, VARIO_REQUEST, DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND);
	SimConnect_RequestDataOnSimObject(hSimConnect, NAV_ACTIVE_FREQ_1_REQUEST, DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND);
}

void open_connection(void)
{
	HRESULT hr;
	hr = SimConnect_Open(&hSimConnect, "", NULL, 0, 0, 0);

	switch (hr)
	{
		case S_OK:         
		{ 
			printf("Connection successful!\n"); 
			break; 
		}
		case E_FAIL:
		{
			printf("Connection failed!\n");
			exit(1);			
		}
		case E_INVALIDARG: 
		{
			printf("A SimConnect section in the Simconnect.cfg file did not contain\n");
			printf("the config index requested in the parameters.\n");
			exit(1);
		}
		default: 
		{
			printf("Unknown error!\n");
			exit(1);
		}
	}
}

void close_connection(void)
{
	SimConnect_Close(hSimConnect);
	printf("Connection closed.");
}

void main_loop(void)
{
	while (true)
    {
	    SimConnect_CallDispatch(hSimConnect, my_dispatch, NULL);
        Sleep(1);
    } 
}

void CALLBACK my_dispatch(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext)
{
	switch (pData->dwID)
    {
		//case SIMCONNECT_RECV_ID_NULL: break;

		case SIMCONNECT_RECV_ID_EXCEPTION:      { exception_handling();           break; }
		case SIMCONNECT_RECV_ID_OPEN:           { open_handling();                break; }
		case SIMCONNECT_RECV_ID_QUIT:           { quit_handling();                break; }
        case SIMCONNECT_RECV_ID_EVENT:          { event_handling();               break; }
		//case SIMCONNECT_RECV_ID_EVENT_OBJECT_ADDREMOVE break;
		//case SIMCONNECT_RECV_ID_EVENT_FILENAME break;
		//case SIMCONNECT_RECV_ID_EVENT_FRAME break;
		case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:	{ simobject_data_handling(pData); break; }
/*
		case SIMCONNECT_RECV_ID_SIMOBJECT_DATA_BYTYPE break;
		case SIMCONNECT_RECV_ID_CLOUD_STATE break;
		case SIMCONNECT_RECV_ID_WEATHER_OBSERVATION break;
		case SIMCONNECT_RECV_ID_ASSIGNED_OJBECT_ID break;
		case SIMCONNECT_RECV_ID_RESERVED_KEY break;
		case SIMCONNECT_RECV_ID_CUSTOM_ACTION break;
		case SIMCONNECT_RECV_ID_SYSTEM_STATE break;
		case SIMCONNECT_RECV_ID_CLIENT_DATA break;
		case SIMCONNECT_RECV_ID_EVENT_WEATHER_MODE break;
		case SIMCONNECT_RECV_ID_AIRPORT_LIST break;
		case SIMCONNECT_RECV_ID_VOR_LIST break;
		case SIMCONNECT_RECV_ID_NDB_LIST break;@
		case SIMCONNECT_RECV_ID_WAYPOINT_LIST break;
		case SIMCONNECT_RECV_ID_EVENT_MULTIPLAYER_SERVER_STARTED break;
		case SIMCONNECT_RECV_ID_EVENT_MULTIPLAYER_CLIENT_STARTED break;
		case SIMCONNECT_RECV_ID_EVENT_MULTIPLAYER_SESSION_ENDED break;
		case SIMCONNECT_RECV_ID_EVENT_RACE_END break;
		case SIMCONNECT_RECV_ID_EVENT_RACE_LAP break;
*/
		default: printf("ERROR: my_dispatch(): dwID = %d\n", pData->dwID);
	}
}

void simobject_data_handling(SIMCONNECT_RECV* pData)
{
	//printf("DEBUG:simobject_data_handling");
	SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*) pData;
	switch (pObjData->dwRequestID)
	{
		case VARIO_REQUEST:             { vario_request_handling(pObjData);             break; }
		case NAV_ACTIVE_FREQ_1_REQUEST: { nav_active_freq_1_request_handling(pObjData); break; }
		default: printf("ERROR!!! dwRequestID = %d", pObjData->dwRequestID);
	}
}

void exception_handling(void)
{
	printf("exception_handling");
}

void open_handling(void)
{
	printf("open_handling()\n");
}

void event_handling(void)
{
	//SIMCONNECT_RECV_EVENT *evt = (SIMCONNECT_RECV_EVENT*)pData;

}

void quit_handling(void)
{
	printf("quit_handling");
}

void vario_request_handling(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData)
{
	float vario1, vario2;

	//printf("DEBUG:vario_request_handling");
	//printf(" velkost float = %d ", sizeof(float));
	//printf("dwDefineCount = %d\n\n", pObjData->dwDefineCount);

	ReceivedData* data = (ReceivedData*) &pObjData->dwData;

	vario1 = data->hodnota_1;
	vario2 = data->hodnota_2;

	//printf("\rvario1 = %f vario2 = %f ", vario1, vario2);
}

void nav_active_freq_1_request_handling(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData)
{
	ReceivedData_int* data = (ReceivedData_int*) &pObjData->dwData;

	//printf("char = %d", sizeof(char));

	//printf("dwDefineCount = %d ", pObjData->dwDefineCount);
	//printf("dwoutof = %d ", pObjData->dwoutof);

	//int frq = (int) (pObjData->dwData + 1);

	double dFrequency = *((double *) &pObjData->dwData);

		printf("%f ",  dFrequency);
/*
		printf("%x ", pObjData->dwData + 1);
		printf("%x ", pObjData->dwData + 2);
		printf("%x ", pObjData->dwData + 3);
*/
/*	
	for (int i = 0; i < 8; i++)
	{
		printf("%x ", pObjData->dwData + i);
	}
*/	
//	while (true)	;
	printf("\r");
}