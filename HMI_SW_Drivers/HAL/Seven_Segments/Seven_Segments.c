/*
 * Seven_Segments.c
 *
 * Created: 6/30/2020 12:34:43 PM
 *  Author: HMI
 */
#include "Seven_Segments.h"

uinteg8_t Seven_Segments_Common_Anode_Array_code[]={ 0xc0,0xf9,0xa4,     // 0, 1, 2,
											   		 0xb0,0x99,0x92,     // 3, 4, 5,
													 0x82,0xf8,0x80,     // 6, 7, 8,
													 0x90             }; // 9

void Seven_Segments_Init()
{

  DIO_Init_PORT(Seven_Segments_Comman_Pin_Channel,OUTPUT);
  DIO_Init_PORT(Seven_Segments_Draw_Channel,OUTPUT);
}
/*

void Seven_Segments_Write_Integer_Number(uinteg8_t u8_Copy_Seven_Segment_of_Comman_Pin_Channel,uinteg32_t u32_Copy_of_Number,uinteg8_t u8_Units_Or_Tens)
{


    DIO_Write_Port(Seven_Segments_Comman_Pin_Channel,u8_Copy_Seven_Segment_of_Comman_Pin_Channel);

	if(u8_Units_Or_Tens==UNITS)
	{
	    DIO_Write_Port(Seven_Segments_Draw_Channel,Seven_Segments_Common_Anode_Array_code[u32_Copy_of_Number%10]);

	}
	else if(u8_Units_Or_Tens==TENS)
	{
		DIO_Write_Port(Seven_Segments_Draw_Channel,Seven_Segments_Common_Anode_Array_code[(u32_Copy_of_Number/10)%10]);
	}
	else if(u8_Units_Or_Tens==HUNDRADS)
	{
		DIO_Write_Port(Seven_Segments_Draw_Channel,Seven_Segments_Common_Anode_Array_code[(u32_Copy_of_Number/100)%10]);
	}
	else if(u8_Units_Or_Tens==THOUSANDS)
	{
		DIO_Write_Port(Seven_Segments_Draw_Channel,Seven_Segments_Common_Anode_Array_code[(u32_Copy_of_Number/1000)%10]);
	}
	else if(u8_Units_Or_Tens==TENS_THOUSANDS)
	{
		DIO_Write_Port(Seven_Segments_Draw_Channel,Seven_Segments_Common_Anode_Array_code[(u32_Copy_of_Number/10000)%10]);
	}
	//Debug_By_Toggle(11);
}
*/


void Seven_Segments_Turn_off()
{
	DIO_Write_Port(Seven_Segments_Draw_Channel,0);

}

void Seven_Segments_Write_Integer_Number(uinteg8_t u8_Copy_Seven_Segment_of_Comman_Pin_Channel,uinteg8_t u8_Copy_of_Number,uinteg8_t u8_Write_Point)
{

	DIO_Write_Port(Seven_Segments_Comman_Pin_Channel,u8_Copy_Seven_Segment_of_Comman_Pin_Channel);

	if(u8_Write_Point)
	{
		 DIO_Write_Port(Seven_Segments_Draw_Channel,Seven_Segments_Common_Anode_Array_code[u8_Copy_of_Number]&0x7F);
	}
	else
	{
		DIO_Write_Port(Seven_Segments_Draw_Channel,Seven_Segments_Common_Anode_Array_code[u8_Copy_of_Number]     );
	}
}

void Seven_Segments_Write_Something(uinteg8_t u8_Copy_Seven_Segment_of_Comman_Pin_Channel,uinteg8_t u8_Copy_of_Thing_Representation,uinteg8_t u8_Write_Point)
{

	DIO_Write_Port(Seven_Segments_Comman_Pin_Channel,u8_Copy_Seven_Segment_of_Comman_Pin_Channel);

	if(u8_Write_Point) DIO_Write_Port(Seven_Segments_Draw_Channel,u8_Copy_of_Thing_Representation&0x7F);
	else               DIO_Write_Port(Seven_Segments_Draw_Channel,u8_Copy_of_Thing_Representation     );
}
