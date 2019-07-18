//TODO: Currently coded for Linux only!

#ifndef UDP_RECEIVER_H
#define UDP_RECEIVER_H

// System Libraries
#include "../Include/Global.h"
#include "../Include/ThreadBase.h"
#include "../Include/Ptr32Queue.h"

// External Libraries
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class UdpReceiver : public ThreadBase
{
	public:
		UdpReceiver(int providedPortNumber, int providedBufferSize, int providedNumBuffers, char* owningClass, char* myIP);
		~UdpReceiver();

		//public methods
		void InitializeUdpReceiver();
		void ThreadMethod();
		bool GetDataBuffer(char** tempBufferPtr);
		bool ReleaseDataBuffer(char* tempBufferPtr);

		// public data
		int portNumber;
		int numBuffers;
		int bufferSize;
		char** dataBuffers;
		int qSize;

	private:
		// default constructor is private so that it cannot be called
		// to instantiate the class
		UdpReceiver();

		// private methods
		void ReceiveData();
		void ResyncFreeQAndDataQIfNecessary();
        void ConcatCharArraysAndAddNullChar(char* dest, const char* src);

		// private data
		char* receiverOwner;
		Ptr32Queue* freeQ;
		char freeQName[MAX_CLASSNAME_LENGTH];
		Ptr32Queue* dataQ;
		char dataQName[MAX_CLASSNAME_LENGTH];
		char* bufferBeingFilled;
		int mySocket;
		int port;
		int bytesRead;
		unsigned int sockaddrSize;
		struct sockaddr_in destinationAddr, sourceAddr;
		char dataReceived[MAX_UDP_DATA_SIZE];
};

#endif
