/*
 * Stepper.h
 *
 * Created: 12/15/2020 6:24:06 PM
 *  Author: Mohamed
 */ 

#include "Data_Types.h"
#include "BitManipulation.h"
#include "String_Manipulation.h"
#include "util/delay.h"
#include "avr/io.h"
#include "stdlib.h"
#include "UART_USER.h"
#include "BitManipulation.h"
#include "avr/interrupt.h"
#include "Stepper_User.h"

#ifndef STEPPER_H_
#define STEPPER_H_


#define LOW_NIBBLE   1
#define HIGH_NIBBLE  2

 void stepper_dir(uint8_t dir);
 void stepper_init(uint8_t _Nibble_Postion);
 void stepper_move(void);/*move one step*/
 /*call this function in case stepper motor finish all number of steps to back to its last position */
void Stepper_Intial_Position(void);
 






#endif /* STEPPER_H_ */