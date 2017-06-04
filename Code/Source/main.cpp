// System Files
#include "Global.h"
//#include "ThreadManager.h"

///////////////////////////////////////////////////////////
// RTSC Main
//
/// Description: The main loop for the RTSC application,
/// it starts the Thread Manager then 
///////////////////////////////////////////////////////////
int main(void)
{	
	cout << "<== Real Time System Core Starting ==>" << endl;

	/*// Instantiate the ThreadManager class
	cout << "RTSC Thread Manager started..." << endl;
	ThreadManager* myThreadManager = ThreadManager::getInstance();*/	

	// Loop indefinitely
	while (true)
	{
		// Sleep for 10 seconds
		#ifdef RTSC_LINUX
			usleep(60000000); // 60 seconds
		#endif

		#ifdef RTSC_WIN
			Sleep(6000); // 60 seconds
		#endif
	}
}

/*
Maximum Line Size
<=======================================================================>
*/
