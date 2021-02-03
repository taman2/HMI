/*
 * Rotary_Encoder_CONFIG.h
 *
 * Created: 12/31/2020 4:19:01 PM
 *  Author: Mohamed
 */ 
#define  F_CPU 16000000UL
#include "Data_Types.h"
#include "BitManipulation.h"
#include "String_Manipulation.h"
#include "util/delay.h"
#include "avr/io.h"
#include "stdlib.h"
#include "UART_USER.h"
#include "BitManipulation.h"
#include "avr/interrupt.h"

#ifndef ROTARY_ENCODER_CONFIG_H_
#define ROTARY_ENCODER_CONFIG_H_

#define CLK_WISE   1
#define C_CLK_WISE 2
/*2 parameter that rotary encoder modifies them during its revolution  */
 volatile extern uinteg8_t U8_Rotary_Incoder_Direction;
 volatile extern uinteg8_t U8_Rotary_Incoder_OK_Button_Flag;
 volatile extern int U8_Rotary_Incoder_Counter;
 volatile extern uinteg8_t Rotary_flag;

enum Rotary_Encoder_Mode
{
	INTERRUP_MODE,
	POLLING_MODE
};
enum Rotary_Encoder_RESOLUTION
{
	FULL_RESOLUTION,
	HALF_RESOLUTION
};
	
struct ROTARY_Config{
	enum Rotary_Encoder_Mode           ROTARY_OPERATION_MODE;
	enum Rotary_Encoder_RESOLUTION     ROTARY_RESOLUTION;
	
};
extern struct ROTARY_Config ROTARY_ENCODER_PRE_CONFIGRATION;

/*main functions*/
void Rotary_Incoder_Init(struct ROTARY_Config CONFIG);
void Rotary_Incoder_DirectionINT0(void);
void Rotary_Incoder_DirectionINT1(void);
void Rotary_Encoder_Ok_IsPressed(void);







#endif /* ROTARY_ENCODER_CONFIG_H_ */