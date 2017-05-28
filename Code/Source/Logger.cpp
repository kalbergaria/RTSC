// External Libraries
#include <time.h>

// System Files
#include "../include/CMSNLogger.h"
#include "../include/CMSNTiming.h"

//
//
// Private Default Constructor
CMSNLogger::CMSNLogger() {}

//
//
// Constructor
CMSNLogger::CMSNLogger(UDPReceiver* UDPReceiverPtr)
{
	strcpy(myClassName, "CMSNLogger");

	loggingUDPReceiver = UDPReceiverPtr;

	// create log file name
	time_t now;
	now = time(NULL);
	logFileName[0] = '\0';
	if (now != -1)
		strftime(logFileName, LOG_PATH_LENGTH, "../../../logs/%m-%d-%y_%H:%M:%S.log", gmtime(&now));

	// Create file for writing
	logFile.open(logFileName, ios::out);

	// Prep logMSG and log that the class has been created
	strcpy(myLogMessage->UDP_MSGHeader.source, DISPLAY_AND_LOGGER_IP);
	strcpy(myLogMessage->UDP_MSGHeader.destination, DISPLAY_AND_LOGGER_IP);
	strcpy(myLogMessage->className, myClassName);
	myLogMessage->msgLevel = CLASS_CREATION;
	myLogMessage->deviceRole = DISPLAY_UNIT;
	SendToLogger();

	#if AUTO_OPEN_LOG == true
	    if(fork() == 0)
		{
			system("./../scripts/LaunchGloggWithLatestLog.sh 2> /dev/null");
			exit(0);
		}
	#endif
}

// Logging
void CMSNLogger::ThreadMethod()
{
	// Checks for log messages, if there are none it re-checks every 10ms, otherwise
	// it writes the log message to the log file.
	while(true)
	{
		if(loggingUDPReceiver->GetDataBuffer((char**)&logMessage))
		{
			WriteToLog();
			loggingUDPReceiver->ReleaseDataBuffer((char*)logMessage);
		}
		else
		{
			usleep(1000); //10ms
		}
	}
}

//
//
// Write to the system log
void CMSNLogger::WriteToLog()
{
	// Print the timestamp at the head of the line
	clock_gettime(CLOCK_REALTIME, &logMSGTimestamp);
	logFile << "[" << TimespecConcatTimeConvert2us(&logMSGTimestamp) << "]: ";

	// Print the log level
	switch(logMessage->msgLevel)
	{
		case CLASS_CREATION:
			logFile << "CLASS CREATION: ";
			break;
			
		case INFO:
			logFile << "INFO: ";
			break;

		case WARNING:
			logFile << "WARNING: ";
			break;

		case ERROR:
			logFile << "ERROR: ";
			break;

		case FATAL:
			logFile << "FATAL: ";
			break;

		default:
			logFile << "UNKNOWN: ";
			break;
	}

	WriteCharArrayToLog(logMessage->className, MAX_CLASSNAME_LENGTH);
	
	// Print the device from which the message originated
	switch(logMessage->deviceRole)
	{
		case MOTOR_UNIT:
			logFile << "on MOTOR-pi ";
			break;
		case LIDAR_UNIT:
			logFile << " on LIDAR-pi ";
			// Print the ip address of the device if the device is a LIDAR pi
			// so that the messages source can be distinguished
			logFile << "[";
			WriteCharArrayToLog(logMessage->UDP_MSGHeader.source, IPV4_ADDR_LENGTH);
			logFile << "]";
			break;
		case DISPLAY_UNIT:
			logFile << " on DISPLAY-PC ";
			break;
		default:
			logFile << " on UNKNOWN-DEVICE ";
			break;
	}

	// Print anything else about what is being logged
	if(logMessage->logString[0] != '\0' || logMessage->logString[0] != 0)
		logFile << " ---> ";
	WriteCharArrayToLog(logMessage->logString, MAX_LOG_STRING_LENGTH);

	logFile << endl;
}

//
//
//
void CMSNLogger::WriteCharArrayToLog(char* array, int arrayLength)
{
	// Print the class name
	for(int charIndex = 0; charIndex < arrayLength; charIndex++)
	{
		if(array[charIndex] != '\0')
			logFile << array[charIndex];
		else
			break;
	}
}