/*
 * LCD_cfg.h
 *
 *  Created on: Jan 3, 2020
 *      Author: HMI
 */

#ifndef MCAL_LCD_LCD_H_
#define MCAL_LCD_LCD_H_


#include "Data_Types.h"
#include "AtmegaPort.h"
#include "BitManipulation.h"
#include "String_Manipulation.h"
#include "DIO.h"
#include"lcd_ret_val.h"

/***********************INCLUDES***************************************/
typedef uinteg8_t ERROR_TYPE_t; 
#define NULL ((uinteg8_t*)(0))
/****************************TYPE_DEF*****************************************/

//typedef uinteg8_t ERROR_TYPE_t;

/*********************************Config_MACROS************************************/
/* LCD HW Pins */
#define RS 4
#define RW 5
#define EN  6
#define LCD_CTRL_PORT     PORTD
#define LCD_CTRL_PORT_DIR DDRD
#define LCD_DATA_PORT     PORTB
#define LCD_DATA_PORT_DIR DDRB
/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 4

/* Use higher 4 bits in the data port */
#define UPPER_PORT_PINS

#define LCD_SIZE_20_MULTIPLY_4 1
/***************************FUNCTION_PROTOTYPES*****************************/
ERROR_TYPE_t LCD_init(void);
ERROR_TYPE_t LCD_sendCommand(uinteg8_t u8_command);
ERROR_TYPE_t LCD_displayCharacter(uinteg8_t u8_data);
ERROR_TYPE_t LCD_displayString(const uinteg8_t * ptr_String);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uinteg8_t row,uinteg8_t col,const uinteg8_t *Str);
void LCD_goToRowColumn(uinteg8_t row, uinteg8_t col);
void LCD_FloatToString(float64_t f_Number,uinteg8_t u8_How_Many_Number_Before_Point,uinteg8_t u8_How_Many_Number_After_Point,uinteg8_t row,uinteg8_t col);
void LCD_integerToString(integ16_t s64_value,uinteg8_t row,uinteg8_t col,uinteg8_t u8_Number_Of_Digits);

#endif /* MCAL_LCD_LCD_H_ */
