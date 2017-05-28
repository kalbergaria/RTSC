// External Libraries
#include <stdio.h>

// System Files
#include "../include/ThreadBase.h"
// Are the includes not inherited from CMSNBase?
#include "../include/Debug.h"

// Prototypes
// Exists so that this method name can be re-defined in the child class
// Used in the StartThread function
void* THREAD_METHOD(void* lpParam);

// Class Mutexes
pthread_mutex_t ThreadStartMutex;

// Default Constructor
ThreadBase::ThreadBase() {}

// Function to starts the thread of the  thread
bool ThreadBase::StartThread()
{
    DB3_2strings(myClassName, ": started thread");

	int retVal = pthread_create(&threadHandle, NULL, THREAD_METHOD, (void*)this);
    if (retVal != 0)
    {
		DB1_2strings(myClassName, ": could not start thread.");
        return false;
    }

	//
	// log that the thread has been started
	//

	return true;
}

void* THREAD_METHOD(void* lpParam)
{
    ThreadBase * myClass = (ThreadBase *) lpParam;

    myClass->ThreadMethod();

    return 0;
}