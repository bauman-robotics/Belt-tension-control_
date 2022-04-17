#include "main.h"
#include "MedianFilter.h"
#include <stdlib.h>

#define DATA (filter->data)
#define SIZE (filter->sample_size)
#define LAST (filter->index_of_last)
#define CLEARED (filter->cleared==1)
#define SET_NOT_CLEARED (filter->cleared = 0)
#define SET_CLEARED (filter->cleared = 0)

void InitFilter(Median_Filter* new_filter, uint8_t sample_size)
{
	new_filter->sample_size = 3;
//	new_filter->sample_size = sample_size;
	new_filter->data = calloc(sample_size, sizeof(int32_t));
	new_filter->cleared = 1;
}
int32_t ReturnMedian(Median_Filter* filter)
{
	if(DATA[0]<DATA[1])
	{
		if(DATA[1]<DATA[2])
		{
			return DATA[1];
		}
		else
		{
			if(DATA[0]<DATA[2])
			{
				return DATA[2];
			}
			else
			{
				return DATA[0];
			}
		}
	}
	else
	{
		if(DATA[0]<DATA[2])
		{
			return DATA[0];
		}
		else
		{
			if(DATA[1]<DATA[2])
			{
				return DATA[2];
			}
			else
			{
				return DATA[1];
			}
		}
	}
//	if(CLEARED)
//	{
//		return 0;
//	}
//	else
//	{
//		return DATA[SIZE/2];
//	}
}
void AddValue(Median_Filter* filter, int32_t value)
{
	if(CLEARED)
	{
		for(int i=0; i<SIZE; i++)
		{
			DATA[i] = value;
		}
		SET_NOT_CLEARED;
		LAST=0;
	}
//	else
//	{
//		uint8_t length = SIZE;
//		uint8_t start_index = 0;
//		while(length>1)
//		{
//			length/=2;
//			if(DATA[start_index+length]<value)
//			{
//				start_index+=length+1;
//				if(start_index>=SIZE)
//				{
//					start_index=SIZE-1;
//					length=1;
//					break;
//				}
//			}
//			else if(DATA[start_index+length]==value)
//			{
//				start_index+=length;
//				length=1;
//				break;
//			}
//		}
//		for(int i=LAST+((start_index>LAST)?1:-1); i!=start_index; i+=(start_index>LAST)?1:-1)
//		{
//			DATA[i-((start_index>LAST)?1:-1)]=DATA[i];
//		}
//		DATA[start_index]=value;
//	}
	else
	{
		for(int i=1; i<3; i++)
		{
			DATA[i-1]=DATA[i];
		}
		DATA[2]=value;
	}
}
void ClearValues(Median_Filter* filter)
{
	SET_CLEARED;
}