/*
 * ICU.h
 *
 * Created: 2/3/2021 2:13:52 PM
 *  Author: Mohamed
 */ 


#ifndef ICU_H_
#define ICU_H_


#define  F_CPU 16000000UL
#include "Data_Types.h"
#include "Timer.h"
#include "BitManipulation.h"
#include "util/delay.h"
#include "avr/io.h"
#include "stdlib.h"

 static uinteg64_t a,b,c,high,period;

/*********************main Functions*****************************************/
void Icu_Init(void);
void Icu_Capture_Signal(void);
uinteg64_t Icu_Signal_Period(void);
uinteg64_t Icu_Signal_Frequ(void);


#endif /* ICU_H_ */