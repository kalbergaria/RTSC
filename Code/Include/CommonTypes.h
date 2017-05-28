#ifndef CMSN_TYPES_H
#define CMSN_TYPES_H

#include "UDPHeader.h"

// Common
#define MAX_CLASSNAME_LENGTH 30
enum deviceType
{
	MOTOR_UNIT,
	LIDAR_UNIT,
	DISPLAY_UNIT
};

// Logger
#define LOG_PATH_LENGTH 36
#define NUM_LOG_SEGMENTS 10
#define MAX_LOG_STRING_LENGTH 200
enum LogLevel
{
	CLASS_CREATION,
	INFO,
	WARNING,
	ERROR,
	FATAL
};

// LIDAR
#define NUM_SENSOR_ELEMENTS 16
#define NUM_SAMPLES_PER_ROTATION 48
#define IDEAL_NUM_SAMPLES 48
struct LDATA_UDP_MSG
{
	unsigned int rotCount;
	float ldet[16];
	UDPHeader UDP_MSGHeader;
};
// this typecast is here to avoid having to go 
// back and change data types in other locations
typedef LDATA_UDP_MSG LDATA;

// Networking
#define IPV4_ADDR_LENGTH 16
#define MAX_UDP_DATA_SIZE 1024
#define LIDAR_PI_IP20         "192.168.100.20"
#define LIDAR_PI_IP40         "192.168.100.40"
#define HAT_CONTROLLER_PI_IP  "192.168.100.30"
#define DISPLAY_AND_LOGGER_IP "192.168.100.50"
// Port Numbers for each MSG type
#define HAT_MSG_PORT 9000
#define HAT_RST_PORT 9005 // port to sync up the tachometer reading with all Pis
#define OBS_MSG_PORT 10000
#define LOG_MSG_PORT 11000
#define DNS_RCV_PORT 9000

// Merge And Collapse
#define NUM_ZONES 4
#define NO_ZONE 0
#define FRONT_ZONE 1
#define RIGHT_ZONE 2
#define REAR_ZONE 3
#define LEFT_ZONE 4

#define HIGH_VAL 9999

#define L20_LB_BOUND 6
#define L20_RB_BOUND 18
#define L20_RF_BOUND 30
#define L20_LF_BOUND 42

#define L40_RF_BOUND 6
#define L40_LF_BOUND 18
#define L40_LB_BOUND 30
#define L40_RB_BOUND 42

#endif