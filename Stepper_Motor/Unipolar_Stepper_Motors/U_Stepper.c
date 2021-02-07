/*
 * Stepper.c
 *
 * Created: 12/15/2020 6:23:48 PM
 *  Author: Mohamed
  
 * Simple stepper motor (28BYJ-48) controller.
 * Key features:
 * -> move on one step,
 * -> set direction,
 * -> 4096 steps per revolution,
 * -> 0.087890625° per step,
 * -> frequency 100Hz.
*/
#include "U_Stepper.h"

static uint8_t _seq=0;
static uint8_t _dir=0;



/* Set direction (1 - clock wise, 0 - counter clock wise) */
 void stepper_dir(uint8_t dir)
{
	_dir = !!(dir);
}
/* Set _Nibble_Postion (LOW_NIBBLE, HIGH_NIBBLE) */
 void stepper_init(uint8_t _Nibble_Postion)
{
    /* set step motor pins as OUTPUT */
	if(_Nibble_Postion==HIGH_NIBBLE)
	 STEPPER_PORT_DIRECTION =0xf0;
    else
	 STEPPER_PORT_DIRECTION =0x0f;
}
 void stepper_move(void)
{
	_seq = (_seq + (_dir?1:-1)) & 7;

	switch (_seq) {
		/* Pattern for 8 microsteps: A-AB-B-BC-C-CD-D-DA */
		/*      [   A   ][   B  ][   C   ][   D   ] */
		case 0: SET_BIT(STEPPER_PORT,IN1);clearBit(STEPPER_PORT,IN2);clearBit(STEPPER_PORT,IN3);clearBit(STEPPER_PORT,IN4);break;
		case 1: SET_BIT(STEPPER_PORT,IN1);SET_BIT(STEPPER_PORT,IN2);clearBit(STEPPER_PORT,IN3);clearBit(STEPPER_PORT,IN4);break;
		case 2: clearBit(STEPPER_PORT,IN1);SET_BIT(STEPPER_PORT,IN2);clearBit(STEPPER_PORT,IN3);clearBit(STEPPER_PORT,IN4);break;
		case 3: clearBit(STEPPER_PORT,IN1);SET_BIT(STEPPER_PORT,IN2);SET_BIT(STEPPER_PORT,IN3);clearBit(STEPPER_PORT,IN4);break;
		case 4: clearBit(STEPPER_PORT,IN1);clearBit(STEPPER_PORT,IN2);clearBit(STEPPER_PORT,IN3);clearBit(STEPPER_PORT,IN4);break;
		case 5: clearBit(STEPPER_PORT,IN1);clearBit(STEPPER_PORT,IN2);SET_BIT(STEPPER_PORT,IN3);SET_BIT(STEPPER_PORT,IN4);break;
		case 6: clearBit(STEPPER_PORT,IN1);clearBit(STEPPER_PORT,IN2);clearBit(STEPPER_PORT,IN3);SET_BIT(STEPPER_PORT,IN4);break;
		case 7: SET_BIT(STEPPER_PORT,IN1);clearBit(STEPPER_PORT,IN2);clearBit(STEPPER_PORT,IN3);SET_BIT(STEPPER_PORT,IN4);break;
	}

	_delay_ms(MOTOR_SPEED); // 100Hz
}
void Stepper_Intial_Position(void)
{
	SET_BIT(STEPPER_PORT,IN1);clearBit(STEPPER_PORT,IN2);clearBit(STEPPER_PORT,IN3);SET_BIT(STEPPER_PORT,IN4);
}
