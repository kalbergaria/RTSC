//TODO: Currently coded for Linux only!

// System Files
#include "UdpSender.h"

// External Libraries

//
//
//
UdpSender::UdpSender() {}

//
//
//
UdpSender::UdpSender(char* ipAddress, int portNumber)
{
	#ifdef RTSC_LINUX
		sockaddrSize = sizeof(struct sockaddr);
		destIPAddress = (char*)malloc(IPV4_ADDR_LENGTH*sizeof(char));
		strcpy(destIPAddress, ipAddress);
		strcat(destIPAddress, "\0");

		if ((mySocket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
			printf("UdpSender: error creating socket!\n");

		destinationAddr.sin_family = AF_INET;
		destinationAddr.sin_port = htons(portNumber);
		destinationAddr.sin_addr.s_addr = inet_addr(ipAddress);
		bzero(&(destinationAddr.sin_zero), 8);
	#endif
}

//
//
//
void UdpSender::SendMSG(char* msg, int msgSize)
{
	#ifdef RTSC_LINUX
		sendto(mySocket, msg, msgSize, 0, 
			   (const struct sockaddr *)&destinationAddr, sockaddrSize);
	#endif
}

/*
Maximum Line Size
<=======================================================================>
*/