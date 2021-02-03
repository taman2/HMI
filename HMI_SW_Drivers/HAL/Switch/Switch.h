/*
 * Switch.h
 *
 * Created: 7/2/2020 1:15:39 PM
 *  Author: HMI
 */ 

#include "DIO.h"
#define SWICTH_PULL_UP					  1
#define SWICTH_LEFT_FLOAT				  0
#define SWITCH_0					      0
#define SWITCH_1                          1
#define SWITCH_2                          2
#define SWITCH_3                          3
#define SWITCH_4                          4
#define SWITCH_5                          5
#define SWITCH_IS_CLOSED                  LOW
#define SWITCH_IS_OPENED                  HIGH
#define SWITCH_STATE_SINGLE_PUSH          13
#define SWITCH_STATE_HOLD                 14  
#define SWITCH_STATE_NOT_CLICKED          15
void Switch_Init(uinteg8_t u8_Pulled_Up);
void Switch_Read_Single_Sample(uinteg8_t u8_Switch_Pin,uinteg8_t* copy_of_address_of_Switch_State_Buffer);
void Switch_Read(uinteg8_t u8_Copy_Switch_Pin,uinteg8_t* copy_of_address_of_Switch_State_Buffer);