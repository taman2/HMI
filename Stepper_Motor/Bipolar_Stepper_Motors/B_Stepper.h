/*
 * Stepper.h
 *
 * Created: 12/15/2020 6:24:06 PM
 *  Author: Mohamed
 */ 

#include "Data_Types.h"
#include "BitManipulation.h"
#include "util/delay.h"
#include "avr/io.h"
#include "stdlib.h"
#include "BitManipulation.h"
#include "avr/interrupt.h"
#include "B_Stepper_User.h"

#ifndef STEPPER_H_
#define STEPPER_H_


#define LOW_NIBBLE   1
#define HIGH_NIBBLE  2

 static void B_Stepper_Dir(uint8_t dir);
 void B_Stepper_Init(void);
 void B_Stepper_move(float32_t Angel); 
 /*call this function in case stepper motor finish all number of steps to back to its last position */
 






#endif /* STEPPER_H_ */