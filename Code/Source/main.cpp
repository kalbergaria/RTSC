// System Files
#include "Global.h"
#include "ThreadManager.h"

///////////////////////////////////////////////////////////
// METHOD NAME: Main
//
/// DESCRIPTION: The main loop for the RTSC application,
/// it starts the Thread Manager then 
///////////////////////////////////////////////////////////
int main(void)
{	
	cout << "<== Real Time System Core Starting ==>" << endl;

	// TODO: Config.rtsc read-in

	// Instantiate the ThreadManager class and start all threads
	cout << "RTSC Thread Manager started..." << endl;
	ThreadManager* myThreadManager = ThreadManager::getInstance();
	myThreadManager->StartAllThreads();

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
