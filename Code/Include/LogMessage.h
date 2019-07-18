#ifndef LOG_MSG_H
#define LOG_MSG_H

// System Files
#include "Global.h"
#include "UDPHeader.h"

///////////////////////////////////////////////////////////
// Log Message Contents
///////////////////////////////////////////////////////////
struct LogMsg
{
	UDPHeader UDP_MSGHeader;
    LogLevel msgLevel;
    char className[MAX_CLASSNAME_LENGTH];
    char logString[MAX_LOG_STRING_LENGTH];
};

#endif

/*
Maximum Line Size
<=======================================================================>
*/