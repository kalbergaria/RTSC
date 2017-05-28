#ifndef UDP_HEADER_H
#define UDP_HEADER_H

#define MAX_MSG_TYPE_SIZE 20
#define MAX_ADDR_SIZE 16

//TODO: Ensure that the message headers are being populated
//maybe this shoudl be done in the UDPSender?
struct UDPHeader
{
	char source[MAX_ADDR_SIZE];
	char destination[MAX_ADDR_SIZE];
};

#endif
