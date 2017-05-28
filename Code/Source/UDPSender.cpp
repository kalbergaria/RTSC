// External Libraries
#include <string.h>

// System Files
#include "../include/UDPSender.h"

//
//
// Private Default Constructor
UDPSender::UDPSender() {}

//
//
// Constructor
UDPSender::UDPSender(char* ipAddress, int portNumber)
{
	sockaddrSize = sizeof(struct sockaddr);
	destIPAddress = (char*)malloc(IPV4_ADDR_LENGTH*sizeof(char));
	strcpy(destIPAddress, ipAddress);
	strcat(destIPAddress, "\0");
	InitializeUDPSender(ipAddress, portNumber);
}

//
//
//
void UDPSender::InitializeUDPSender(const char* ipAddress, int portNumber)
{
	if ((mySocket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		printf("UDPSender: error creating socket!\n");

	destinationAddr.sin_family = AF_INET;
	destinationAddr.sin_port = htons(portNumber);
	destinationAddr.sin_addr.s_addr = inet_addr(ipAddress);
	bzero(&(destinationAddr.sin_zero), 8);
}

//
//
// Send obstruction data across the network to the display pi
void UDPSender::SendMSG(char* msg, int msgSize)
{
	//printf("Sending data to ip: %s...\n", destIPAddress);
	sendto(mySocket, msg, msgSize, 0, (const struct sockaddr *)&destinationAddr, sockaddrSize);
}

void UDPSender::SendMSG(LDATA* msg, int msgSize)
{
	//printf("Sending data to ip: %s...\n", destIPAddress);
	/*for(int i=0; i<IDEAL_NUM_SAMPLES; i++)
	{
		printf("%1.2f ", msg[i].ldet[0]);
	}
	printf("\n");*/
	sendto(mySocket, msg, msgSize, 0, (const struct sockaddr *)&destinationAddr, sockaddrSize);
}