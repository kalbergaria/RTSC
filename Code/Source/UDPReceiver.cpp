// External Libraries

// System Files
#include "../include/UDPReceiver.h"

//
//
// Default Constructor
UDPReceiver::UDPReceiver() {}

//
//
// Constructor
UDPReceiver::UDPReceiver(int providedPortNumber, int providedBufferSize, int providedNumBuffers, char* owningClass, char* myIP)
{
	strcpy(myClassName, "-Receiver");

	receiverOwner = (char*)malloc(MAX_CLASSNAME_LENGTH * sizeof(char));
	strcpy(receiverOwner, owningClass);
	ConcatCharArraysAndAddNullChar(receiverOwner, myClassName);

	// Init receiver
	sockaddrSize = sizeof(struct sockaddr);
	portNumber = providedPortNumber;
	InitializeUDPReceiver(providedPortNumber);

	// Record buffer and queue specs
	numBuffers = providedNumBuffers;
	qSize = providedNumBuffers;
	bufferSize = providedBufferSize;

	// Create data destination synchronization queues
	strcpy(dataQName, receiverOwner);
	strcpy(freeQName, receiverOwner);
	ConcatCharArraysAndAddNullChar(dataQName, " dataQ");
	ConcatCharArraysAndAddNullChar(freeQName, " freeQ");
	dataQ = new CharPtrQueue(providedNumBuffers, dataQName);
	freeQ = new CharPtrQueue(providedNumBuffers, freeQName);

	// Dynamically allocate space for the user-defined buffers
	dataBuffers = (char**)malloc(numBuffers * sizeof(char*));
	for (int bufferIndex = 0; bufferIndex < numBuffers; bufferIndex++)
	{
		dataBuffers[bufferIndex] = (char*)malloc(bufferSize * sizeof(char));
		freeQ->Enqueue(dataBuffers[bufferIndex]);
	}

	// Prep logMSG and log that the class has been created
	strcpy(myLogMessage->UDP_MSGHeader.source, myIP);
	strcpy(myLogMessage->UDP_MSGHeader.destination, DISPLAY_AND_LOGGER_IP);
	strcpy(myLogMessage->className, receiverOwner);
	myLogMessage->msgLevel = CLASS_CREATION;
	myLogMessage->deviceRole = DISPLAY_UNIT;
	myLogMessage->logString[0] = '\0';
	SendToLogger();
}

//
//
//
void UDPReceiver::InitializeUDPReceiver(int portNumber)
{sprintf(myLogMessage->logString, "Sample obtained and queued in %s", LIDAR_PI_IP20);
	if ((mySocket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		printf("UDPReceiver: error creating socket!\n");

	destinationAddr.sin_family = AF_INET;
	destinationAddr.sin_port = htons(portNumber);
	destinationAddr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(destinationAddr.sin_zero), 8);

	if (bind(mySocket, (struct sockaddr *)&destinationAddr, sizeof(struct sockaddr)) == -1)
		printf("UDPReceiver: Binding error");
}

//
//
//
void UDPReceiver::ThreadMethod()
{
	while (true)
	{
		ReceiveData();
	}
}

//
//
// Receive obstruction data from the LIDAR Pis
void UDPReceiver::ReceiveData()
{
	//printf("Waiting for a message on port %d...\n", portNumber);
	
	// If there are no additional buffers available, resynchronize with the
	// data destination by emptying the dataQ
	ResyncFreeQAndDataQ();

	// Reserve a buffer to place the incoming data
	freeQ->Dequeue(&bufferBeingFilled);

	// Receive data and place in buffer
	bytesRead = recvfrom(mySocket, bufferBeingFilled, bufferSize, 0, (struct sockaddr *)&sourceAddr, &sockaddrSize);
	// TODO: Error handling needed here...
	
	// to check if sample data stuctures are coming across the network properly
	#if debug3 == true
	LDATA_UDP_MSG* tempObsMsg = (LDATA_UDP_MSG*)bufferBeingFilled;
	for (int currentSample = 0; currentSample < NUM_SAMPLES_PER_ROTATION; currentSample++)
	{
			printf("ShortestObject: %1.2f\n", tempObsMsg[currentSample].ldet[0]);
	}
	#endif

	// Now that the buffer has been filled place it in the dataQ
	dataQ->Enqueue(bufferBeingFilled);
}

//
//
//
// TODO: What type does this need to be in order for me to be able to
// pass to return a char* two layers up?
bool UDPReceiver::GetDataBuffer(char** tempBufferPtr)
{
	bool dequeueFlag = false;

	if(!dataQ->IsEmpty())
	{
		dataQ->Dequeue(tempBufferPtr);
		dequeueFlag = true;
	}

	return dequeueFlag;
}

//
//
//
bool UDPReceiver::ReleaseDataBuffer(char* tempBufferPtr)
{
	return freeQ->Enqueue(tempBufferPtr);
}

//
//
//
void UDPReceiver::ResyncFreeQAndDataQ()
{
	if(freeQ->IsEmpty())
	{
		for (int elementNum = 0; elementNum < qSize; elementNum++)
		{
			dataQ->Dequeue(&bufferBeingFilled);
			freeQ->Enqueue(bufferBeingFilled);
		}
		myLogMessage->msgLevel = ERROR;
		strcpy(myLogMessage->logString, "freeQ and DataQ resynchronization was required!");
		SendToLogger();
	}
}