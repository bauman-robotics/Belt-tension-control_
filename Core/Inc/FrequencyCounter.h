#ifndef _FREQUENCY_COUNTER
#define _FREQUENCY_COUNTER

#include "main.h"

typedef struct
{
	TIM_HandleTypeDef* timer;
	uint32_t timer_frequency;
	uint32_t chanel;
	
	uint32_t result_frequency;
} Frequency_Counter;

void InitFrequencyCounter(Frequency_Counter* new_counter, TIM_HandleTypeDef* timer, uint32_t chanel,
  uint32_t timer_frequency, uint16_t base_prescaler);
void CountFrequency(Frequency_Counter* counter);
void IncreaseMeasuringLimit(Frequency_Counter* counter);

#endif