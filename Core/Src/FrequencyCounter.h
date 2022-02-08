#include "main.h"
#ifndef _FREQUENCY_COUNTER
	#define _FREQUENCY_COUNTER

typedef struct
{
	TIM_HandleTypeDef* timer;
	int count;
} FrequencyCounter;

void InitFrequencyCounter(FrequencyCounter* new_counter, TIM_HandleTypeDef* timer);
int CountFrequency(FrequencyCounter* counter);

#endif