/*
 * DIO.h
 *
 * Created: 02/11/2019 00:35:59
 *  Author: Native_programmer
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "BitManipulation.h"
#include "Data_Types.h"
#include "AtmegaPort.h"

/*Configuration by user*/
#define PinsNeeded                  32
/*The designer of driver only play on this defines*/
#define DIO_PIN_LEFT_FLOAT          0
#define DIO_PIN_OUTPUT              0
#define DIO_PIN_PULLED_UP           1            
#define No_of_pins  No_of_ports*PortSize

#define CPU_FLAG_Register                     SREG
#define INT_BIT                               I

#define ReadRegisterA                         PINA
#define WriteRegisterA                        PORTA
#define DirectionRegisterA                    DDRA
 
#define ReadRegisterB                         PINB
#define WriteRegisterB                        PORTB
#define DirectionRegisterB                    DDRB

#define ReadRegisterC                         PINC
#define WriteRegisterC                        PORTC
#define DirectionRegisterC                    DDRC

#define ReadRegisterD                         PIND
#define WriteRegisterD                        PORTD
#define DirectionRegisterD                    DDRD

#define ReadRegisterE                         PINE
#define WriteRegisterE                       PORTE
#define DirectionRegisterE                    DDRE

#define ReadRegisterF                         PINF
#define WriteRegisterF                       PORTF
#define DirectionRegisterF                    DDRF

#define ReadRegisterG                         PING
#define WriteRegisterG                       PORTG
#define DirectionRegisterG                    DDRG

#define ExternalInterruptRegister             GICR

#define ExternalInterrupt_2_ENABLE            INT2
#define ExternalInterrupt_0_ENABLE            INT0
#define ExternalInterrupt_1_ENABLE            INT1

#define ExternalInterruptSenseCntrlRegister_1 MCUCR

#define ExternalInterrupt_1_LOW_LEVEL         0b00000000
#define ExternalInterrupt_1_LOGICAL_CHANGE    0b00000100
#define ExternalInterrupt_1_RISING            0b00001000
#define ExternalInterrupt_1_FALLING           0b00001100
#define ExternalInterrupt_0_LOW_LEVEL         0b00000000
#define ExternalInterrupt_0_LOGICAL_CHANGE    0b00000001
#define ExternalInterrupt_0_RISING            0b00000010
#define ExternalInterrupt_0_FALLING           0b00000011

#define ExternalInterruptSenseCntrlRegister_2 MCUCSR

#define ExternalInterrupt_2_FALLING           0b00000000
#define ExternalInterrupt_2_RISING            0b01000000

/*
#define ReadRegisterE       PINE
#define WriteRegisterE      PORTE
#define DirectionRegisterE  DDRE

#define ReadRegisterF       PINF
#define WriteRegisterF      PORTF
#define DirectionRegisterF  DDRF
*/




/***************************************************************/
/******************GENERAL_PARPOUS_INPUT_OUTPUT*****************/
/***************************************************************/

/*Direction*/
#define OUTPUT 1
#define INPUT  0
/*Value*/
#define LOW    0
#define HIGH   1

#define LOWER_NIBBLE  0
#define HIGHER_NIBBLE 1

#define SHIFTED_LEFT 0
#define NOT_SHIFTED  1



//Functions
extern uinteg8_t DIO_Init_Pin(uinteg8_t pin, uinteg8_t direction,uinteg8_t u8_Pull_up);
extern uinteg8_t DIO_Init_Nibble(uinteg8_t por,uinteg8_t nibble,uinteg8_t direction); // function used to initiate data direction of a given port.....  ex:- fun(LCD_PORT,INPUT)

extern uinteg8_t DIO_Init_Nibble(uinteg8_t por,uinteg8_t nibble,uinteg8_t direction); // function to initiate data direction of nibble in a given port.....  ex:- fun(SEVEN_SEGGMENT_PORT,LOWER_NIBBLE,OUTPUT)

extern uinteg8_t DIO_Init_PORT(uinteg8_t Port_Name,uinteg8_t direction); // function used to initiate data direction a single pin in a given register.....ex:- fun(KEY_BAD_PORT,6,INPUT)

//extern uinteg8_t DIO_Init(gstrDioConfig_t* pstr_DioConfig);

extern uinteg8_t DIO_Read_Port (uinteg8_t por, uinteg8_t * ReadData); // function returns port state.....  ex:- fun(LCD_PORT)

extern uinteg8_t DIO_Write_Port(uinteg8_t por,uinteg8_t Data); // function to write data to given port.....  ex:- fun(LCD_PORT,99)

extern uinteg8_t DIO_Read_Pin (uinteg8_t pin, uinteg8_t * ReadData); // function that returns the value of a pin in a register.....  ex:- fun(LCD_PORT,LCD_RS_PIN)

extern uinteg8_t DIO_Write_Pin(uinteg8_t pin,uinteg8_t BitValue); // function used to.....  ex:- fun(LCD_PORT,LCD_ENABLE_PIN,1)

extern uinteg8_t DIO_toggle_Port(uinteg8_t por); // this function is used to toggle defined port.....  ex:- fun(LED_LINE_PORT)

extern uinteg8_t DIO_toggle_Pin(uinteg8_t pin); // this function is used to toggle pin in a defined port .....  ex:- fun(LED_PORT,LED_PIN)

extern uinteg8_t DIO_Read_Nibble(uinteg8_t por,uinteg8_t nibble,uinteg8_t shifted_left_or_not,uinteg8_t * ReadData); // this function is used to read a nibble ....ex:- fun(LCD_DATA_PORT,HIGHER_NIBBLE,NOT_SHIFTED)

extern uinteg8_t DIO_Write_Nibble(uinteg8_t por ,uinteg8_t lower_or_higher_nibble,uinteg8_t data); // this function is used to write on nibble ... ex:- fun(LCD_DATA_PORT,LOWER_NIBBLE,'M')

extern uinteg8_t DIO_Init_Part_In_Port(uinteg8_t Port_Name,uinteg8_t Port_From,uinteg8_t Port_To,uinteg8_t Value);

extern uinteg8_t DIO_Write_Part_In_Port(uinteg8_t Port_Name,uinteg8_t Port_From,uinteg8_t Port_To,uinteg8_t Value);

#define DIO_ERROR_OK   0
#define DIO_ERROR_NOK  1


#endif /* DIO_H_ */