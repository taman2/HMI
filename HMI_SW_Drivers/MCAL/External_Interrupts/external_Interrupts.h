/*
 * external_Interrupts.h
 *
 * Created: 12/31/2020 4:35:07 PM
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

#ifndef EXTERNAL_INTERRUPTS_H_
#define EXTERNAL_INTERRUPTS_H_



#define FALLING_EDGE 1
#define RISING_EDGE  2
#define TOGGLE       3

void(*External_Int0_Fun)(void);/*POINTER TO FUCTION CARRY THE ADRESS OF INT0_FUCTION  */
void(*External_Int1_Fun)(void);/*POINTER TO FUCTION CARRY THE ADRESS OF INT1_FUCTION  */
void(*External_Int1_Fun)(void);/*POINTER TO FUCTION CARRY THE ADRESS OF INT2_FUCTION  */

void External_Interrupts_Init(uinteg8_t INT_Num,uinteg8_t Interrupt_triggering ,void(*External_Int_Fun_Address)(void));


#endif /* EXTERNAL_INTERRUPTS_H_ */