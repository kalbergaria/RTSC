//TODO: Currently coded for Linux only!

// External Libraries
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// System Files
#include "../Include/Logger.h"
#include "../Include/RtscTiming.h"

//
//
// Constructor
Logger::Logger(LoggerType type, string baseFileName)
{
	this->type = type;
	switch(this->type)
	{
		case LOCAL:
			// create log filename
			unsigned long long rdtsc = getRdtsc();
			if (rdtsc > 0)
			{
				string fileName = baseFileName + to_string(rdtsc);
				
				// Create file for writing
				logFile = fopen(logFileName, "W");
				if (logFile == NULL)
				{

				}
			}
			else
			{
				cout << "Error creating log file... exiting..." << endl;
				exit(0);
			}
	
		break;

		case UDP:
		break;

		default:
		break;
	}
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
	char* logString;

	// Checks the logQueue for log stirngs, if there are none it sleeps 10ms
	// the retries, otherwise it writes each available log string to the file
	while(true)
	{
		if (!logQueue->isEmpty)
		{
			logQueue->Dequeue((char**)& logString);
			WriteToLog(logString);
		}
		else
		{
			usleep(1000); // 10ms
		}
	}
}

//
//
// Write to the system log
void Logger::WriteToLog(char* logString, LogLevel logLevel)
{
	// Print the timestamp at the head of the line
	unsigned long long rdtsc = getRdtsc();
	logFile << "[" << to_string(rdtsc) << "]: ";

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