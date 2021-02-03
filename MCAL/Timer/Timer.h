/*
 * Timer.h
 *
 * Created: 05/11/2019 18:33:53
 *  Author: HMI
 */ 



#ifndef TIMER_H_
#define TIMER_H_

/*- INCLUDES -----------------------------------------------*/

#include"Timer.h"
#include"Data_Types.h"
#include "AtmegaPort.h"

/*- USER CONFIGURATION ----------------------------------------------*/

#define TIMER0_COMP_ISR_NEEDED  1
#define TIMER1_COMPA_ISR_NEEDED 1
#define TIMER1_COMPB_ISR_NEEDED 0
#define TIMER2_COMP_ISR_NEEDED  1

/*- STRUCTS AND UNIONS -------------------------------------*/

typedef struct
{
  uinteg8_t Timer_Channel;  /*Timer Channel (TIMER0 or TIMER1 or TIMER2)*/
  uinteg8_t Timer_Psc;      /*Timer sgau8_Prescaler Based on DataSheet No sgau8_Prescaler or /8 or /64 or .....*/
  uinteg8_t Timer_Mode;     /*Timer Mode Timer or Counter*/
  uinteg8_t Interrupt_Mode; /*Timer Overflow Mode Interrupt or polling*/
}StrTimerConfiguration_t;

/*-  MACROS -------------------------------------------------*/

/******************************************************************/
/*                    Interrupt vectors                           */
/******************************************************************/

/*-  Definition of ISR -------------------------------------------*/


/*-  Definition of Vectors----------------------------------------*/

#if      ATMEGA==8

	#define TIMER1_COMPA_VECTOR  	__vector_6
	#define TIMER1_COMPB_VECTOR 	__vector_7
	#define TIMER2_COMP_VECTOR      __vector_3 

#elif    ATMEGA==16

	#define TIMER1_COMPA_VECTOR  	__vector_6
	#define TIMER1_COMPB_VECTOR 	__vector_7
	#define TIMER2_COMP_VECTOR      __vector_3
	
#elif    ATMEGA==32

	#define TIMER0_COMP_VECTOR		__vector_10
	#define TIMER1_COMPA_VECTOR  	__vector_7
	#define TIMER1_COMPB_VECTOR 	__vector_8
	#define TIMER2_COMP_VECTOR      __vector_4

#endif

/*-  Defination of ISR -------------------------------------------*/
 
#define Timer_ISR(N)            \
void N (void)__attribute((signal,used)); \
void N (void)


/******************************************************************/
/*         Names of Timer Registers and bits                      */
/******************************************************************/
#define CPU_FLAG_Register                                       SREG
#define INT_BIT                                                 I

#define TIMER0_COUNTER_REG                                      TCNT0
#define TIMER0_CNTRL_REG	                                    TCCR0

#define TIMER0_CNTRL_REG_CTC_MODE_VALUE                         0b00001000U	
#define TIMER0_CNTRL_REG_FAST_PWM_MODE_VALUE                    0b01001000U	
#define TIMER0_CNTRL_REG_PHASE_PWM_MODE_VALUE                   0b01000000U
#define TIMER0_CNTRL_REG_SET_OUTPUT_ON_COMPARE                  0b00110000U
#define TIMER0_CNTRL_REG_CLEAR_OUTPUT_ON_COMPARE                0b00100000U

#define TIMER2_CNTRL_REG_FAST_PWM_MODE_VALUE                    0b01001000U
#define TIMER2_CNTRL_REG_PHASE_PWM_MODE_VALUE                   0b01000000U
#define TIMER2_CNTRL_REG_SET_OUTPUT_ON_COMPARE                  0b00110000U
#define TIMER2_CNTRL_REG_CLEAR_OUTPUT_ON_COMPARE                0b00100000U
#if      ATMEGA!=8
#define TIMER0_COMPARE_REG						                OCR0
#endif
#define TIMER0_DATA_DIRCETION_Register                          DDRB
#define TIMER0_Wave_Out_BIT                                     D11

 
#define TIMER1_COUNTER_REG                                      TCNT1
#define TIMER1_CNTRL_REG_A                                      TCCR1A
#define TIMER1_CNTRL_REG_CTC_MODE_VALUE_A                       0b00000000U
#define TIMER1_CNTRL_REG_B                                      TCCR1B

#define TIMER1_CNTRL_REG_CTC_MODE_VALUE_B                       0b00001000U
#define TIMER1_COMP_REG_A                                       OCR1A
#define TIMER1_COMP_REG_B                                       OCR1B

#define TIMER2_COUNTER_REG                                      TCNT2
#define TIMER2_CNTRL_REG                                        TCCR2
#define TIMER2_COMPARE_REG                                      OCR2
#define TIMER2_CNTRL_REG_CTC_MODE_VALUE                         0b00001000U
#define TIMER_EVENT_FLAGS_REG                                   TIFR
#define TIMER0_OVF_COUNT_FLAG_BIT                               TOV0
#define TIMER1_OVF_COUNT_FLAG_BIT                               TOV1
#define TIMER2_OVF_COUNT_FLAG_BIT                               TOV2
#if      ATMEGA!=8

	#define TIMER0_Compare_FLAG_BIT                                 OCF0
	
#endif
#define TIMER1_Compare_A_FLAG_BIT                               OCF1A
#define TIMER1_Compare_B_FLAG_BIT                               OCF1B
#define TIMER2_Compare_FLAG_BIT                                 OCF2
#define TIMER_ENABLE_INTERRUPT_REGISTER                         TIMSK
#define TIMER0_OVF_COUNT_INT_EN_BIT                             TOIE0	
#define TIMER1_OVF_COUNT_INT_EN_BIT                             TOIE1	
#define TIMER2_OVF_COUNT_INT_EN_BIT                             TOIE2
#define TIMER0_Compare_INT_EN_BIT                               OCIE0 	
#define TIMER1_Compare_A_INT_EN_BIT                             OCIE1A 	
#define TIMER1_Compare_B_INT_EN_BIT                             OCIE1B	
#define TIMER2_Compare_INT_EN_BIT                               OCIE2
#define TIMER1_B_COMP_FLAG                                      OCF1B
#define TIMER1_One_Second_Equivalent_Value                      7812U
#define TIMER1_CNTRL_REG_A_SET_OUTPUT_ON_COMPARE                0b11000000U
#define TIMER1_CNTRL_REG_A_CLEAR_OUTPUT_ON_COMPARE              0b10000000U
#define TIMER1_CNTRL_REG_A_FAST_PWM_MODE_VALUE                  0b00000001U
#define TIMER1_CNTRL_REG_B_FAST_PWM_MODE_VALUE                  0b00001000U


/*________________________________________________________________*/
/******************************************************************/
/*                        TIMER_CHANNELS                          */
/******************************************************************/
#define TIMER0 0U
#define TIMER1 1U
#define TIMER2 2U
/*________________________________________________________________*/
/******************************************************************/
/*                        TIMER_CHANNELS OverFlow                 */
/******************************************************************/
#define TIMER0_OVF_COUNT 255U
#define TIMER1_OVF_COUNT 65536U
#define TIMER2_OVF_COUNT 255U
/*________________________________________________________________*/
/******************************************************************/
/*                        TIMER_MODE                              */
/******************************************************************/
#define TIMER_MODE_MICRO  0U
#define COUNTER_MODE      1U
#define TIMER_MODE_MILIE  2U

/*________________________________________________________________*/
/******************************************************************/
/*                        sgau8_Prescaler                         */
/******************************************************************/

/*_______TIMER0__________________________________*/
#define NO_CLOCK_TIMER_0     					0U
#define F_CPU_CLOCK_TIMER_0   					1U
#define F_CPU_CLOCK_8_TIMER_0 					2U
#define F_CPU_CLOCK_64_TIMER_0					3U
#define F_CPU_CLOCK_256_TIMER_0			     	4U
#define F_CPU_CLOCK_1024_TIMER_0				5U
#define F_EXTERNAL_CLOCK_FALLING_TIMER_0		6U
#define F_EXTERNAL_CLOCK_RISING_TIMER_0		    7U

/*_______TIMER1__________________________________*/
#define NO_CLOCK_TIMER_1     					0U
#define F_CPU_CLOCK_TIMER_1   					1U
#define F_CPU_CLOCK_8_TIMER_1 					2U
#define F_CPU_CLOCK_64_TIMER_1					3U
#define F_CPU_CLOCK_256_TIMER_1				    4U
#define F_CPU_CLOCK_1024_TIMER_1				5U
#define F_EXTERNAL_CLOCK_FALLING_TIMER_1	 	6U
#define F_EXTERNAL_CLOCK_RISING_TIMER_1	        7U

/*_______TIMER2__________________________________*/
#define NO_CLOCK_TIMER_2     					 0U
#define F_CPU_CLOCK_TIMER_2   					 1U
#define F_CPU_CLOCK_8_TIMER_2 					 2U
#define F_CPU_CLOCK_32_TIMER_2					 3U
#define F_CPU_CLOCK_64_TIMER_2					 4U
#define F_CPU_CLOCK_128_TIMER_2			         5U
#define F_CPU_CLOCK_256_TIMER_2		 	         6U
#define F_CPU_CLOCK_1024_TIMER_2				 7U
 
#define Max_Prescaler_possiblities               7U
#define TIMER_NOTHING_PASSED_FOR_PRESCALER       0U
#define TIMER_MODE_NO_NEED_TO_COUNT_IN_INTERRUPT 0U
/*________________________________________________________________*/
/******************************************************************/
/*                        OverFlow Mode                           */
/******************************************************************/

#define POLLING      0U
#define INTERRUPT    1U

/*________________________________________________________________*/
/******************************************************************/
/*                        ERROR STATUS                            */
/******************************************************************/
#define TIMER_ERROR_OK     0U
#define TIMER_ERROR_NOK    1U
/*______________________________________________________________________________________________________________________________*/
/******************************************************************/
/*                    Other types                                 */
/******************************************************************/
#define  NO_OF_CHANNELS               3U
#define  GLOBAL_INTERRUPT             7U
#define  TIMER_Enable                 1U
#define  TIMER_Disable                0U
#define  NoPeriod                    -1
/*--Externs-------------------------------------------------*/
/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS ---------------------------------*/
#define TIMER_CLR_INT_FLAG(N)   CLR_INT_FLAG(TIMER_EVENT_FLAGS_REG,N)
/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer/Counter Initialization
 * Input     : Timer_Configuration_S* ps_Copy_Measurement_ECU_TIMER_Init_Config (Struct contain : Timer Channel, sgau8_Prescaler, Timer mode , Mode as described in Struct)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uinteg8_t  Timer_Init(StrTimerConfiguration_t* ps_Copy_Measurement_ECU_TIMER_Init_Config);
/*_______________________________________________________________________________________________________________________________*/


/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer/Counter Start
 * Input     :  Timer Channel(Timer Channel (TIMER0 or Timer1 or Timer2), Tick Counting (Counts given by user)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uinteg8_t Timer_Start(uinteg8_t u8_Copy_TIMER_Start_TIMERChannel,uinteg32_t u32_Copy_TIMER_Start_tickCounts,PntrToFunc_t PntrToFunc_t_Copy_TIMER_Start_ISR);
/*_______________________________________________________________________________________________________________________________*/


/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer/Counter Stop
 * Input     :  Timer Channel(Timer Channel (TIMER0 or Timer1 or Timer2)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uinteg8_t  Timer_Pause(uinteg8_t u8_Copy_TIMER_Start_TIMERChannel);
/*_______________________________________________________________________________________________________________________________*/

/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer Reset
 * Input     :  Timer Channel(Timer Channel (TIMER0 or Timer1 or Timer2)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uinteg8_t Timer_Reset(uinteg8_t u8_Copy_TIMER_Start_TIMERChannel);
/*_______________________________________________________________________________________________________________________________*/

/*_______________________________________________________________________________________________________________________________*/
/*Description: Get Timer Tick Time value to use it by user
 * Input     : Timer Channel(Timer Channel (TIMER0 or Timer1 or Timer2), *Timer_time (Pointer to return Value)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uinteg8_t Timer_Get_tickTime(uinteg8_t u8_Copy_TIMER_Start_TIMERChannel, void volatile*Copy_uint8Ptr_TIMERTickTime);
/*_______________________________________________________________________________________________________________________________*/

/*_______________________________________________________________________________________________________________________________*/
/*Description: Get Timer Flag Status
 * Input     : Timer Channel(Timer Channel (TIMER0 or Timer1 or Timer2), *FlagStatus (Pointer to Flag)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uinteg8_t Timer_Get_FlagStatus(uinteg8_t u8_Copy_TIMER_Start_TIMERChannel, void volatile *Copy_uint8Ptr_FlagStatus);
/*_______________________________________________________________________________________________________________________________*/


#endif /* TIMER_H_ */
