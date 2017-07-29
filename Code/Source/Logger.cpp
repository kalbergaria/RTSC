//TODO: Currently coded for Linux only!

// External Libraries
#include <time.h>

// System Files
#include "../Include/Logger.h"
#include "../Include/RtscTiming.h"

//
//
// Private Default Constructor
Logger::Logger() {}

//
//
// Constructor
Logger::Logger(UDPReceiver* UDPReceiverPtr)
{
	strcpy(myClassName, "Logger");

	loggingUDPReceiver = UDPReceiverPtr;

	// create log file name
	time_t now;
	now = time(NULL);
	logFileName[0] = '\0';
	if (now != -1)
		strftime(logFileName, LOG_PATH_LENGTH, "Logs/%m-%d-%y_%H:%M:%S.log", gmtime(&now));

	// Create file for writing
	logFile.open(logFileName, ios::out);

	// Prep logMSG and log that the class has been created
	strcpy(myLogMessage->UDP_MSGHeader.source, DISPLAY_AND_LOGGER_IP);
	strcpy(myLogMessage->UDP_MSGHeader.destination, DISPLAY_AND_LOGGER_IP);
	strcpy(myLogMessage->className, myClassName);
	myLogMessage->msgLevel = CLASS_CREATION;
	SendToLogger();

	#if AUTO_OPEN_LOG == true
	    if(fork() == 0)
		{
			system("./../scripts/LaunchGloggWithLatestLog.sh 2> /dev/null");
			exit(0);
		}
	#endif
}

//
//
// Default Destructor
Logger::~Logger()
{

}

// Logging
void Logger::ThreadMethod()
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
void Logger::WriteToLog()
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

	// Print anything else about what is being logged
	if(logMessage->logString[0] != '\0' || logMessage->logString[0] != 0)
		logFile << " ---> ";
	WriteCharArrayToLog(logMessage->logString, MAX_LOG_STRING_LENGTH);

	logFile << endl;
}

//
//
//
void Logger::WriteCharArrayToLog(char* array, int arrayLength)
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