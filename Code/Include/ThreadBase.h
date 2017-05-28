#ifndef THREAD_BASE_H
#define THREAD_BASE_H

// External Files
#include <pthread.h>

// System Files
#include "CMSNBase.h"

class ThreadBase : public CMSNBase
{
	public:
		ThreadBase();
		bool StartThread();
        virtual void ThreadMethod() = 0;

	protected:
		pthread_t threadHandle;
};

#endif