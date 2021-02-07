/*
 * Stepper_User.h
 * Created: 7/2/2021 6:23:48 PM
 *  Author: Mohamed Salah Taman
 
 * * Simple stepper motor (Nima17) controller.
 * Key features:
 * -> move on one step,
 * -> set direction,
 * -> 200 steps per revolution,
 * -> 1.8° per step,
 * -> frequency 100Hz.
 */

#ifndef STEPPER_USER_H_
#define STEPPER_USER_H_


#define STEPPER_PORT              PORTA   /*Stepper Port*/
#define STEPPER_PORT_DIRECTION    DDRA    /*stepper port direction*/
#define MOTOR_SPEED  10                   /*100Hz since (1/10m=100HZ)*/
/*Set O/P PINS Connected to A4988 bipolar stepper motor driver */
#define DIRECTION_PIN	PA0
#define STEP_PIN		PA1
#define STEPP_ANGLE		1.8
/* angle */


#endif /* STEPPER_USER_H_ */