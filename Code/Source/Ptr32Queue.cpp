//TODO: Currently coded for Linux only!

//
// NOTE: the following queue is implemented as a circular-queue, though those
// details are abstracted from the user
//


// System Libraries
#include "../Include/RtscConfig.h"
#include "../Include/Ptr32Queue.h"

// External Libraries
#include <string.h>
#include <iostream>

// Class Mutexes
pthread_mutex_t myQueueMutex;

// 
//
// 
Ptr32Queue::Ptr32Queue(int size, char* name):
	qSize(0),
    numQueuedElements(0),
	dequeueIndex(0),
    enqueueIndex(0),
	Q(0)
{
    // store provided q name
    qName = (char*)malloc(MAX_CLASSNAME_LENGTH * sizeof(char));
    strcpy(qName, name);

	// Save the size passed in
    qSize = size;

	// create the queue data area
    Q = (char**) malloc(qSize * sizeof(char*));
    if (Q == 0)
    {
        //TODO: ERROR log here
        return;
	}
}

// 
//
// 
Ptr32Queue::~Ptr32Queue(void)
{
    if (Q != 0)
	{
		delete Q;
		Q = 0;
	}

    free(qName);

    pthread_mutex_destroy(&myQueueMutex);
}

//
//
// 
bool Ptr32Queue::Dequeue(char** data)
{
	bool success = false;

    // synchronize the read
    pthread_mutex_lock(&myQueueMutex);

    // ensure that the queue is not empty
    if (dequeueIndex != enqueueIndex)
    {
        *data = Q[dequeueIndex];
        dequeueIndex = NextIndex(dequeueIndex);
        numQueuedElements--;
		success = true;
    }

    // release the mutex
    pthread_mutex_unlock(&myQueueMutex);

	return success;
}

// 
//
// 
bool Ptr32Queue::Enqueue(char* data)
{
	bool success = false;

    // synchronize the write
    pthread_mutex_lock(&myQueueMutex);

    // ensure that the queue is not full
    if (NextIndex(enqueueIndex) != dequeueIndex)
    { 
        Q[enqueueIndex] = data;
        enqueueIndex = NextIndex(enqueueIndex);
        numQueuedElements++;
		success = true;
    }

    // release the mutex
    pthread_mutex_unlock(&myQueueMutex);

	return success;
}


// 
//
// 
bool Ptr32Queue::IsFull(void)
{
    bool fullFlag = false;

    // synchronize
    pthread_mutex_lock(&myQueueMutex);

    // the queue is full if an additional write would make the queue 
    // look like it was empty 
    int nextWriteIndex = NextIndex(enqueueIndex);
    if (nextWriteIndex == dequeueIndex)
    {
        fullFlag = true;
    }

    // release mutex
    pthread_mutex_unlock(&myQueueMutex);

    return fullFlag;

}

// 
//
// 
bool Ptr32Queue::IsEmpty(void)
{
    bool emptyFlag = false;

    // lock mutex
    pthread_mutex_lock(&myQueueMutex);

    if (dequeueIndex == enqueueIndex)
    {
        emptyFlag = true;
    }

    // release the mutex
    pthread_mutex_unlock(&myQueueMutex);

    return emptyFlag;
}

// 
//
// 
bool Ptr32Queue::EmptyQueue()
{
	bool emptyFlag = false;

    // lock mutex
    pthread_mutex_lock(&myQueueMutex);

	dequeueIndex = 0;
	enqueueIndex = 0;
    numQueuedElements = 0;
	emptyFlag = true;

    // release the mutex
    pthread_mutex_unlock(&myQueueMutex);

	return emptyFlag;
}

// 
//
// 
bool Ptr32Queue::GetOccupancy(int* occupancy)
{
    bool occupancyFlag = false;

    // lock mutex
    pthread_mutex_lock(&myQueueMutex);

    *occupancy = numQueuedElements;
    occupancyFlag = true;

    // release the mutex
    pthread_mutex_unlock(&myQueueMutex);

    return occupancyFlag;
}

// 
//
// 
int Ptr32Queue::NextIndex(int currentIndex)
{
    int next = currentIndex + 1;
    // check if next exceeds the queue size
    if (next >= qSize + 1)
    {
        next = 0;
    }

    return next;
}


