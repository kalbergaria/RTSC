#ifndef CMSN_TIME_H
#define CMSN_TIME_H

#include "Global.h"

void SleepRemainingIterationDuration(timespec* iterationStart, int usecIterationDuration, int usecSleepIntervals);

long long TimespecConcatTimeConvert2us(timespec* timeStruct);

long long TimevalConcatTimeConvert2us(timeval* timeStruct);

#endif
