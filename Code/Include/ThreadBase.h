//TODO: Currently coded for Linux only!

#ifndef THREAD_BASE_H
#define THREAD_BASE_H

// External Files
#include <pthread.h>

// System Files
#include "Base.h"

class ThreadBase : public Base
{
	public:
		ThreadBase();
		bool StartThread();
        virtual void ThreadMethod() = 0;

	protected:
		pthread_t threadHandle;
};

#endif