#ifndef CMSN_BASE_H
#define CMSN_BASE_H

// External Files
#include <string>

// System Files
#include "../include/UDPSender.h"
#include "../include/LogMSG.h"
#include "../include/CMSNTypes.h"

using namespace std;

class CMSNBase
{
  public:
    CMSNBase();
    void SendToLogger();
    void ConcatCharArraysAndAddNullChar(char* dest, const char* src);
    void WriteStringtoCharArray(char* array, string str);

  protected:
    UDPSender* logSender;
    LogMSG* myLogMessage;
    char* myClassName;
};

#endif