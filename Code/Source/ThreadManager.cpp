//TODO: Currently coded for Linux only!

// System Files
#include "../Include/ThreadManager.h"
#include "../Include/UDPReceiver.h"
#include "../Include/Logger.h"


// External Libraries

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
	// double-checked locking (in case threads compete to instantiate)
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
		threadManagerInstance = NULL;

    // release and destroy MUTEX
	#ifdef RTSC_LINUX
    pthread_mutex_unlock(&ThreadManager_DESTRUCTOR);

	pthread_mutex_destroy(&ThreadManager_GET_INSTANCE);
	pthread_mutex_destroy(&ThreadManager_DESTRUCTOR);
	#endif
}

//
//
//
void ThreadManager::StartAllThreads()
{
	UDPReceiver* loggerUDPReceiver = new UDPReceiver(
			DISPLAY_AND_LOGGER_IP, sizeof(LogMSG),
			8, DISPLAY_AND_LOGGER_PORT);
	loggerUDPReceiver->StartThread();

	Logger* myLogger = new Logger(loggerUDPReceiver);
	myLogger->StartThread();
}

/*
Maximum Line Size
<=======================================================================>
*/
