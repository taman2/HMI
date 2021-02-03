/*
 * LED.h
 *
 * Created: 7/3/2020 10:24:30 PM
 *  Author: HMI
 */ 


#ifndef LED_H_
#define LED_H_

#include "DIO.h"

/**Configuration for LEDs for user**/
#define LED_0     12
#define LED_1     13
#define LED_2     14
#define LED_3     15
/****Mutual between user and creater or author****/
#define LED_BY_DEFAULT_ON  0
#define LED_BY_DEFAULT_OFF 1
/***Functions Protoype***/
void LED_Init(uinteg8_t u8_Led_Pin);
void LED_ON(uinteg8_t u8_Led_Pin,uinteg8_t u8_default_Led_State);
void LED_OFF(uinteg8_t u8_Led_Pin,uinteg8_t u8_default_Led_State);
void LED_TOGGLE(uinteg8_t u8_Led_Pin,uinteg8_t u8_default_Led_State);

#endif /* LED_H_ */