#ifndef _GLOBAL_HEADER_
#define _GLOBAL_HEADER_

// Common External Libraries
#include <stdio.h>
#include <stddef.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

// Common System files
#include "DebugState.h"
#include "Debug.h"
#include "CMSNTypes.h"

// Dependent Compilation Libraries
#if RUNNING_ON_PI == true
	#include <wiringPi.h>
#endif

using namespace std;

#define MAX_PATH_LENGTH 256
#define MAX_SENSOR_VALUE 100

#define NUM_SENSOR_ELEMENTS 16

// GPIO Pins used
#define TACH 1

#endif
