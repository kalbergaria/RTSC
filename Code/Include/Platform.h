#ifndef _PLATFORM_H
#define _PLAYFORM_H

// System Files
#include<stdint.h>

///////////////////////////////////////////////////////////
// Determine the OS
//
/// => __unix__ is typically defined by compilers 
///	   targeting Unix sytems
///
/// => _WIN32 is typically defined by compilers targeting
///	   32 or 64 bit Windows systems
///////////////////////////////////////////////////////////
#if defined(_WIN32)
	#define RTSC_WIN
#elif defined(__unix__)
	#define RTSC_LINUX
#else
	#define RTSC_UNKNOWN_OS
#endif

///////////////////////////////////////////////////////////
// Determine the OS Word Size
///
/// => This method is highly portable
///////////////////////////////////////////////////////////
#if UINTPTR_MAX == 0xffffffff
	#define RTSC_32
#elif UINTPTR_MAX == 0xffffffffffffffff
	#define RTSC_64
#else
	#define RTSC_UNKNOWN_WORD_SIZE
#endif

///////////////////////////////////////////////////////////
// Detect ARM Processor Architecture
///
/// => The following pre-defined compiler macros for
///    identifying a CPU with an ARM architecture are from
///    the following site:
///    https://sourceforge.net/p/predef/wiki/Architectures/
///////////////////////////////////////////////////////////
#if defined(__arm__) || defined(__aarch64__) || defined(_M_ARM)
	#define RTSC_ARM
#endif

#endif //end of Platform.h

/*
Maximum Line Size
<=======================================================================>
*/