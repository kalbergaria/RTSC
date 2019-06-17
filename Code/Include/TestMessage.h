#ifndef TEST_MSG_H
#define TEST_MSG_H

// System Files
#include "Global.h"
#include "UDPHeader.h"

///////////////////////////////////////////////////////////
// Log Message Contents
///////////////////////////////////////////////////////////
struct TestMSG
{
	UDPHeader UDP_MSGHeader;
    char message[100];
};

#endif

/*
Maximum Line Size
<=======================================================================>
*/