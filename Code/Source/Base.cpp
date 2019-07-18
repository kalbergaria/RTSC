// System Files
#include "Base.h"
#include "RtscConfig.h"

// External Libraries

//
//
//
Base::Base()
{
	// Allocate memory for the class name
	myClassName = (char*)malloc(MAX_CLASSNAME_LENGTH * sizeof(char));

	// Allocted memory for a log messge
	myLogMessage = new LogMsg();

	// Instantiate the UdpSender for logging, IP and Port parameters
	// are those specified in the Config.rtsc file.
	logSender = new UdpSender((char*)DISPLAY_AND_LOGGER_IP, DISPLAY_AND_LOGGER_PORT);
}

//
//
//
Base::~Base()
{
	free(myClassName);
	delete(myLogMessage);
	delete(logSender);
}

//
//
//
void Base::SendToLogger()
{
	// Send the data currently in the classes log message
	// to the logger
	logSender->SendMSG((char*)myLogMessage, sizeof(LogMsg));
}

/*
Maximum Line Size
<=======================================================================>
*/
