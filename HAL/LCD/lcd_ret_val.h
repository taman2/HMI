/*
 * lcd_ret_val.h
 *
 *  Created on: Jan 3, 2020
 *      Author: HMI
 */

#ifndef MCAL_LCD_LCD_RET_VAL_H_
#define MCAL_LCD_LCD_RET_VAL_H_

#define INIT_LCD_OK 0u
#define INIT_MODE_BITS_COMMAND 1u
#define INIT_CURSOR_OFF_COMMAND 2u
#define INIT_CLEAR_COMMAND_OK 3u
#define INIT_LCD_NOK 4u

#define COMMAND_CONFIG_OK 0u
#define COMMAND_ENABLE_OK 2u
#define COMMAND_SEND_CURRENTLY 3u
#define COMMAND_SEND_OK 1u
#define COMMAND_NOT_DELIEVERED 4u

#define DISPLAY_DATA_CONFIG_OK 0u
#define DISBLAY_DATA_ENABLE_OK 2u
#define DISPLAY_DATA_NOK 3u
#define DISPLAY_DATA_DISABLE_OK 1u
#define DISPLAY_DATA_INIT_OK 4u

#define DISPLAY_STRING_FINISHED 0u
#define DISPLAY_STRING_CHAR_DONE 1u
#define DISPLAY_STRING_CHAR_NDONE 2u


#endif /* MCAL_LCD_LCD_RET_VAL_H_ */