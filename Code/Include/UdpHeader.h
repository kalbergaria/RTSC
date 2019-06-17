#ifndef UDP_HEADER_H
#define UDP_HEADER_H

#define MAX_MSG_TYPE_SIZE 20
#define MAX_ADDR_SIZE 16

struct UDPHeader
{
	char source[MAX_ADDR_SIZE];
	char destination[MAX_ADDR_SIZE];
};

#endif
