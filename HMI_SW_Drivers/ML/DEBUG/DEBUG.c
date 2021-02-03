/*
 * Debug.c
 *
 * Created: 25/01/2020 02:36:24
 *  Author: Native_programmer
 */ 

#include "DEBUG.h"

#define Debug_By_Toggle_State_1st_time    0
#define Debug_By_Toggle_State_Other_times 1
#define Debug_By_Toggle_State_Nothing     2


void Debug_By_Toggle(uinteg8_t u8_Pin)
{
	DIO_Init_Pin(u8_Pin,1,DIO_PIN_OUTPUT);
	DIO_toggle_Pin(u8_Pin);
}