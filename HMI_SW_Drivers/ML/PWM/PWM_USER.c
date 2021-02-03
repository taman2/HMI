/*
 * PWM_USER.c
 *
 * Created: 8/29/2020 4:07:41 PM
 *  Author: Amgad_HMI
 */
#include "PWM_DESIGNER.h"
#include "PWM_USER.h"

#if  (PWM_SOFTWARE==ACTIVATE)


	str_PWM_NODE_t Software_Pwm_Configuration_arr[HOW_MANY_SOFTWARE_PWM_CHANNEL]={{PWM_CHANNEL_11,50},
																				  {PWM_CHANNEL_12,50},
																				  {PWM_CHANNEL_13,50},
																				  {PWM_CHANNEL_14,50}
																				  };

#endif
