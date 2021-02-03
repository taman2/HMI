/*
 * Math.c
 *
 * Created: 9/3/2020 1:18:25 PM
 *  Author: HMI
 */

#include "Data_Types.h"

void Power_For_Two(uinteg64_t* pu64_The_Result,uinteg64_t u64_Number_That_Need_To_Powered )
{
	uinteg64_t u64_Result_Buffer=1;

	for(uinteg64_t u64_index=0;u64_index<u64_Number_That_Need_To_Powered;u64_index++)
	{
		u64_Result_Buffer=u64_Result_Buffer*2uL;
	}

	*pu64_The_Result=u64_Result_Buffer;
}
