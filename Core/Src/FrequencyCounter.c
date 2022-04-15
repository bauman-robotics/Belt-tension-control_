#include "FrequencyCounter.h"
#include "main.h"
#include <stdio.h>

uint32_t tick_count;

void InitFrequencyCounter(Frequency_Counter* new_counter, TIM_HandleTypeDef* timer, uint32_t chanel,
  uint32_t base_frequency)
{
	new_counter->timer = timer;
	new_counter->chanel = chanel;
	new_counter->timer_frequency = base_frequency/(timer->Init.Prescaler+1);
}
 
void CountFrequency(Frequency_Counter* counter)
{
	tick_count = HAL_TIM_ReadCapturedValue(counter->timer, counter->chanel);
	counter->result_frequency = (10000000*counter->timer_frequency)/(tick_count+counter->full_periods*counter->timer->Init.Period);
	__HAL_TIM_SetCounter(counter->timer, 0);
	counter->full_periods = 0;
}