//TODO: Currently coded for Linux only!

#ifndef UDP_SENDER_H
#define UDP_SENDER_H

// System Files
#include "Global.h"

// External Files
#ifdef RTSC_LINUX
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

class UdpSender
{
	public:
		///////////////////////////////////////////////////////////
		// TYPE: Method 
		//  
		// METHOD NAME: UdpSender
		//
		/// DESCRIPTION: Only means of instantiating the class, 
		/// forcing a user to specify an ip and port number to
		/// whom this sender will send messages to.
		///////////////////////////////////////////////////////////
		UdpSender(char* ipAddress, int portNumber);

		///////////////////////////////////////////////////////////
		// TYPE: Method 
		//  
		// METHOD NAME: SendMSG
		//
		/// DESCRIPTION: Send the specified message to the ip and
		/// port number originally specified when the class was
		/// instantiated.
		///////////////////////////////////////////////////////////
		void SendMSG(char* msg, int msgSize);

	private:
		///////////////////////////////////////////////////////////
		// TYPE: Method 
		//  
		// METHOD NAME: UdpSender
		//
		/// DESCRIPTION: Default constructor
		///////////////////////////////////////////////////////////
		UdpSender();

		///////////////////////////////////////////////////////////
		// TYPE: Private Data Members
		///////////////////////////////////////////////////////////
		#ifdef RTSC_LINUX
			int mySocket;
			char* destIPAddress;
			unsigned int sockaddrSize;
			struct sockaddr_in destinationAddr;
		#endif	
};

#endif

/*
Maximum Line Size
<=======================================================================>
*/
