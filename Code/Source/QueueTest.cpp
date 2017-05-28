#include <stdio.h>
#include <string.h>
#include "../include/CharPtrQueue.h"

int main(void)
{
	char a = 'a';
	char b = 'b';
	char c = 'c';

	char* aPTR = &a;
	char* bPTR = &b;
	char* cPTR = &c;

	CharPtrQueue* myQ = new CharPtrQueue(3);

	printf("Checking if queue is empty before adding anything to it:\n");
	if(myQ->IsEmpty())
	{
		printf("Queue is empty!\n");
	}

	printf("Adding 3 things to the queue and checking if queue is full:\n");
	myQ->Enqueue(aPTR);
	myQ->Enqueue(bPTR);
	myQ->Enqueue(cPTR);

	if(myQ->IsFull())
	{
		printf("Queue is full!\n");
	}

	printf("Emptying queue and checking if queue is empy after calling the EmptyQueue function:\n");
	myQ->EmptyQueue();
	if(myQ->IsEmpty())
	{
		printf("Queue is empty!\n");
	}

	printf("Refilling queue with the 3 things and checking if refilled queue is full:\n");
	myQ->Enqueue(aPTR);
	myQ->Enqueue(bPTR);
	myQ->Enqueue(cPTR);

	if(myQ->IsFull())
	{
		printf("Queue is full!\n");
	}

	printf("Dequeueing and printing elements:\n");
	char* temp;
	for(int i = 0; i < 3; i++)
	{
		myQ->Dequeue(&temp);
		printf("Dequeued value: %c\n", (char)temp[0]);
	}

	return 0;
}
