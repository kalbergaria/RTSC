#ifndef BASE_H
#define BASE_H

// System Files
#include "Global.h"
#include "UDPSender.h"
#include "LogMessage.h"

class Base
{
  public:

	///////////////////////////////////////////////////////////
	// TYPE: Method 
	//  
	// METHOD NAME: Base
	//
	/// DESCRIPTION: Default constructor
	///////////////////////////////////////////////////////////
    Base();

	///////////////////////////////////////////////////////////
	// TYPE: Method
	//
	// METHOD NAME: ~Base
	//
	/// DESCRIPTION: Default destructor
	///////////////////////////////////////////////////////////
	~Base();

	///////////////////////////////////////////////////////////
	// TYPE: Method
	//
	// METHOD NAME: SendToLogger
	//
	/// DESCRIPTION: When the UDPSender is instantiated, it is
	/// given the port # and ip address for the system's 
	/// logger (this information is read-in from the 
	/// Config.rtsc file at runtime).
	///////////////////////////////////////////////////////////
    void SendToLogger();


  protected:

	///////////////////////////////////////////////////////////
	// TYPE: Protected Data Members
	//
	/// DESCRIPTION: Classes that inherit from this one will be
	/// provided with allocated space in memory for a class name 
	/// and log message, and an instantiated UDP-based log 
	/// sender.
	///////////////////////////////////////////////////////////
	char* myClassName;
    UDPSender* logSender;
    LogMsg* myLogMessage;
};

#endif

/*
Maximum Line Size
<=======================================================================>
*/