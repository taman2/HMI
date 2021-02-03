/*
 * lcd.c
 *
 *  Created on: Apr 29, 2019
 *      Author: HMI
 */


#include "lcd.h"
#include "avr/delay.h"
#include "String_Manipulation.h"
#define INIT_CASE_0 0u
#define INIT_CASE_1 1u
#define INIT_CASE_2 2u
#define INIT_CASE_3 3u

#define COMMAND_CASE_0 0u
#define COMMAND_CASE_1 1u
#define COMMAND_CASE_2 2u
#define COMMAND_CASE_3 3u
#define COMMAND_CASE_4 4u
#define COMMAND_CASE_5 5u
#define COMMAND_CASE_6 6u
#define COMMAND_CASE_7 7u


#define DISPLAY_CHAR_CASE_0 0u
#define DISPLAY_CHAR_CASE_1 1u
#define DISPLAY_CHAR_CASE_2 2u
#define DISPLAY_CHAR_CASE_3 3u
#define DISPLAY_CHAR_CASE_4 4u
#define DISPLAY_CHAR_CASE_5 5u
#define DISPLAY_CHAR_CASE_6 6u
#define DISPLAY_CHAR_CASE_7 7u

/***********************************Global_Variable*****************************************/


ERROR_TYPE_t LCD_init(void)
{
	/*uinteg8_t au8_error=8;*/

		LCD_CTRL_PORT_DIR |= (1<<EN) | (1<<RS) | (1<<RW);
/*		LCD_CTRL_PORT^= (1<<EN) | (1<<RS) | (1<<RW);*/
#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS
		LCD_DATA_PORT_DIR |= 0xF0; /* Configure the highest 4 bits of the data port as output pins */
		LCD_sendCommand(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */

#else
		LCD_DATA_PORT_DIR |= 0x0F; /* Configure the lowest 4 bits of the data port*/
		LCD_sendCommand(FOUR_BITS_DATA_MODE);
#endif
#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT_DIR = 0xFF; /* Configure the data port as output port */
		LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
#endif

		LCD_sendCommand(0x28); /* cursor off */

		LCD_sendCommand(CURSOR_OFF);
		LCD_sendCommand(0x01);



}

ERROR_TYPE_t LCD_sendCommand(uinteg8_t u8_command)
{
	/*uinteg8_t au8_error;*/

		CLR_BIT(LCD_CTRL_PORT,RS); /* Instruction Mode RS=0 */
		CLR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
/*		Debug_By_Toggle(22);	*/
		SET_BIT(LCD_CTRL_PORT,EN); /* Enable LCD E=1 */
        _delay_ms(2);
/*		Debug_By_Toggle(22);*/
#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (u8_command & 0xF0);
#else
		LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((u8_command & 0xF0) >> 4);
#endif
#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT = u8_command; /* out the required command to the data bus D0 --> D7 */
#endif
/*		Debug_By_Toggle(22);	*/
		CLR_BIT(LCD_CTRL_PORT,EN); /* disable LCD E=0 */
	    _delay_ms(2);
/*		Debug_By_Toggle(22);*/
		SET_BIT(LCD_CTRL_PORT,EN); /* disable LCD E=0 */
        _delay_ms(2);
/*		Debug_By_Toggle(22);*/
#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((u8_command & 0x0F) << 4);
#else
		LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (u8_command & 0x0F);
#endif
#endif
/*		Debug_By_Toggle(22);	*/
		CLR_BIT(LCD_CTRL_PORT,EN); /* disable LCD E=0 */
        _delay_ms(2);
/*		Debug_By_Toggle(22);*/
}

ERROR_TYPE_t LCD_displayCharacter(uinteg8_t u8_data)
{
	uinteg8_t au8_error=NULL;

	SET_BIT(LCD_CTRL_PORT,RS); /* Data Mode RS=1 */
	CLR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	SET_BIT(LCD_CTRL_PORT,EN); /* Enable LCD E=1 */
	_delay_ms(2);
	#if (DATA_BITS_MODE == 4) /* out the highest 4 bits of the required data to the data bus D4 --> D7 */
	#ifdef UPPER_PORT_PINS
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (u8_data & 0xF0);
	#else
		LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((u8_data & 0xF0) >> 4);
	#endif
	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT = u8_data; /* out the required command to the data bus D0 --> D7 */
	#endif
		CLR_BIT(LCD_CTRL_PORT,EN); /* DISABLE LCD E=1 */
		_delay_ms(2);
		SET_BIT(LCD_CTRL_PORT,EN); /* Enable LCD E=1 */
		_delay_ms(2);
	#ifdef UPPER_PORT_PINS
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((u8_data & 0x0F) << 4);
	#else
		LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (u8_data & 0x0F);
	#endif
		CLR_BIT(LCD_CTRL_PORT,EN); /* DISABLE LCD E=1 */
		_delay_ms(2);


	return au8_error;
}

ERROR_TYPE_t LCD_displayString(const uinteg8_t * ptr_String)
{
  uinteg8_t u8_string_index=0;
  while(ptr_String[u8_string_index])
  {

	  LCD_displayCharacter(ptr_String[u8_string_index]);
	  u8_string_index++;
  }
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display
}

void LCD_goToRowColumn(uinteg8_t row, uinteg8_t col)
{
	uinteg8_t address;
	switch(row)
	{
		case 1:

		address = col-1;
		LCD_sendCommand(address | 0x80 );
		//OR LCD_sendCommand(0x80).
		break;

		case 2:

		address =0x40 + col-1;
		LCD_sendCommand(address | 0x80 );
		//OR LCD_sendCommand(0xC0);

		break;

		#ifdef LCD_SIZE_20_MULTIPLY_4

		case 3:

		address = 0x14 + col-1;
		LCD_sendCommand(address | 0x80 );
		//OR LCD_sendCommand(0x80).
		break;

		case 4:

		address = 0x54 + col-1;
		LCD_sendCommand(address | 0x80 );
		//OR LCD_sendCommand(0xC0);

		break;

		#endif

		default:

		break;
			//Nothing.
	}



}

void LCD_displayStringRowColumn(uinteg8_t row,uinteg8_t col,const uinteg8_t *Str)
{

	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str);

}
void LCD_integerToString(integ16_t s64_value,uinteg8_t row,uinteg8_t col,uinteg8_t u8_Number_Of_Digits)
{
	uinteg8_t buffer[20];
    TransformIntToString(s64_value,buffer,u8_Number_Of_Digits);
	LCD_displayStringRowColumn(row,col,buffer);
}

void LCD_FloatToString(float64_t f_Number,uinteg8_t u8_How_Many_Number_Before_Point,uinteg8_t u8_How_Many_Number_After_Point,uinteg8_t row,uinteg8_t col)
{
	uinteg8_t buffer[20];
	TransformFloatToString(f_Number,u8_How_Many_Number_Before_Point,u8_How_Many_Number_After_Point,buffer);
	LCD_displayStringRowColumn(row,col,buffer);
}
