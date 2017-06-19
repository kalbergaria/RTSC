// External Libraries

// System Files
#include "ThreadManager.h"

ThreadManager* ThreadManager::threadManagerInstance = NULL;

//
//
//
#ifdef RTSC_LINUX
pthread_mutex_t ThreadManager_GET_INSTANCE;
pthread_mutex_t ThreadManager_DESTRUCTOR;
#endif

//
//
//
ThreadManager::ThreadManager() 
{
	strcpy(myClassName, "Thread Manager");
}

//
//
//
ThreadManager* ThreadManager::getInstance()
{
	// synchronization
	#ifdef RTSC_LINUX
	pthread_mutex_lock(&ThreadManager_GET_INSTANCE);
	#endif

	// if the class not been instantiated, instantiate it
	// double-checked locking (in case of threads compete to instantiate)
	if (threadManagerInstance == NULL)
		if (threadManagerInstance == NULL)
			threadManagerInstance = new ThreadManager();

	// release the MUTEX
	#ifdef RTSC_LINUX
	pthread_mutex_unlock(&ThreadManager_GET_INSTANCE);
	#endif

	return threadManagerInstance;
}

//
//
//
ThreadManager::~ThreadManager()
{
	// synchronization
	#ifdef RTSC_LINUX
	pthread_mutex_lock(&ThreadManager_DESTRUCTOR);
	#endif

	if (threadManagerInstance != NULL)
	{

	}
	threadManagerInstance = NULL;

    // release the MUTEX
	#ifdef RTSC_LINUX
    pthread_mutex_unlock(&ThreadManager_DESTRUCTOR);
	#endif
}

//
//
//
void ThreadManager::StartAllThreads()
{

}

/*
Maximum Line Size
<=======================================================================>
*/
