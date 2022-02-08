#include "FrequencyCounter.h"
const int system_frequency = 72;

void InitFrequencyCounter(FrequencyCounter* new_counter, TIM_HandleTypeDef* timer)
{
	new_counter->timer = timer;
	new_counter->count = 0;
}

int CountFrequency(FrequencyCounter* counter)
{
	int period = counter->timer->Init.Period/(system_frequency);
	int result = counter->count*1000/period;
	counter->count = 0;
	return result;
}