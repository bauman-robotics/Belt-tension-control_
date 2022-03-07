#include "FrequencyCounter.h"
#include "main.h"
#include <stdio.h>

uint32_t tick_count;
uint32_t self_frequency;

void InitFrequencyCounter(Frequency_Counter* new_counter, TIM_HandleTypeDef* timer, uint32_t chanel,
  uint32_t timer_frequency, uint16_t base_prescaler)
{
	timer->Init.Prescaler = (base_prescaler>17)?base_prescaler:17;
	new_counter->timer = timer;
	new_counter->chanel = chanel;
	new_counter->timer_frequency = timer_frequency;
}
 
void CountFrequency(Frequency_Counter* counter)
{
	self_frequency = (1000000*counter->timer_frequency/(counter->timer->Init.Prescaler+1));
	tick_count = HAL_TIM_ReadCapturedValue(counter->timer, counter->chanel);
	counter->result_frequency = self_frequency/tick_count;
	if(tick_count < counter->timer->Init.Period/2)
	{
		if(counter->timer->Init.Prescaler/2 < 17)
		{
			counter->timer->Init.Prescaler = 17;
		}
		else
		{
			counter->timer->Init.Prescaler /= 2;
		}
	}
	__HAL_TIM_SetCounter(counter->timer, 0);
}

void IncreaseMeasuringLimit(Frequency_Counter* counter)
{
	if(counter->timer->Init.Prescaler <= 1024)
	{
		counter->timer->Init.Prescaler *= 2;
	}
}