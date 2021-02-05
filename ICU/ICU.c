/*
 * ICU.c
 *
 * Created: 2/3/2021 1:44:17 AM
 *  Author: Mohamed Salah Taman
 */

#include "ICU.h"

 static uinteg64_t a=0,b=0,c=0,high=0,period=0;
	
void Icu_Init(void)
{
	/* Turn ON pull-up resistor */
	SET_BIT(PORTD,PD6);
	TCCR1A=0;
}
void Icu_Capture_Signal(void)
{
	TCNT1=0;
	TIFR = (1<<ICF1);  	/* Clear ICF (Input Capture flag) flag */

	TCCR1B = 0x41;  	/* Rising edge, no prescaler */
	while ((TIFR&(1<<ICF1)) == 0);
	a = ICR1;  		/* Take value of capture register */
	TIFR = (1<<ICF1);  	/* Clear ICF flag */
	
	TCCR1B = 0x01;  	/* Falling edge, no prescaler */
	while ((TIFR&(1<<ICF1)) == 0);
	b = ICR1;  		/* Take value of capture register */
	TIFR = (1<<ICF1);  	/* Clear ICF flag */
	
	TCCR1B = 0x41;  	/* Rising edge, no prescaler */
	while ((TIFR&(1<<ICF1)) == 0);
	c = ICR1;  		/* Take value of capture register */
	TIFR = (1<<ICF1);  	/* Clear ICF flag */

	TCCR1B = 0;  		/* Stop the timer */

}
uinteg64_t Icu_Signal_Period(void)
{
	/* Check for valid condition, to avoid timer overflow reading */
	if(a<b && b<c)
	{
		period=0;
		period=c-a;
		return period;
			
	}
	else
	return 0;
}
uinteg64_t Icu_Signal_Frequ(void)
{
	uinteg64_t freq=0;
	if(a<b && b<c)
	{
		Icu_Signal_Period();
		/* Calculate frequency */
		freq=F_CPU/period;
		return freq;
	}
	else 
	return 0;
}
float32_t Icu_Signal_Duty(void)
{
	high=0;
	if(a<b && b<c)
	{
		high=b-a;
		Icu_Signal_Period();
		float32_t duty_cycle =((float) high /(float)period)*100;
		return duty_cycle;
	}
	else
	return 0.0;
}