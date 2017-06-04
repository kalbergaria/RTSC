#ifndef _PLATFORM_H
#define _PLAYFORM_H

///////////////////////////////////////////////////////////
// Determining Operating System
//
/// => __unix__ is typically defined by compilers 
///	   targeting Unix sytems
///
/// => _WIN32 or WIN32 are typically defined by
///	   compilers targeting 32 or 64 bit
///    Windows systems
///////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(WIN32)

	#define RTSC_WIN

#elif defined(__unix__)

	#define RTSC_LINUX

#endif

///////////////////////////////////////////////////////////
// Determining System Architecture
//
/// => Information for this was obtained from the
///    following link: 
///    https://sourceforge.net/p/predef/wiki/Architectures/
///
/// => __amd64, __amd64__, or _M_AMD64 will likely be
///    defined if the system has a 64-bit AMD processor
///
/// => __x86_64, __x86_64__, _M_X64, i386, __i386, 
///    __i386__, __i486__, __i586__, __i686__, _M_I86, or 
///    _M_IX86 will likely be defined if the system has 
///	   an Intel processor
///
/// => __arm__, __aarch64__, _M_ARM will likely be defined 
///    if the system has an ARM processor
///////////////////////////////////////////////////////////
#if defined(__x86_64) || defined(__x86_64__) || defined(_M_X64)
	|| defined(i386) || defined(__i386) || defined(__i386__) 
	|| defined(__i486__) || defined(__i586__) || defined(__i686__)
	|| defined(_M_I86) || defined(_M_IX86)

	#define RTSC_INTEL

#elif defined(__amd64) || defined(__amd64__) || defined(_M_AMD64)

	#define RTSCA_AMD

#elif defined(__arm__) || defined(__aarch64__) || defined(_M_ARM)

	#define RTSC_ARM

#endif

#endif //end of Patform.h

/*
Maximum Line Size
<=======================================================================>
*/