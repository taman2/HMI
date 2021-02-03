/*
 * OneWire.h
 *
 * Created: 10/18/2020 3:16:58 PM
 *  Author: HMI
 */ 


#ifndef ONEWIRE_H_
#define ONEWIRE_H_
#include "DIO.h"
                       
#define ONEWIRE_OPERATION_POLLING                0U
#define ONEWIRE_OPERATION_TIME_BASE              1U
#define ONEWIRE_GET_THE_RESET_RESPOND_LOW        2U
#define ONEWIRE_GET_THE_RESET_RESPOND_PULLED_UP  3U
#define ONEWIRE_OPERATION                        ONEWIRE_OPERATION_POLLING
#define ONE_WIRE_NODE_NOT_RESPONDING             HIGH
#define ONE_WIRE_NODE_RESPONDED                  LOW


void OneWire_Init(uinteg8_t u8_OneWire_Pin);
void OneWire_Get_The_Reset_Respond(uinteg8_t u8_OneWire_Pin);
void OneWire_Byte_Write(uinteg8_t u8_OneWire_Pin,uinteg8_t u8_OneWire_Byte_Write_Byte);
void OneWire_Byte_Read(uinteg8_t u8_OneWire_Pin ,uinteg8_t*pu8_OneWire_Byte_Read_Byte);
void OneWire_Two_Bytes_Read(uinteg8_t u8_OneWire_Pin ,uinteg16_t*pu16_OneWire_Two_Bytes_Read_Byte);
#endif /* ONEWIRE_H_ */