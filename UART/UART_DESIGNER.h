/*
 * UART_DESIGNER.h
 *
 * Created: 9/13/2020 4:15:53 PM
 *  Author: Mohamed
 */ 


#ifndef UART_DESIGNER_H_
#define UART_DESIGNER_H_
#include "UART.h"

/*Asynchronous mode */

#define UART_BUAD_RATE_REG_value    ((F_CPU/(16(BAUD_RATE_VALUE))))
#define ENABLE_RX_TX                  (1<<RXEN)|(1<<TXEN)   /* Enable receiver and transmitter */
#define UART_FRAME_FORMAT_2STOP_BITS ((1<<URSEL)|(1<<USBS)|(3<<UCSZ0))	/* Set frame format: 8data, 2stop bit */
#define UART_FRAME_FORMAT_1STOP_BIT  ( (1<<URSEL)|(3<<UCSZ0) )/* Set frame format: 8data, 1stop bit */
                                     
#define UART_COTR_STATUS_REGB                         UCSRB
#define UART_BUAD_RATE_REG_HIGH_value                 UBRRH
#define UART_BUAD_RATE_REG_LOW_value                  UBRRL
#define UART_COTR_STATUS_REGC                         UCSRC 
#define UART_COTR_STATUS_REGA                         UCSRA
#define UART_COTR_STATUS_REGB                         UCSRB
//#define UART_TRANSMIT_9TH_DATA_BIT                    TXB8

#define UART_DATA_BUFFER                              UDR
#define UART_DATA_REG_EMPTY                           UDRE







#endif /* UART_DESIGNER_H_ */