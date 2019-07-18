//TODO: Currently coded for Linux only!

#ifndef LOGGER_H
#define LOGGER_H

// System Files
#include "../Include/Global.h"
#include "../Include/ThreadBase.h"
#include "../Include/UDPReceiver.h"

// Extrernal Files
#include <fstream>

class Logger : public ThreadBase
{
  public:
    Logger(UdpReceiver* UdpReceiverPtr);
    ~Logger();
    void ThreadMethod();
    void WriteToLog();
    void CreateNewLog();

  private:
    // private default constructor, so it cannot be called
    Logger();
    void WriteCharArrayToLog(char* array, int arrayLength);

    // private data
    struct timespec logMsgTimestamp;
    ofstream logFile;
    char logFileName[LOG_PATH_LENGTH];
    LogMsg* logMessage;
    UDPReceiver* loggingUdpReceiver;
};

#endif
