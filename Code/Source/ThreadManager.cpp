// External Libraries

// System Files
#include "../include/ThreadManager.h"
#include "../include/VehicleObstructions.h"
#include "../include/LIDAR.h"
#include "../include/UDPReceiver.h"
#include "../include/DNSCommsWrapper.h"
#include "../include/DispObsProc.h"
#include "../include/CMSNLogger.h"
#include "../include/CMSNTypes.h" //TODO: don't want to include this
#include "../include/MergeAndCollapse.h"

#if RUNNING_ON_PI == true
#include "Tachometer.h"
#endif

// Pointer to the global instance of this class
ThreadManager* ThreadManager::threadManagerInstance = NULL;

// Class Mutexes
pthread_mutex_t ThreadManager_GET_INSTANCE;
pthread_mutex_t ThreadManager_DESTRUCTOR;

// Private Default Constructor
ThreadManager::ThreadManager() 
{
	strcpy(myClassName, "Thread Manager");
}

/*---------------------------------------------------------------*/
// Create and returns (if an instance has not already been created) OR simply 
// returns, the only instance of the class
ThreadManager* ThreadManager::getInstance()
{
	// synchronization
	pthread_mutex_lock(&ThreadManager_GET_INSTANCE);

	// if the class not been instantiated, instantiate it
	// double-checked locking (in case of threads compete to instantiate)
	if (threadManagerInstance == NULL)
		if (threadManagerInstance == NULL)
			threadManagerInstance = new ThreadManager();

	// release the MUTEX
	pthread_mutex_unlock(&ThreadManager_GET_INSTANCE);

	return(threadManagerInstance);
}

/*---------------------------------------------------------------*/
// Performs any tasks needed before nullifying the pointer to the only
// instance of this class
ThreadManager::~ThreadManager()
{
	// synchronization
	pthread_mutex_lock(&ThreadManager_DESTRUCTOR);

	if (threadManagerInstance != NULL)
	{

	}
	threadManagerInstance = NULL;

    // release the MUTEX
    pthread_mutex_unlock(&ThreadManager_DESTRUCTOR);
}

/*---------------------------------------------------------------*/
//
//
void ThreadManager::StartAllThreads_LIDAR_Pi(char* myIP)
{
	struct HATMSG
	{
		//UDPHeader UDP_MSGHeader;
		char reset[32];
	};
	//DB1("Executing StartAllThreads_LIDAR_Pi()...");

	
	// VehicleObstructions threading setup
	VehicleObstructions* myVehicleObstructions = VehicleObstructions::getInstance(myIP);
	myVehicleObstructions->StartThread();

	#if RUNNING_ON_PI == true
		// LIDAR threading setup
		LIDAR* myLIDAR = LIDAR::getInstance(myIP);
		myLIDAR->StartThread();

		// Tachometer threading setup
		tachReceiver = (char*)malloc(MAX_CLASSNAME_LENGTH*sizeof(char));
		strcpy(tachReceiver, "TACHReceiver");
		UDPReceiver* tachUDPReceiver = new UDPReceiver(HAT_RST_PORT, sizeof(HATMSG), 8, tachReceiver, (char*)&LIDAR_PI_IP20);
		tachUDPReceiver->StartThread();
		Tachometer* myTachometer = new Tachometer(tachUDPReceiver, myIP);
		myTachometer->StartThread();
	#endif
}

/*---------------------------------------------------------------*/
//
//
void ThreadManager::StartAllThreads_Display_Pi()
{
	//TODO: Remember tp put a delay in the start script for pis to ensure logger is functioning before they start
	//TODO: pick a better number of buffers, probably want it to be #define---------v
	loggingReceiver = (char*)malloc(MAX_CLASSNAME_LENGTH*sizeof(char));
	strcpy(loggingReceiver, "CMSNLogger");
	UDPReceiver* loggingUDPReceiver = new UDPReceiver(LOG_MSG_PORT, sizeof(LogMSG), 16, loggingReceiver, (char*)&DISPLAY_AND_LOGGER_IP);
	loggingUDPReceiver->StartThread();
	// Start the logger
	CMSNLogger* myLogger = new CMSNLogger(loggingUDPReceiver);
	myLogger->StartThread();

	//TODO: pick a better number of buffers, probably want it to be #define------------------v
	dispObsProcReceiver = (char*)malloc(MAX_CLASSNAME_LENGTH*sizeof(char));
	strcpy(dispObsProcReceiver, "DispObsProc");
	UDPReceiver* dispProcUDPReceiver = new UDPReceiver(OBS_MSG_PORT, sizeof(LDATA_UDP_MSG)*IDEAL_NUM_SAMPLES, 8, dispObsProcReceiver, (char*)&DISPLAY_AND_LOGGER_IP);
	dispProcUDPReceiver->StartThread();
	// Vehicle threading setup
	//TODO: pick a better number of buffers, probably want it to be #define----v
	DispObsProc* myDispObsProc = DispObsProc::getInstance(dispProcUDPReceiver, 4);
	myDispObsProc->StartThread();

	MergeAndCollapse* myMergeAndCollapse = new MergeAndCollapse();
	myMergeAndCollapse->StartThread();
}

/*---------------------------------------------------------------*/
//
//
void ThreadManager::StartAllThreads_Debug()
{

}
