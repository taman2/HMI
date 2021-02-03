/*
 * AtmegaPort.h
 *
 * Created: 04/11/2019 01:15:54
 *  Author: Amgad_HMI
 */ 


#ifndef AtmegaPort_H_
#define AtmegaPort_H_

#include "Data_types.h"
/*Configuration by user*/
#define ATMEGA 32
/*The designer of driver only play on this defines*/
#if    ATMEGA==8
#define  No_of_ports 3
#elif  ATMEGA==16
#define  No_of_ports 4
#elif ATMEGA==32
#define  No_of_ports 4
#elif ATMEGA==128
#define  No_of_ports 6
#endif

#define  DataBus     8
#define  PortSize    DataBus


#define  EnableGeneralInterrupt()       SET_BIT(SREG,I)
#define  DisableGeneralInterrupt()      CLR_BIT(SREG,I)

//TWI Registers
#define TWBR    ( *((volatile uinteg8_t* )(0X20)) )
#define TWSR    ( *((volatile uinteg8_t* )(0X21)) )
#define TWAR    ( *((volatile uinteg8_t* )(0X22)) )
#define TWDR    ( *((volatile uinteg8_t* )(0X23)) )
//ADC Registers
#define ADCL    ( *((volatile uinteg8_t* )(0X24)) )
#define ADCH    ( *((volatile uinteg8_t* )(0X25)) )
#define ADCSRA  ( *((volatile uinteg8_t* )(0X26)) )
#define ADMUX   ( *((volatile uinteg8_t* )(0X27)) )
//Analog Comparator Registers
#define ACSR    ( *((volatile uinteg8_t* )(0X28)) )
//UART Registers
#define UBRRL   ( *((volatile uinteg8_t* )(0X29)) )
#define UCSRB   ( *((volatile uinteg8_t* )(0X2A)) )
#define UCSZ2    2
#define TXEN     3
#define RXEN     4
#define UDRIE    5
#define TXCIE    6
#define RXCIE    7
#define UCSRA   ( *((volatile uinteg8_t* )(0X2B)) )
#define UDRE     5
#define RXC      7
#define UDR     ( *((volatile uinteg8_t* )(0X2C)) )


//DIO Registers
#define PIND    ( *((volatile uinteg8_t* )(0X30)) )
#define DDRD    ( *((volatile uinteg8_t* )(0X31)) )
#define PORTD   ( *((volatile uinteg8_t* )(0X32)) )
#define PINC    ( *((volatile const uinteg8_t* )(0X33)) )
#define DDRC    ( *((volatile uinteg8_t* )(0X34)) )
#define PORTC   ( *((volatile uinteg8_t* )(0X35)) )
#define PINB    ( *((volatile const uinteg8_t* )(0X36)) )
#define DDRB    ( *((volatile uinteg8_t* )(0X37)) )
#define PORTB   ( *((volatile uinteg8_t* )(0X38)) )
#define PINA    ( *((volatile const uinteg8_t* )(0X39)) )
#define DDRA    ( *((volatile uinteg8_t* )(0X3A)) )
#define PORTA   ( *((volatile uinteg8_t* )(0X3B)) )
//EEPROM Registers
#define EECR    ( *((volatile uinteg8_t* )(0X3C)) )
#define EEDR    ( *((volatile uinteg8_t* )(0X3D)) )
#define EEARL   ( *((volatile uinteg8_t* )(0X3E)) )
#define EEARH   ( *((volatile uinteg8_t* )(0X3F)) )
//The rest of UART Registers
#define UCSRC   ( *((volatile uinteg8_t* )(0X40)) )
#define UCPOL    0
#define UCSZ0    1
#define UCSZ1    2
#define USBS     3
#define UPMO     4
#define UPM1     5
#define UMSEL    6
#define URSEL    7
#define UBRRH   ( *((volatile uinteg8_t* )(0X40)) )
#define WDTCR   ( *((volatile uinteg8_t* )(0X41)) )
//Asynchronous Timer Registers
#define ASSR    ( *((volatile uinteg8_t* )(0X42)) )
#define OCR2    ( *((volatile uinteg8_t* )(0X43)) )
#define TCNT2   ( *((volatile uinteg8_t* )(0X44)) )
#define TCCR2   ( *((volatile uinteg8_t* )(0X45)) )
//Timer1 Registers
#define ICR1	( *((volatile uinteg16_t* )(0X46)) )
#define ICR1L	( *((volatile uinteg8_t* )(0X46)) )
#define ICR1H   ( *((volatile uinteg8_t* )(0X47)) )
#define OCR1B   ( *((volatile uinteg16_t*)(0X48)) )
#define OCR1BL  ( *((volatile uinteg8_t* )(0X48)) )
#define OCR1BH  ( *((volatile uinteg8_t* )(0X49)) )
#define OCR1A   ( *((volatile uinteg16_t* )(0X4A)) )
#define OCR1AL  ( *((volatile uinteg8_t* )(0X4A)) )
#define OCR1AH  ( *((volatile uinteg8_t* )(0X4B)) )
#define TCNT1   ( *((volatile uinteg16_t* )(0X4C)) )
#define TCNT1L  ( *((volatile uinteg8_t* )(0X4C)) )
#define TCNT1H  ( *((volatile uinteg8_t* )(0X4D)) )
#define TCCR1B  ( *((volatile uinteg8_t* )(0X4E)) )
#define TCCR1A  ( *((volatile uinteg8_t* )(0X4F)) )
//Special Function Register
#define SFIOR   ( *((volatile uinteg8_t* )(0X50)) )
//On-Chip Debug Register
#define OCDR    ( *((volatile uinteg8_t* )(0X51)) )
////On-Chip Debug Register
#define OSCCAL  ( *((volatile uinteg8_t* )(0X51)) )
//TIMER0 Registers
#define TCNT0   ( *((volatile uinteg8_t* )(0X52)) )
#define TCCR0   ( *((volatile uinteg8_t* )(0X53)) )
//MCU Status and Control Registers
#define MCUCSR  ( *((volatile uinteg8_t* )(0X54)) )
#define MCUCR   ( *((volatile uinteg8_t* )(0X55)) )
//Register of TWO WIRE Control Register
#define TWCR    ( *((volatile uinteg8_t* )(0X56)) )

#define SPMCR   ( *((volatile uinteg8_t* )(0X57)) )
/*Timer's Interrupt Flags*/
#define TIFR    ( *((volatile uinteg8_t* )(0X58)) )
#define TOV0    0
#define OCF0    1
#define TOV1    2
#define OCF1B   3
#define OCF1A   4
#define ICF1    5
#define TOV2    6
#define OCF2    7

#define TIMSK   ( *((volatile uinteg8_t* )(0X59)) )
/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0
//General Interrupt Flags
#define GIFR    ( *((volatile uinteg8_t* )(0X5A)) )
#define GICR    ( *((volatile uinteg8_t* )(0X5B)) )
#define INT1    7
#define INT0    6
#define INT2    5
//TIMER0 Output Compare Register
#define OCR0    ( *((volatile uinteg8_t* )(0X5C)) )
//Stack pointer Register
#define SPL     ( *((volatile uinteg8_t* )(0X5D)) )
#define SPH     ( *((volatile uinteg8_t* )(0X5E)) )
//Status Register
#define SREG    ( *((volatile uinteg8_t* )(0X5F)) )
#define I       7

//SPI Registers
#define SPCR    ( *((volatile uinteg8_t* )(0X2D)) )
#define SPCR_SPR0 0
#define SPCR_SPR1 1
#define SPCR_CPHA 2
#define SPCR_CPOL 3
#define SPCR_MSTR 4
#define SPCR_DORD 5
#define SPCR_SPE  6
#define SPCR_SPIE 7
#define SPSR    ( *((volatile uinteg8_t* )(0X2E)) )
#define SPSR_SPIF  7
#define SPSR_WCOL  6
#define SPSR_SPI2X 0
#define SPDR    ( *((volatile uinteg8_t* )(0X2F)) )

/*
#define A           0
#define B           1
#define C           2
#define D           3
#define PORT(PORT_NAME)    ( *((volatile INT8U* )      (0X3B-3(PORT_NAME)) )
#define DDRA(PORT_NAME)    ( *((volatile INT8U* )      (0X3A-3(PORT_NAME)) )
#define PINA(PORT_NAME)    ( *((volatile const INT8U* )(0X39-3(PORT_NAME)) )
*/

#endif /* AtmegaPort_H_ */