#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include "Global.h"
#include "CMSNBase.h"

#define NUM_THREADS 1

class ThreadManager : public CMSNBase
{
	public:
		// -----Singleton Code-----
		static ThreadManager* getInstance();
		~ThreadManager();
		// ------------------------

		void StartAllThreads_LIDAR_Pi(char* myIP);
		void StartAllThreads_Display_Pi();
		void StartAllThreads_Debug();

	private:
		// -----Singleton Code-----
		ThreadManager();
		static ThreadManager* threadManagerInstance;
		// ------------------------
		char* tachReceiver;
		char* loggingReceiver;
		char* dispObsProcReceiver;
};

#endif