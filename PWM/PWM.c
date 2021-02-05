/*
 * PWM.c
 *
 * Created: 8/29/2020 3:47:27 PM
 *  Author: mohaned
 */



#include "PWM.h"
#include "DIO.h"
#include "Timer_PostBConfig.h"

#if (PWM_SOFTWARE==ACTIVATE)
    void PWM_SOFTWARE_ISR(void)
	{
      Debug_By_Toggle(0);
/*
	   DIO_Init_Pin(0,OUTPUT,0);
	   DIO_Write_Pin(0,1);*/
	   static volatile uinteg8_t su8_PWM_SOFTWARE_ISR_COUNTER=0;
	   su8_PWM_SOFTWARE_ISR_COUNTER++;

   		for(uinteg8_t u8_index=0;u8_index<HOW_MANY_SOFTWARE_PWM_CHANNEL;u8_index++)
   		{
			if(Software_Pwm_Configuration_arr[u8_index].u8_Duty_cycle==100)
			{
				DIO_Write_Pin(Software_Pwm_Configuration_arr[u8_index].u8_PIN,HIGH);
			}
			else if(Software_Pwm_Configuration_arr[u8_index].u8_Duty_cycle==0)
			{
				DIO_Write_Pin(Software_Pwm_Configuration_arr[u8_index].u8_PIN,LOW);
			}
			else
			{
	   			if(((Software_Pwm_Configuration_arr[u8_index].u8_Duty_cycle*255)/100)==su8_PWM_SOFTWARE_ISR_COUNTER)
	   			{
		   			DIO_Write_Pin(Software_Pwm_Configuration_arr[u8_index].u8_PIN,LOW);
	   			}

			}
			if(su8_PWM_SOFTWARE_ISR_COUNTER==255u)
			{
				DIO_Write_Pin(Software_Pwm_Configuration_arr[u8_index].u8_PIN,HIGH);
			}
   		}
/*	   DIO_Write_Pin(0,0);*/



	}
/**Take care we can't use all values of prescalers as the ISR TAKES 30U The best the prescaler from range 256 to 1024**/
void PWM_SOFTWARE_INIT(void)
{
          Timer_Init(&PWM_TIMER_Init_Config);
          Timer_Start(TIMER2,15U,PWM_SOFTWARE_ISR);

   		  for(uinteg8_t u8_index=0;u8_index<HOW_MANY_SOFTWARE_PWM_CHANNEL;u8_index++)
   		  {
	   			DIO_Init_Pin(Software_Pwm_Configuration_arr[u8_index].u8_PIN,OUTPUT,DIO_PIN_OUTPUT);
	         	DIO_Write_Pin(Software_Pwm_Configuration_arr[u8_index].u8_PIN,HIGH);
   		  }
	}
	void PWM_SOFTWARE_CHANNEL(uinteg8_t u8_Channel,uinteg8_t u8_Percentage)
	{

		for(uinteg8_t u8_index=0;u8_index<HOW_MANY_SOFTWARE_PWM_CHANNEL;u8_index++)
		{
			if(Software_Pwm_Configuration_arr[u8_index].u8_PIN==u8_Channel)
			{
				Software_Pwm_Configuration_arr[u8_index].u8_Duty_cycle=u8_Percentage;
				break;
			}
		}

	}

#endif
#if (PWM_HARDWARE==ACTIVATE)

void PWM_HARDWARE_INIT(void)
{
		#if   (PWM_H_11==ACTIVATE)

			DIO_Init_Pin(11,OUTPUT,DIO_PIN_OUTPUT);


		   #if (PWM_H_11_OUTPUT_TYPE==PWM_FAST)


			   TIMER0_CNTRL_REG=TIMER0_CNTRL_REG_FAST_PWM_MODE_VALUE;

				#if   (PWM_H_11_DUTY_CYCLE==100u)

					DIO_Write_Pin(11,HIGH);
					TIMER0_CNTRL_REG|=PWM_H_11_FREQUENCY;

				#elif (PWM_H_11_DUTY_CYCLE==0u)

					DIO_Write_Pin(11,LOW);
					TIMER0_CNTRL_REG|=PWM_H_11_FREQUENCY;

				#else

					TIMER0_COMPARE_REG=((PWM_H_11_DUTY_CYCLE*255u))/100u;
					#if   (PWM_H_11_OUTPUT_SHAPE==CLEAR_ON_COMPARE)

						TIMER0_CNTRL_REG|=PWM_H_11_FREQUENCY|TIMER0_CNTRL_REG_CLEAR_OUTPUT_ON_COMPARE;

					#elif (PWM_H_11_OUTPUT_SHAPE==SET_ON_COMPARE)

						TIMER0_CNTRL_REG|=PWM_H_11_FREQUENCY|TIMER0_CNTRL_REG_SET_OUTPUT_ON_COMPARE;

					#endif

			#endif

			#elif (PWM_H_11_OUTPUT_TYPE==PWM_PHASE_CORRECT)

			   TIMER0_CNTRL_REG=TIMER0_CNTRL_REG_PHASE_PWM_MODE_VALUE;
			   TIMER0_COMPARE_REG=155u;

			   #if   (PWM_H_11_OUTPUT_SHAPE==CLEAR_ON_COMPARE)

				   TIMER0_CNTRL_REG|=TIMER0_CNTRL_REG_PHASE_PWM_MODE_VALUE|TIMER0_CNTRL_REG_CLEAR_OUTPUT_ON_COMPARE|PWM_H_11_FREQUENCY;

			   #elif (PWM_H_11_OUTPUT_SHAPE==SET_ON_COMPARE)

				   TIMER0_CNTRL_REG|=TIMER0_CNTRL_REG_PHASE_PWM_MODE_VALUE|TIMER0_CNTRL_REG_SET_OUTPUT_ON_COMPARE|PWM_H_11_FREQUENCY;

			   #endif


	        #endif

		#endif

		#if (PWM_H_29==ACTIVATE)

			DIO_Init_Pin(29,OUTPUT,DIO_PIN_OUTPUT);

			#if (PWM_H_29_OUTPUT_TYPE==PWM_FAST)

					TIMER1_CNTRL_REG_A=TIMER1_CNTRL_REG_A_FAST_PWM_MODE_VALUE;
					TIMER1_CNTRL_REG_B=TIMER1_CNTRL_REG_B_FAST_PWM_MODE_VALUE;

					#if   (PWM_H_29_DUTY_CYCLE==100u)

						DIO_Write_Pin(29,HIGH);
						TIMER1_CNTRL_REG_B|=PWM_H_29_FREQUENCY;


					#elif (PWM_H_29_DUTY_CYCLE==0u)

						DIO_Write_Pin(29,LOW);
						TIMER1_CNTRL_REG_B|=PWM_H_29_FREQUENCY;

					#else

						TIMER1_COMP_REG_A=((PWM_H_29_DUTY_CYCLE*255u))/100u;

						#if  (PWM_H_29_OUTPUT_SHAPE==CLEAR_ON_COMPARE)

								TIMER1_CNTRL_REG_A|=TIMER1_CNTRL_REG_A_CLEAR_OUTPUT_ON_COMPARE;
								TIMER1_CNTRL_REG_B|=PWM_H_29_FREQUENCY;

						#elif (PWM_H_29_OUTPUT_SHAPE==SET_ON_COMPARE)

								TIMER1_CNTRL_REG_A|=TIMER1_CNTRL_REG_A_SET_OUTPUT_ON_COMPARE;
								TIMER1_CNTRL_REG_B|=PWM_H_29_FREQUENCY;

						#endif
	                    TIMER1_COMP_REG_A=((PWM_H_11_DUTY_CYCLE*255u))/100u;


					#endif

			#elif (PWM_H_29_OUTPUT_TYPE==PWM_PHASE_CORRECT)

	        #endif

		#endif

		#if (PWM_H_31==ACTIVATE)

			DIO_Init_Pin(31,OUTPUT,DIO_PIN_OUTPUT);

			#if (PWM_H_31_OUTPUT_TYPE==PWM_FAST)

					TIMER2_CNTRL_REG=TIMER2_CNTRL_REG_FAST_PWM_MODE_VALUE;

					#if   (PWM_H_31_DUTY_CYCLE==100u)

						DIO_Write_Pin(31,HIGH);
                        TIMER2_CNTRL_REG|=PWM_H_31_FREQUENCY;


					#elif (PWM_H_31_DUTY_CYCLE==0u)

						DIO_Write_Pin(31,LOW);
						TIMER2_CNTRL_REG|=PWM_H_31_FREQUENCY;

					#else

 						#if   (PWM_H_31_OUTPUT_SHAPE==CLEAR_ON_COMPARE)

 						TIMER2_CNTRL_REG|=PWM_H_31_FREQUENCY|TIMER2_CNTRL_REG_CLEAR_OUTPUT_ON_COMPARE;

 						#elif (PWM_H_31_OUTPUT_SHAPE==SET_ON_COMPARE)

 						TIMER2_CNTRL_REG|=PWM_H_31_FREQUENCY|TIMER2_CNTRL_REG_SET_OUTPUT_ON_COMPARE;

 						#endif

						TIMER2_COMPARE_REG=((PWM_H_31_DUTY_CYCLE*255u))/100u;

			       #endif

			#elif (PWM_H_31_OUTPUT_TYPE==PWM_PHASE_CORRECT)

            #endif

		#endif
}



void PWM_HARDWARE_CHANNEL(uinteg8_t u8_Channel,uinteg8_t u8_Percentage)
{
	#if (PWM_H_11==ACTIVATE)

	if(u8_Channel==PWM_CHANNEL_11)
	{
		if(u8_Percentage==0u)
		{
			TIMER0_CNTRL_REG&=~TIMER0_CNTRL_REG_CLEAR_OUTPUT_ON_COMPARE;
			clearBit(PORTB,3);
		}
		else if(u8_Percentage==100u)
		{
			TIMER0_CNTRL_REG&=~TIMER0_CNTRL_REG_CLEAR_OUTPUT_ON_COMPARE;
			SET_BIT(PORTB,3);
		}
		else
		{
			TIMER0_CNTRL_REG|=TIMER0_CNTRL_REG_CLEAR_OUTPUT_ON_COMPARE;
			TIMER0_COMPARE_REG=((u8_Percentage*255u))/100u;
		}

	}
	#endif

	#if (PWM_H_29==ACTIVATE)

	if(u8_Channel==PWM_CHANNEL_29)
	{
		if(u8_Percentage==0u)
		{
			TIMER1_CNTRL_REG_A&=~TIMER1_CNTRL_REG_A_CLEAR_OUTPUT_ON_COMPARE;
			DIO_Write_Pin(29,LOW);
		}
		else if(u8_Percentage==100u)
		{
			TIMER1_CNTRL_REG_A&=~TIMER1_CNTRL_REG_A_CLEAR_OUTPUT_ON_COMPARE;
			DIO_Write_Pin(29,HIGH);
		}
		else
		{
			TIMER1_CNTRL_REG_A|=TIMER1_CNTRL_REG_A_CLEAR_OUTPUT_ON_COMPARE;
			TIMER1_COMP_REG_A=((u8_Percentage*255u))/100u;
		}
	}


	#endif

	#if (PWM_H_31==ACTIVATE)

	if(u8_Channel==PWM_CHANNEL_31)
	{
		if(u8_Percentage==0u)
		{
			TIMER2_CNTRL_REG&=~TIMER2_CNTRL_REG_CLEAR_OUTPUT_ON_COMPARE;
			clearBit(PORTD,7);
		}
		else if(u8_Percentage==100u)
		{
			TIMER2_CNTRL_REG&=~TIMER2_CNTRL_REG_CLEAR_OUTPUT_ON_COMPARE;
			SET_BIT(PORTD,7);
		}
		else
		{
			TIMER2_CNTRL_REG|=TIMER2_CNTRL_REG_CLEAR_OUTPUT_ON_COMPARE;
			TIMER2_COMPARE_REG=((u8_Percentage*255u))/100u;
		}
	}

	#endif
}
void PWM_Set_Duty_Cycle(uinteg8_t u8_Channel,uinteg8_t u8_Percentage)
{
	if (u8_Channel==PWM_CHANNEL_11)
	TIMER0_COMPARE_REG=((u8_Percentage*255u))/100u;
	else if(u8_Channel==PWM_CHANNEL_31)
	TIMER2_COMPARE_REG=((u8_Percentage*255u))/100u;
	else
	TIMER1_COMP_REG_A=((u8_Percentage*255u))/100u;

}
void PWM_Set_Compare_Reg_Value(uinteg8_t u8_Channel,uinteg8_t COMP_REG_VALUE )
{

	if (u8_Channel==PWM_CHANNEL_11)
	{
	   TIMER0_CNTRL_REG|=TIMER2_CNTRL_REG_CLEAR_OUTPUT_ON_COMPARE;
	   TIMER0_COMPARE_REG= (uinteg8_t) COMP_REG_VALUE;
	}
	else if(u8_Channel==PWM_CHANNEL_31)
	{
	  TIMER2_CNTRL_REG|=TIMER2_CNTRL_REG_CLEAR_OUTPUT_ON_COMPARE;
	  TIMER2_COMPARE_REG=(uinteg8_t) COMP_REG_VALUE;
	}
	else
	{
	  TIMER1_CNTRL_REG_A|=TIMER2_CNTRL_REG_CLEAR_OUTPUT_ON_COMPARE;
	  TIMER1_COMP_REG_A=(uinteg8_t) COMP_REG_VALUE;
	}
}




#endif
