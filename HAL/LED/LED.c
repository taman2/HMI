/*
 * LED.c
 *
 * Created: 7/3/2020 10:24:18 PM
 *  Author:HMI
 */
#include "LED.h"

void LED_Init(uinteg8_t u8_Led_Pin)
{
	DIO_Init_Pin(u8_Led_Pin,OUTPUT,DIO_PIN_OUTPUT);
}

void LED_ON(uinteg8_t u8_Led_Pin,uinteg8_t u8_default_Led_State)
{
	if(u8_default_Led_State==LED_BY_DEFAULT_ON)
	{
		DIO_Write_Pin(u8_Led_Pin,LOW);
	}
	else if(u8_default_Led_State==LED_BY_DEFAULT_OFF)
	{
		DIO_Write_Pin(u8_Led_Pin,HIGH);
	}
}
void LED_OFF(uinteg8_t u8_Led_Pin,uinteg8_t u8_default_Led_State)
{
	if(u8_default_Led_State==LED_BY_DEFAULT_ON)
	{
		DIO_Write_Pin(u8_Led_Pin,HIGH);
	}
	else if(u8_default_Led_State==LED_BY_DEFAULT_OFF)
	{
		DIO_Write_Pin(u8_Led_Pin,LOW);
	}
}
void LED_TOGGLE(uinteg8_t u8_Led_Pin,uinteg8_t u8_default_Led_State)
{
	DIO_toggle_Pin(u8_Led_Pin);
}
