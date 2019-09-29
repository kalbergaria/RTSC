//TODO: Currently coded for Linux only!

#ifndef LOGGER_H
#define LOGGER_H

// System Files
#include "../Include/Global.h"
#include "../Include/ThreadBase.h"
#include "../Include/UdpReceiver.h"
#include "../Include/Ptr32Queue.h"

// Extrernal Files


// External Namespaces

class Logger : public ThreadBase
{
	enum LoggerType
	{
		LOCAL,
		UDP
	};

	enum LogLevel
	{
		LOG_CLASS_CREATION,
		LOG INFO,
		LOG_WARNING,
		LOG_ERROR,
		LOG_FATAL,
		LOG_UNKOWN
	};

public:
	Logger(LoggerType type, string baseFileName);
	Logger(UdpReceiver *UdpReceiverPtr);
	~Logger();
	void ThreadMethod();
	void WriteToLog(char* logString);
	void CreateNewLog();

private:
	FILE* logFile;
	Pts32Queue* logQueue;
	LoggerType type;

	void WriteCharArrayToLog(char *array, int arrayLength);

	// private data
	struct timespec LogMsgTimestamp;
	ofstream logFile;
	char logFileName[LOG_PATH_LENGTH];
	LogMsg *logMessage;
	UdpReceiver *loggingUdpReceiver;
};

#endif
