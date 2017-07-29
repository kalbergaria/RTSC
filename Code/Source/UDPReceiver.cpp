//TODO: Currently coded for Linux only!

// External Libraries

// System Files
#include "../Include/UDPReceiver.h"

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
	//ConcatCharArraysAndAddNullChar(receiverOwner, myClassName);
    // TODO: Find this function in CMSN

	// Init receiver
	sockaddrSize = sizeof(struct sockaddr);
	portNumber = providedPortNumber;

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
	myLogMessage->logString[0] = '\0';
	SendToLogger();
}

//
//
// Default Constructor
UDPReceiver::~UDPReceiver()
{
	free(receiverOwner);
	delete(dataQ);
	delete(freeQ);
	free(dataBuffers);
}

//
//
//
void UDPReceiver::InitializeUDPReceiver()
{
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
//
void UDPReceiver::ReceiveData()
{
	// If there are no additional buffers available, resynchronize with the
	// data destination by emptying the dataQ
	ResyncFreeQAndDataQIfNecessary();

	// Reserve a buffer to place the incoming data
	freeQ->Dequeue(&bufferBeingFilled);

	// Receive data and place in buffer
	bytesRead = recvfrom(mySocket, bufferBeingFilled, bufferSize, 0, (struct sockaddr *)&sourceAddr, &sockaddrSize);
	// TODO: Error handling needed here...

	// Now that the buffer has been filled place it in the dataQ
	dataQ->Enqueue(bufferBeingFilled);
}

//
//
//
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
void UDPReceiver::ResyncFreeQAndDataQIfNecessary()
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

void UDPReceiver::ConcatCharArraysAndAddNullChar(char* dest, const char* src)
{
    strcat(dest, src);
    dest[strlen(dest)+strlen(src)+1] = '\0';
}