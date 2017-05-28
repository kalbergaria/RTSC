#ifndef CMSN_LOGGER_H
#define CMSN_LOGGER_H

// Extrernal Files
#include <fstream>

// System Files
#include "../include/Global.h"
#include "../include/ThreadBase.h"
#include "../include/UDPReceiver.h"

class CMSNLogger : public ThreadBase
{
  public:
    CMSNLogger(UDPReceiver* UDPReceiverPtr);
	  void ThreadMethod();
    void WriteToLog();
    void CreateNewLog();

  private:
    // private default constructor, so it cannot be called
    CMSNLogger();
    void WriteCharArrayToLog(char* array, int arrayLength);

    // private data
    struct timespec logMSGTimestamp;
    ofstream logFile;
    char logFileName[LOG_PATH_LENGTH];
    LogMSG* logMessage;
    UDPReceiver* loggingUDPReceiver;
};

#endif
