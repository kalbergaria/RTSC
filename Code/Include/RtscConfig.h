#ifndef RTSC_CONFIG_H
#define RTSC_CONFIG_H

///////////////////////////////////////////////////////////
// Common
///////////////////////////////////////////////////////////
#define MAX_CLASSNAME_LENGTH 30
#define MAX_UDP_DATA_SIZE 1024
#define IPV4_ADDR_LENGTH 16

///////////////////////////////////////////////////////////
// Logger
///////////////////////////////////////////////////////////
#define DISPLAY_AND_LOGGER_IP "127.0.0.1"
#define DISPLAY_AND_LOGGER_PORT 10000
#define TEST_IP "127.0.0.1"
#define TEST_PORT 5000
#define LOG_PATH_LENGTH 36
#define MAX_LOG_STRING_LENGTH 200
enum LogLevel
{
	CLASS_CREATION,
	INFO,
	WARNING,
	ERROR,
	FATAL
};

#endif

/*
Maximum Line Size
<=======================================================================>
*/