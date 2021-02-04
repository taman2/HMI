/*
 * UART.c
 *
 * Created: 10/4/2020 2:25:35 PM
 *  Author: Mohamed
 */ 

#define  F_CPU 8000000UL
#include "util/delay.h"
#include "avr/io.h"
#include "stdlib.h"
#include "Data_Types.h"
#include "UART.h"


uinteg16_t  MYUBRR=0;
/*POINTER TO FUCTION CARRY THE ADRESS OF TX__ISR_FUNCTION  */
void (*ptr_To_TX_Int_fun)(void)=0;
void (*ptr_To_RX_Int_fun)(void)=0;

void USART_Init(struct USART_Config config){
	USART_PRE_CONFIGRATION=config;
	
/*****************************************************USART BAUD RATE****************************************************************/

	if(USART_PRE_CONFIGRATION.SYNCH_MODE== USART_ASYNCH_MODE && USART_PRE_CONFIGRATION.SPEED_MODE== USART_NORMAL_SPEED){
		MYUBRR   = (uinteg16_t)  (((F_CPU / (  BUAD_RATE* 16UL))) - 1);
	}
   else if(	USART_PRE_CONFIGRATION.SYNCH_MODE== USART_ASYNCH_MODE && USART_PRE_CONFIGRATION.SPEED_MODE== USART_DOUBLE_SPEED){
	   
       MYUBRR   = (uinteg16_t)  (((F_CPU / (  BUAD_RATE* 8UL))) - 1);
	}
   else if(	USART_PRE_CONFIGRATION.SYNCH_MODE== USART_SYNCH_MODE ){
	MYUBRR   = (uinteg16_t) (((F_CPU / (  BUAD_RATE* 2UL))) - 1);   
   }
   	   UBRRL=(uinteg8_t)(MYUBRR);
   	   UBRRH=(uinteg8_t)(MYUBRR>>8);
   /**************************************USART ENABLE RX & TX******************************************************/


    if(USART_PRE_CONFIGRATION.TX_==USART_TX_ENABLE){
		UCSRB |=   (1 << TXEN);
	}
	else if(USART_PRE_CONFIGRATION.TX_==USART_TX_DISABLE){
	  clearBit(UCSRB, TXEN);
	}
	if(USART_PRE_CONFIGRATION.RX_==USART_RX_ENABLE){
		UCSRB |=   (1 << RXEN);
	}
	else if(USART_PRE_CONFIGRATION.TX_==USART_TX_DISABLE){
		clearBit (UCSRB, RXEN);
	}
	/*******************************************USART DATA FORMAT CHAR SIZE ***********************************************/

   if(USART_PRE_CONFIGRATION.CHAR_SIZE==USART_DATA_FORMAT_8BIT_MODE){
	   UCSRC |=USART_DATA_FORMAT_8BIT_MODE |(1 << URSEL);
	 //   /*(1 << URSEL) |*/ (1 << UCSZ0) | (1 << UCSZ1); 
   }
   else if(USART_PRE_CONFIGRATION.CHAR_SIZE==USART_DATA_FORMAT_7BIT_MODE){
	   UCSRC |=USART_DATA_FORMAT_8BIT_MODE;
	   // /*(1 << URSEL) |*/ (1 << UCSZ0) | (0 << UCSZ1);

   }
   /*******************************************USART TX & RX INTERUUPT ENABLE OR DISABLE **************************************/
   
    if(USART_PRE_CONFIGRATION.RX_INTERRUPT==USART_RX_INTERRUPT_ENABLE){
	    UCSRB |= (1<<7);
    }
    else if(USART_PRE_CONFIGRATION.RX_INTERRUPT==USART_RX_INTERRUPT_DISABLE){
		clearBit(UCSRB,RXCIE);
    }
	if(USART_PRE_CONFIGRATION.TX_INTERRUPT==USART_TX_INTERRUPT_ENABLE){
		UCSRB |= (1<<TXCIE);
	}
	else if(USART_PRE_CONFIGRATION.TX_INTERRUPT==USART_TX_INTERRUPT_DISABLE){
		clearBit(UCSRB,TXCIE);
	}
   
}

void USART_Transmit( uinteg8_t data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}

uinteg8_t USART_Receive( void )
{
	//return UDR;
	/*Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR;
}
void USART_Send_Packet(volatile uinteg8_t *str,uinteg8_t Stop_Byte)
{
	 uinteg8_t j=0;
	
	while (str[j]!=Stop_Byte)		/* Send string till stop byte*/
	{
		USART_Transmit(str[j]);
		j++;
	}
  USART_Transmit(str[j]);

}
void USART_Recieve_Packet (uinteg8_t *Packet_Receive_Buffer ,uinteg8_t Tail_Byte){
	  uinteg8_t i=0;
	  
Packet_Receive_Buffer[i]= USART_Receive();

	while( Packet_Receive_Buffer[i]!= Tail_Byte  ){
		if(Packet_Receive_Buffer[0]!=0xaa){
			break;
		}
		i++;
		Packet_Receive_Buffer[i]=USART_Receive();
	}

}
void USART_Receive_Byte_Iterrupt(volatile uinteg8_t *Byte_Address)
{
	*Byte_Address=UDR;
}
void USART_RX_Int_CallBack_fun(void (*ptr_To_Fun)(void)){
	
	ptr_To_TX_Int_fun=ptr_To_Fun;

	
}
void USART_TX_Int_CallBack_fun(void (*ptr_To_Fun)(void)){
	
	ptr_To_Fun=ptr_To_TX_Int_fun;
	
}
ISR(USART_RXC_vect)
{
	ptr_To_TX_Int_fun();
}