// External Libraries

// System Files
#include "Base.h"

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
	logSender = new UDPSender((char*)LOGGER_IP, LOGGER_PORT);
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
