/*
 * Seven_Segments.h
 *
 * Created: 6/30/2020 12:35:00 PM
 *  Author: HMI
 */ 


#ifndef SEVEN_SEGMENTS_H_
#define SEVEN_SEGMENTS_H_

#include "Data_Types.h"
#include "DIO.h"

/*Pre-compile Configuration*/


/*
#define Seven_Segments_Comman_Pin_Channel      'C'
#define Seven_Segments_Draw_Channel            'B'
*/


#define Seven_Segments_Comman_Pin_Channel      'C'
#define Seven_Segments_Draw_Channel            'B'

#define Seven_Segment_1                         1
#define Seven_Segment_2                         2
#define Seven_Segment_3                         4
#define Seven_Segment_4                         8
#define Seven_Segment_5                         16
#define TWO_POINTS_DEFINE                       0

/*Defines for the abstracted user*/

#define UNITS                                   0
#define TENS                                    1
#define HUNDRADS                                2
#define THOUSANDS                               3
#define TENS_THOUSANDS                          4
#define HUNDRADS_THOUSANDS                      5
#define R                                    0X88
#define E                                    0X84
#define S                                    0x92
#define T                                    0X87
#define BLANK                                0XFF

/*Defines for the driver itself*/ 


#define POINTS_CONFIURED     1   
#define NO_POINTS_CONFIURED  0


/*Prototype of functions*/

void Seven_Segments_Init();
/*void Seven_Segments_Write_Integer_Number(uinteg8_t u8_Copy_Seven_Segment_of_Comman_Pin_Channel,uinteg32_t u32_Copy_of_Number,uinteg8_t u8_Units_Or_Tens);*/
void Seven_Segments_Turn_off();
void Seven_Segments_Write_Integer_Number(uinteg8_t u8_Copy_Seven_Segment_of_Comman_Pin_Channel,uinteg8_t u8_Copy_of_Number,uinteg8_t u8_Write_Point);
void Seven_Segments_Write_Something(uinteg8_t u8_Copy_Seven_Segment_of_Comman_Pin_Channel,uinteg8_t u8_Copy_of_Thing_Representation,uinteg8_t u8_Write_Point);
#endif /* SEVEN_SEGMENTS_H_ */