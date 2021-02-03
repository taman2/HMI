/*
 * TimerConfig.c
 *
 * Created: 23/11/2019 04:07:28
 *  Author: HMI
 */


#include "Timer_PostBConfig.h"

/*
 *
 * Let's suppose i have two case the 1st one i want to delay for 4ms and we will initiate for 1st case structure
 *              from type called TimerConfig called u_DelayConfig and let us define it
 *
 *
 */

  StrTimerConfiguration_t Delay_TIMER_Init_Config={  TIMER1

													,TIMER_NOTHING_PASSED_FOR_PRESCALER

													,TIMER_MODE_MILIE

													,POLLING                              };


 StrTimerConfiguration_t Switch_Timer_Init_Config= {  TIMER0

													 ,F_CPU_CLOCK_1024_TIMER_0

													 ,COUNTER_MODE

												     ,INTERRUPT                              };

   StrTimerConfiguration_t APP_TIMER_ISR_Config={     TIMER2

													 ,F_CPU_CLOCK_64_TIMER_2

													 ,COUNTER_MODE

											         ,INTERRUPT                              };

   StrTimerConfiguration_t DS18B20_Timer_Init_Config= { TIMER1

											         ,F_CPU_CLOCK_1024_TIMER_1

											         ,COUNTER_MODE

										             ,INTERRUPT                              };
