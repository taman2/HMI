/*
 * UART.h
 *
 * Created: 9/13/2020 4:15:26 PM
 *  Author: Mohamed
 */ 


#ifndef UART_H_
#define UART_H_

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

/* main functions prototypes */


void USART_Init(struct USART_Config config);
/*void USART_Init( struct USART_Config SET_UART_CONFIG );*/
void USART_Transmit( uinteg8_t data );
uinteg8_t USART_Receive(void);
void USART_SendChar(uinteg8_t );
uinteg8_t USART_ReceiveChar(void);
void UART_ReceiveString(uinteg8_t *Str);
void UART_ReceiveBuffer(uinteg8_t *str);
void USART_Recieve_Packet (uinteg8_t *Packet_Receive_Buffer ,uinteg8_t Tail_Byte);
void USART_Send_Packet(volatile uinteg8_t *str,uinteg8_t Stop_Byte);
void USART_Receive_Byte_Iterrupt(volatile uinteg8_t *Byte_Address);




#endif /* UART_H_ */