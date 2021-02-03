/*
 * PWM_DESIGNER.h
 *
 * Created: 8/29/2020 6:05:32 PM
 *  Author: programer
 */ 


#ifndef PWM_DESIGNER_H_
#define PWM_DESIGNER_H_

#include "Data_Types.h"
#include "PWM_USER.h"

 typedef struct
 {
	 uinteg8_t u8_PIN;
	 uinteg8_t u8_Duty_cycle;
 }str_PWM_NODE_t;
 
extern str_PWM_NODE_t Software_Pwm_Configuration_arr[HOW_MANY_SOFTWARE_PWM_CHANNEL];
/*_______PWM0__________________________________*/
#define NO_CLOCK_PWM_0     					    0U
#define F_CPU_CLOCK_PWM_0   					1U
#define F_CPU_CLOCK_8_PWM_0 					2U
#define F_CPU_CLOCK_64_PWM_0					3U
#define F_CPU_CLOCK_256_PWM_0			       	4U
#define F_CPU_CLOCK_1024_PWM_0				    5U
#define F_EXTERNAL_CLOCK_FALLING_PWM_0		    6U
#define F_EXTERNAL_CLOCK_RISING_PWM_0		    7U

/*_______PWM1__________________________________*/
#define NO_CLOCK_PWM_1     					    0U
#define F_CPU_CLOCK_PWM_1   					1U
#define F_CPU_CLOCK_8_PWM_1 					2U
#define F_CPU_CLOCK_64_PWM_1					3U
#define F_CPU_CLOCK_256_PWM_1				    4U
#define F_CPU_CLOCK_1024_PWM_1				    5U
#define F_EXTERNAL_CLOCK_FALLING_PWM_1	 	    6U
#define F_EXTERNAL_CLOCK_RISING_PWM_1	        7U

/*_______PWM2__________________________________*/
#define NO_CLOCK_PWM_2     					     0U
#define F_CPU_CLOCK_PWM_2   					 1U
#define F_CPU_CLOCK_8_PWM_2 					 2U
#define F_CPU_CLOCK_32_PWM_2					 3U
#define F_CPU_CLOCK_64_PWM_2					 4U
#define F_CPU_CLOCK_128_PWM_2			         5U
#define F_CPU_CLOCK_256_PWM_2		 	         6U
#define F_CPU_CLOCK_1024_PWM_2				     7U

#define Max_Prescaler_possiblities               7U
#define PWM_NOTHING_PASSED_FOR_PRESCALER         0U

#define PWM_FAST            5u
#define PWM_PHASE_CORRECT   6u
#define ACTIVATE            7u
#define DEACTIVATE          8u
#define CLEAR_ON_COMPARE    9u
#define SET_ON_COMPARE      10u
#define PWM_CHANNEL_0       0u
#define PWM_CHANNEL_1       1u
#define PWM_CHANNEL_2       2u
#define PWM_CHANNEL_3       3u
#define PWM_CHANNEL_4       4u
#define PWM_CHANNEL_5       5u
#define PWM_CHANNEL_6       6u
#define PWM_CHANNEL_7       7u
#define PWM_CHANNEL_8       8u  
#define PWM_CHANNEL_9       9u
#define PWM_CHANNEL_10      10u
#define PWM_CHANNEL_11      11u
#define PWM_CHANNEL_12      12u
#define PWM_CHANNEL_13      13u
#define PWM_CHANNEL_14      14u
#define PWM_CHANNEL_15      15u
#define PWM_CHANNEL_16      16u
#define PWM_CHANNEL_17      17u
#define PWM_CHANNEL_18      18u
#define PWM_CHANNEL_19      19u
#define PWM_CHANNEL_20      20u
#define PWM_CHANNEL_21      21u
#define PWM_CHANNEL_22      22u
#define PWM_CHANNEL_23      23u
#define PWM_CHANNEL_24      24u
#define PWM_CHANNEL_25      25u
#define PWM_CHANNEL_26      26u
#define PWM_CHANNEL_27      27u
#define PWM_CHANNEL_28      28u
#define PWM_CHANNEL_29      29u
#define PWM_CHANNEL_30      30u
#define PWM_CHANNEL_31      31u

void PWM_SOFTWARE_INIT(void);
void PWM_HARDWARE_INIT(void);
void PWM_HARDWARE_CHANNEL(uinteg8_t u8_Channel,uinteg8_t u8_Percentage);


#endif /* PWM_DESIGNER_H_ */