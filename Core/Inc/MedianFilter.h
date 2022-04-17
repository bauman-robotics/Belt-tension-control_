#ifndef _MEDIAN_FILTER
#define _MEDIAN_FILTER

#include "main.h"

typedef struct
{
	int32_t* data;
	uint8_t sample_size;
	uint8_t cleared;
	uint8_t index_of_last;
} Median_Filter;

void InitFilter(Median_Filter* new_filter, uint8_t sample_size);
int32_t ReturnMedian(Median_Filter* filter);
void AddValue(Median_Filter* filter, int32_t value);
void ClearValues(Median_Filter* filter);
#endif