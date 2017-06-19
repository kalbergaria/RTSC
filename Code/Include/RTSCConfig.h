#ifndef RTSC_CONFIG_H
#define RTSC_CONFIG_H

///////////////////////////////////////////////////////////
// Common
///////////////////////////////////////////////////////////
#define MAX_CLASSNAME_LENGTH 30
#define MAX_UDP_DATA_SIZE 1024

///////////////////////////////////////////////////////////
// Logger
///////////////////////////////////////////////////////////
#define LOGGER_IP "192.168.1.100"
#define LOGGER_PORT 10000
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