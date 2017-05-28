// External Libraries
#include <stdio.h>
#include <iostream>

// System Files
#include "../include/Debug.h"

void DB1(string data)
{
	// get current time in unix format
	time_t ltime;
    time(&ltime);
	
	// print to console only if debug is enabled
	#if debug1 == true
		cout << "[" << ltime << "]: " << data << endl;
	#endif
	
	// print to log file
		
}

void DB2(string data)
{
	// get current time in unix format
	time_t ltime;
    time(&ltime);
	
	// print to console only if debug is enabled
	#if debug2 == true
		cout << "[" << ltime << "]: " << data << endl;
	#endif
	
	// print to log file
		
}

void DB3(string data)
{
	// get current time in unix format
	time_t ltime;
    time(&ltime);
	
	// print to console only if debug is enabled
	#if debug3 == true
		cout << "[" << ltime << "]: " << data << endl;
	#endif
	
	// print to log file
		
}

void DB1_2strings(string data, string data2)
{
	// get current time in unix format
	time_t ltime;
    time(&ltime);
	
	// print to console only if debug is enabled
	#if debug1 == true
		cout << "[" << ltime << "]: " << data << data2 << endl;
	#endif
	
	// print to log file
		
}

void DB2_2strings(string data, string data2)
{
	// get current time in unix format
	time_t ltime;
    time(&ltime);
	
	// print to console only if debug is enabled
	#if debug2 == true
		cout << "[" << ltime << "]: " << data << data2 << endl;
	#endif
	
	// print to log file
		
}

void DB3_2strings(string data, string data2)
{
	// get current time in unix format
	time_t ltime;
    time(&ltime);
	
	// print to console only if debug is enabled
	#if debug3 == true
		cout << "[" << ltime << "]: " << data << data2 << endl;
	#endif
	
	// print to log file
		
}