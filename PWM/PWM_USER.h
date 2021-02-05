/*
 * PWM_USER.h
 *
 * Created: 8/29/2020 3:53:34 PM
 *  Author: Programmer
 */ 


#ifndef PWM_USER_H_
#define PWM_USER_H_

#include "PWM_DESIGNER.h"

	#define HOW_MANY_SOFTWARE_PWM_CHANNEL 3U
	/**Note:Software Pulse width modulation works on condition 16MHZ  **/
	#define PWM_SOFTWARE				 DEACTIVATE
	/**Note:Software Pulse width modulation works on condition 8MHZ OR 16 MHZ **/
	#define PWM_HARDWARE                 ACTIVATE
	
	#define PWM_H_11					 ACTIVATE
	#define PWM_H_11_OUTPUT_TYPE         PWM_FAST
	#define PWM_H_11_OUTPUT_SHAPE        CLEAR_ON_COMPARE
	#define PWM_H_11_FREQUENCY           F_CPU_CLOCK_256_PWM_0
	#define PWM_H_11_DUTY_CYCLE		     100u//Percentage

	#define PWM_H_29					 DEACTIVATE
	#define PWM_H_29_OUTPUT_TYPE         PWM_PHASE_CORRECT
	#define PWM_H_29_OUTPUT_SHAPE        CLEAR_ON_COMPARE
	#define PWM_H_29_FREQUENCY           F_CPU_CLOCK_256_PWM_1
	#define PWM_H_29_DUTY_CYCLE          0u//Percentage

	#define PWM_H_31				     ACTIVATE
	#define PWM_H_31_OUTPUT_TYPE         PWM_FAST
	#define PWM_H_31_OUTPUT_SHAPE	     CLEAR_ON_COMPARE
	#define PWM_H_31_FREQUENCY           F_CPU_CLOCK_PWM_2
	#define PWM_H_31_DUTY_CYCLE          0u//Percentage

#endif /* PWM_USER_H_ */