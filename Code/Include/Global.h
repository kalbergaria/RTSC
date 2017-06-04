#ifndef _GLOBAL_HEADER_
#define _GLOBAL_HEADER_

///////////////////////////////////////////////////////////
// Common System Files
///////////////////////////////////////////////////////////
#include "Platform.h"
#include "DebugState.h"
#include "Debug.h"

///////////////////////////////////////////////////////////
// Platform Independent External Libraries & Namespaces
///////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <sys/types.h>

using namespace std;

///////////////////////////////////////////////////////////
// Linux Platform Libraries & Namespaces
///////////////////////////////////////////////////////////
#ifdef RTSC_LINUX
	#include <sys/time.h>
	#include <pthread.h>
	#include <unistd.h>
	#include <sys/wait.h>
#endif

///////////////////////////////////////////////////////////
// Windows Platform Libraries & Namespaces
///////////////////////////////////////////////////////////
#ifdef RTSC_WIN
	#include <Windows.h>
#endif

#define MAX_PATH_LENGTH 256

#endif

/*
Maximum Line Size
<=======================================================================>
*/