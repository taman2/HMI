/*
 * Stepper.c
 *
 * Created: 7/2/2021 6:23:48 PM
 *  Author: Mohamed Salah Taman
  
 * Simple stepper motor (Nima17) controller.
 * Key features:
 * -> move on one step,
 * -> set direction,
 * -> 200 steps per revolution,
 * -> 1.8° per step,
 * -> frequency 100Hz.
*/
#include "B_Stepper.h"

static uint8_t _seq=0;
static uint8_t _dir=0;
static float32_t Current_Postion=0.0;


/* Set direction (1 - clock wise, 0 - counter clock wise) */
static void B_Stepper_Dir(uint8_t dir)
{
	if(dir=0)
	clearBit(STEPPER_PORT,DIRECTION_PIN);
	else
	SET_BIT(STEPPER_PORT,DIRECTION_PIN);
	
}
/* Set _Nibble_Postion (LOW_NIBBLE, HIGH_NIBBLE) */
 void B_Stepper_Init(void)
{
	SET_BIT(STEPPER_PORT_DIRECTION,DIRECTION_PIN);
	SET_BIT(STEPPER_PORT_DIRECTION,STEP_PIN);

}
 void B_Stepper_move(float32_t Angel)
{
	uint8_t i=0;
	uinteg16_t Num_OfSteppes=0;
	Num_OfSteppes= Angel/STEPP_ANGLE;
	if(Angel > Current_Postion)
	{
		Num_OfSteppes=(uinteg16_t)((Angel-Current_Postion)/STEPP_ANGLE);
		Current_Postion= Angel;
		B_Stepper_Dir(1);
		for(i=0;i<Num_OfSteppes;i++)
		{
			SET_BIT(STEPPER_PORT,STEP_PIN);
			_delay_ms(MOTOR_SPEED);
			clearBit(STEPPER_PORT,STEP_PIN);
		}	
	}
	else if(Angel < Current_Postion)
	{
		Num_OfSteppes=(uinteg16_t)((Current_Postion-Angel)/STEPP_ANGLE);
		Current_Postion= Angel;
		B_Stepper_Dir(0);
		for(i=0;i<Num_OfSteppes;i++)
		{
			SET_BIT(STEPPER_PORT,STEP_PIN);
			_delay_ms(MOTOR_SPEED);
			clearBit(STEPPER_PORT,STEP_PIN);
		}		
	}
}
