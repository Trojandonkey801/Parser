#include <stdio.h>
#include <semaphore.h>
struct BEACON
{
	int ID;
	int startUpTime;
	int timeInterval;
	char IP[4];
	int cmdPort;
};

void BeaconSender();
void CmdAgent();
void GetLocalOS(char OS[16], int *valid);
void GetLocalTime(int *time, int *valid);
