//TODO: Currently coded for Linux only!

#ifndef CHAR_PTR_QUEUE_H
#define CHAR_PTR_QUEUE_H

// includes
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>

using namespace std;

#define MAX_Q_NAME 30

class CharPtrQueue
{

	public:
		CharPtrQueue(int size, char* name);
		~CharPtrQueue(void);

		// methods
		bool IsFull(void);
		bool GetOccupancy(int* occupancy);
		bool IsEmpty(void);
		bool EmptyQueue(void);
		bool Dequeue(char** data);
		bool Enqueue(char* data);

		// data
		char* qName;
		int qSize;

	private: 
		// methods
		int NextIndex(int currentIndex);

		// data
		int numQueuedElements;
		int dequeueIndex; //read
		int enqueueIndex; //write
		char** Q;
};


#endif