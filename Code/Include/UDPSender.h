#ifndef UDP_SENDER_H
#define UDP_SENDER_H

// External Files
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// System Files
#include "../include/Global.h"
#include "../include/CMSNTypes.h"

class UDPSender
{
	public:
		UDPSender(char* ipAddress, int portNumber);
		void SendMSG(char* msg, int msgSize);
		void SendMSG(LDATA* msg, int msgSize);

	private:
		// privte constructor
		UDPSender();

		// private methods
		void InitializeUDPSender(const char* ipAddress, int portNumber);

		// private data
		int mySocket;
		int port;
		int bytesRead;
		char* destIPAddress;
		unsigned int sockaddrSize;
		struct sockaddr_in destinationAddr;
		char dataToSend[MAX_UDP_DATA_SIZE];
};

#endif
