// System Files
#include "Base.h"
// External Libraries

//
//
//
Base::Base()
{
	// Allocate memory for the class name
	myClassName = (char*)malloc(MAX_CLASSNAME_LENGTH * sizeof(char));

	// Allocted memory for a log messge
	myLogMessage = new LogMSG();

	// Instantiate the UDPSender for logging, IP and Port parameters
	// are those specified in the Config.rtsc file.
	logSender = new UDPSender((char*)DISPLAY_AND_LOGGER_IP, LOGGER_PORT);
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
	logSender->SendMSG((char*)myLogMessage, sizeof(LogMSG));
}

/*
Maximum Line Size
<=======================================================================>
*/
