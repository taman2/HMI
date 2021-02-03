/*
 * Stepper_User.h
 * Created: 12/15/2020 6:23:48 PM
 *  Author: Mohamed Salah Taman
 
 * Simple stepper motor (28BYJ-48) controller.
 * Key features:
 * -> move on one step,
 * -> set direction,
 * -> 4096 steps per revolution,
 * -> 0.087890625° per step,
 * -> frequency 100Hz.
 */

#ifndef STEPPER_USER_H_
#define STEPPER_USER_H_


#define STEPPER_PORT              PORTA   /*Stepper Port*/
#define STEPPER_PORT_DIRECTION    DDRA    /*stepper port direction*/
#define MOTOR_SPEED  10                   /*100Hz since (1/10m=100HZ)*/
/*Set O/P PINS Connected to ULN2003 HW driver*/
#define IN1 PA0
#define IN2 PA1
#define IN3 PA2
#define IN4 PA3


#endif /* STEPPER_USER_H_ */