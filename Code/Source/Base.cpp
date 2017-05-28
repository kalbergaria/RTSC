// External Libraries
#include <stdio.h>

// System Files
#include "../include/CMSNBase.h"

// Default Constructor
CMSNBase::CMSNBase() 
{
	myClassName = (char*)malloc(MAX_CLASSNAME_LENGTH * sizeof(char));

	myLogMessage = new LogMSG();
	logSender = new UDPSender((char*)DISPLAY_AND_LOGGER_IP, LOG_MSG_PORT);
}

//
//
//
void CMSNBase::WriteStringtoCharArray(char* array, string str)
{
	strncpy(array, (char*)&str, str.size());
	array[str.size() + 1] = '\0';
}

//
//
//
void CMSNBase::ConcatCharArraysAndAddNullChar(char* dest, const char* src)
{
	strcat(dest, src);
	dest[strlen(dest)+strlen(src)+1] = '\0';
}

// Sends the data the object would like to log to the CMSNLogger
void CMSNBase::SendToLogger()
{
	logSender->SendMSG((char*)myLogMessage, sizeof(LogMSG));
}
