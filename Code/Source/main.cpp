// External Libraries
#include <stdlib.h>
#include <unistd.h>

// System Files
#include "../include/Global.h"
#include "../include/UDPSender.h"
#include "../include/ThreadManager.h"
#include "../include/CMSNTiming.h"

// Prototypes
void PrintMissingInputError();

struct timespec _START_TIME_;

int main(int argc, char** argv)
{	
	// clear the terminal window as program starts
	system("clear");

	//printf("START CMSN");
	// Disable cout calls if specified in DebugState.h
	#if COUT_ON == false 
		std::cout.setstate(std::ios_base::failbit);
	#endif

	//////////////////////////////////////////////////////
	//SET _START_TIME_ GLOBAL.
	clock_gettime(CLOCK_REALTIME, &_START_TIME_);
	/////////////////////////////////////////////////////
	//START GPIO Library
	#if RUNNING_ON_PI == true
		wiringPiSetup();
	#endif
	/////////////////////////////////////////////////////
	
	// Check if none, or too many arguments provided
	if (argc <= 1 || argc > 3)
	{
		printf("here argc=%d\n", argc);
		PrintMissingInputError();
		return -1;
	}

	// Instantiate the ThreadManager class
	DB3("Instantiating Thread Manager");
	ThreadManager* myThreadManager = ThreadManager::getInstance();

	switch (argv[1][0])
	{
		// If running on a LIDAR pi
		case 'L':
			// Check if first parameter is L but no ip is provided as
			// a second parameter
			if(argc == 2)
			{
				PrintMissingInputError();
				return -1;
			}
			
			myThreadManager->StartAllThreads_LIDAR_Pi(argv[2]);
			break;

		// If running on the Display pi
		case 'D':
			myThreadManager->StartAllThreads_Display_Pi();
			break;

		// for Debug
		case 'B':
			myThreadManager->StartAllThreads_Debug();
			break;

		default:
			printf("ERROR: Invalid input entered!\n");
			PrintMissingInputError();
			return 0;
			break;
	}

	// initialize timing variables for loop
	//struct timespec startTime;
	//struct timespec iterationStopTime;
	
	int count = 0;
	while (true)
	{
		usleep(10000000); // 10 seconds
		count++;
		//clock_gettime(CLOCK_REALTIME, &startTime);
		//SleepRemainingIterationDuration(&startTime, 10000000, 10000);
		//clock_gettime(CLOCK_REALTIME, &iterationStopTime);

		//cout << "Start time: " << TimespecConcatTimeConvert2us(&startTime) << endl;
		//cout << "Iteration stop time: " << TimespecConcatTimeConvert2us(&iterationStopTime) << endl;
		//printf("Current count: %d seconds\n", count*10);
	}

	DB3("exiting...");
}

void PrintMissingInputError()
{
	printf("To execute this program enter one of the following characters as the first parameter:\n");
	printf("'L' if running on a LIDAR Raspberry Pi\n");
	printf("'D' if running on the Display Raspberry Pi\n");
	printf("'B' for debug mode\n");
	printf("NOTE: If running on a LIDAR Pi provide the full IP Address of the pi as a second parameter.\n");
}
