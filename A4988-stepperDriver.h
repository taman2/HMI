/*_______________________________________________________________________________

A4988-stepperDriver v1.0

Copyright (c) 2017 Istrate Liviu

NOTICE
--------------------------------------------------------------------
Free for private, non-commercial use

AUTHOR: Istrate Liviu
CONTACT: istrateliviu24@yahoo.com
__________________________________________________________________________________*/
// Uncomment MATH_LIB = -lm in your MAKE file for the compiler to use the math lib from libc not libm.
// The one from libc in about three times larger.

#ifndef A4988_STEPPER_DRIVER_H
#define A4988_STEPPER_DRIVER_H

/*************************************************************
	INCLUDES
**************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



/*************************************************************
	SETUP FOR USER
**************************************************************/
///////////////////    DIGITAL CONTROL PINS SETUP
/* Step Pin */
#define STEP_DDR				DDRD
#define STEP_PORT				PORTD
#define STEP_PIN				PD0

/* Direction Pin (Optional) */
#define USE_DIRECTION_PIN		1
#define DIR_DDR					DDRD
#define DIR_PORT				PORTD
#define DIR_PIN					PD1

/* Enable Pin (Optional) */
#define USE_ENABLE_PIN			1
#define ENABLE_DDR				DDRD
#define ENABLE_PORT				PORTD
#define ENABLE_PIN				PD6

/* Sleep Pin (Optional) */
#define USE_SLEEP_PIN			1
#define SLEEP_DDR				DDRB
#define SLEEP_PORT				PORTB
#define SLEEP_PIN				PB2

/* Reset Pin (Optional) */
#define USE_RESET_PIN			1
#define RESET_DDR				DDRC
#define RESET_PORT				PORTC
#define RESET_PIN				PC5

/* Microstepping Resolution Pins (Optional) */
#define USE_MICROSTEPPING			1
// If total duration of spinning doesn't matter, set this to 0. This will allow using smaller delays between steps
// at a higher microstepping resolution.
#define MICROSTEPPING_DIVIDE_TIME	1
#define MS1_DDR						DDRD
#define MS1_PORT					PORTD
#define MS1_PIN						PD2

#define MS2_DDR						DDRD
#define MS2_PORT					PORTD
#define MS2_PIN						PD3

#define MS3_DDR						DDRD
#define MS3_PORT					PORTD
#define MS3_PIN						PD4

///////////////////    SELECT THE TIMER (put 1 to the one you want to use and 0 to the rest)
#define USE_TIMER0					0
#define USE_TIMER1					1

///////////////////    ACTIVATE/DEACTIVATE FANCY FUNCTIONS (to save space)
#define USE_stepperRotateToDegree	0 // disable acceleration when setting this to 1 or the motor will be slow
#define IMPROVE_TIME_PRECISION		1

///////////////////    STEPPER MOTOR TYPE SETUP
#define STEPPER_DEGREES			1.8

///////////////////    MICROSTEPPING TIME THRESHOLD
#define FULL_STEP_THRESHOLD			200 	// in microseconds
#define HALF_STEP_THRESHOLD			500  	// (1/2) microseconds
#define QUARTER_STEP_THRESHOLD		800  	// (1/4) microseconds
#define EIGHTH_STEP_THRESHOLD		10000  	// (1/8) microseconds
#define SIXTEENTH_STEP_THRESHOLD	1000000	// (1/16) microseconds

///////////////////    ACCELERATION, DECELERATION (from 0 to 100 percents)
#define USE_ACCELERATION				1
#define ACCELERATION					20 // acceleration and deceleration should add up to maximum 100
#define DECELERATION					20 // 
#define ACCELERATION_STARTING_SPEED		8000 // in microseconds

///////////////////		IF TRUE THE MOTOR WILL SPIN ENDLESSLY (or until you stop it)
#define PERPETUAL_MOTION				0



/*************************************************************
	MACROS
**************************************************************/
/* STEPPER DIRECTION */
#define TURN_RIGHT					1 // turn clockwise
#define TURN_LEFT					0 // turn counter-clockwise

/* ENABLE Pin */
// This input turns on or off all of the FET outputs.
// The translator inputs STEP, DIR, and MSx, as well as the internal sequencing logic,
// all remain active, independent of the ENABLE input state. Disable when the load doesn't need the holding torque.
#define A4988_stepperEnable()		(ENABLE_PORT &= ~(1 << ENABLE_PIN))
#define A4988_stepperDisable()		(ENABLE_PORT |= (1 << ENABLE_PIN))

/* SLEEP Pin */
// To minimize power consumption when the motor is not in use, this input disables much of the
// internal circuitry including the output FETs, current regulator, and charge pump.
// When emerging from Sleep mode, in order to allow the charge pump to stabilize, provide a delay of 1 ms
// before issuing a Step command. Sleep during long delays, wake up time is 1ms.
#define A4988_stepperSleep()		(SLEEP_PORT &= ~(1 << SLEEP_PIN))
#define A4988_stepperWakeUp(){\
	SLEEP_PORT |= (1 << SLEEP_PIN);\
	_delay_ms(1);\
}

/* RESET Pin */
// The RESET input sets the translator to a predefined Home state, and turns off all of the FET outputs.
// All STEP inputs are ignored until the RESET input is set to high.
#define A4988_stepperReset(){\
	RESET_PORT &= ~(1 << RESET_PIN);\
	_delay_ms(1);\
	RESET_PORT |= (1 << RESET_PIN);\
}

/* OTHER PARAMETERS */
#define STEPS_PER_REVOLUTION			360 / STEPPER_DEGREES
// Calculate timer 0 TOP value for 10 microseconds resolution
#define FIXED_PRESCALER					1
#define TIMER0_RESOLUTION				10 // microseconds
#define TIMER1_RESOLUTION				10 // microseconds
#if USE_TIMER0 == 1
	#define OCR0A_TIMER0_TOP				(F_CPU / (FIXED_PRESCALER * (1.0 / (TIMER0_RESOLUTION / 1000000.0)))) - 1 // (TIMER0_RESOLUTION / 1000000) converts us to s
#endif
#if USE_TIMER1 == 1
	#define OCR1A_TIMER1_TOP				(F_CPU / (FIXED_PRESCALER * (1.0 / (TIMER1_RESOLUTION / 1000000.0)))) - 1 // (TIMER0_RESOLUTION / 1000000) converts us to s
#endif



/*************************************************************
	GLOBAL VARIABLES
**************************************************************/
static volatile uint16_t ticksPassed = 0;
static volatile uint16_t ticksPerPulse = 0;
static volatile uint16_t numberOfPulsesMade = 0;
static volatile uint32_t numberOfPulsesNecessary = 0;
static volatile uint8_t microTime = 0;
static uint8_t useMicrosteppingGlobalVar = 1;
#if USE_stepperRotateToDegree == 1
float currentDegreePosition = 0;
#endif
#if USE_ACCELERATION == 1
static volatile uint8_t useAcceleration = 1;
static volatile uint16_t stepsToAccelerate = 0;
static volatile uint16_t stepsToDecelerate = 0;
static volatile uint16_t decelerationStep = 0;
static volatile float accelerationPerStep = 0;
static volatile float decelerationPerStep = 0;
static volatile float accelerationPerStepInteger = 0;
static volatile float decelerationPerStepInteger = 0;
#endif
#if IMPROVE_TIME_PRECISION == 1 && USE_ACCELERATION == 0
static volatile uint8_t pulsesAfterTickIsAdded = 0;
static volatile uint8_t countCorrectionPulses = 0;
static volatile uint32_t ticksPerPulseBuffer = 0;
static volatile uint8_t correctionNeeded = 1;
#endif
static volatile uint8_t sregSave;



/*************************************************************
	FUNCTION PROTOTYPES
**************************************************************/
uint8_t A4988_isNotBusy(void);
void A4988_isBusy(void);
void A4988_stepperSetup(void);
void A4988_stepMicroseconds(uint16_t nr_of_steps, uint16_t delay_between_steps_us);
void A4988_stepMilliseconds(uint16_t nr_of_steps, uint32_t delay_between_steps_ms);
#if USE_DIRECTION_PIN == 1
void A4988_stepperDirection(uint8_t direction);
#endif
void A4988_stepperRotateNTimes(uint16_t nr_of_rotations, uint16_t total_duration_ms);
#if USE_stepperRotateToDegree == 1
void A4988_stepperRotateToDegree(float degree, uint16_t delay_between_steps_us);
#endif
void A4988_stepperStop(void);
#if PERPETUAL_MOTION == 1
void A4988_stepperIncreaseSpeed(uint8_t speed);
void A4988_stepperDecreaseSpeed(uint8_t speed);
#endif



/*************************************************************
	FUNCTIONS
**************************************************************/
///////////////////    PUBLIC

void A4988_stepperSetup(){
	// Wait 1 ms for the pump to charge
	_delay_ms(1);
	
	/* I/O Setup */
	STEP_DDR |= 1 << STEP_PIN;
	STEP_PORT &= ~(1 << STEP_PIN);
	
	#if USE_DIRECTION_PIN == 1
	DIR_DDR |= 1 << DIR_DDR;
	#endif
	
	#if USE_ENABLE_PIN == 1
	ENABLE_DDR |= 1 << ENABLE_PIN;
	ENABLE_PORT &= ~(1 << ENABLE_PIN);
	#endif
	
	#if USE_SLEEP_PIN == 1
	SLEEP_DDR |= 1 << SLEEP_PIN;
	SLEEP_PORT |= (1 << SLEEP_PIN);
	#endif
	
	#if USE_RESET_PIN == 1
	RESET_DDR |= 1 << RESET_PIN;
	RESET_PORT |= (1 << RESET_PIN);
	A4988_stepperReset();
	#endif
	
	#if USE_MICROSTEPPING == 1
	MS1_DDR |= 1 << MS1_PIN;
	MS2_DDR |= 1 << MS2_PIN;
	MS3_DDR |= 1 << MS3_PIN;
	#endif
	
	/* Timer Interrupt Setup */
	#if USE_TIMER0 == 1
		// Timer0 in Fast PWM mode, OCR0A as TOP
		TCCR0A 	|= (1 << WGM01) | (1 << WGM00);
		TCCR0B 	|= (1 << WGM02);
		// Set the ISR COMPA vect - TIMER0_COMPA_vect
		TIMSK0 |= (1 << OCIE0A);
	#endif
	
	#if USE_TIMER1 == 1
		// Timer1 in Fast PWM mode, OCR1A as TOP
		TCCR1A |= (1 << WGM10) | (1 << WGM11);
		TCCR1B |= (1 << WGM12) | (1 << WGM13);
		// Set the ISR COMPA vect - TIMER1_COMPA_vect
		TIMSK1 |= (1 << OCIE1A);
	#endif
}

void A4988_isBusy(void){
	while(numberOfPulsesNecessary);
}

uint8_t A4988_isNotBusy(void){
	if(numberOfPulsesNecessary == 0) return 1; // is ready
	else return 0; // is not
}

void A4988_stepperStop(void){
	// Stop timer
	#if USE_TIMER0 == 1
		TCCR0B &= ~((1 << CS02) |  (1 << CS01) | (1 << CS00));
		
		// Clear timer
		TCNT0 = 0;
	#endif
	#if USE_TIMER1 == 1
		TCCR1B &= ~((1 << CS12) |  (1 << CS11) | (1 << CS10));
		
		// Clear timer
		TCNT1 = 0;
	#endif
	
	// Leave STEP pin LOW
	STEP_PORT &= ~(1 << STEP_PIN);
	
	// Restore SREG (Status Register)
	SREG = sregSave;
	
	// Reset some global variables
	ticksPassed = 0;
	numberOfPulsesNecessary = 0;
	numberOfPulsesMade = 0;
	#if USE_ACCELERATION == 1
	useAcceleration = 1;
	#endif
}

#if PERPETUAL_MOTION == 1
void A4988_stepperDecreaseSpeed(uint8_t speed){
	ticksPerPulse += speed;
}

void A4988_stepperIncreaseSpeed(uint8_t speed){
	int16_t newTicksPerPulseValue = ticksPerPulse - speed;
	
	if(newTicksPerPulseValue > 0){
		ticksPerPulse = newTicksPerPulseValue;
	}else{
		ticksPerPulse = 1;
	}
}
#endif

void A4988_stepMicroseconds(uint16_t nr_of_steps, uint16_t delay_between_steps_us){
	microTime = 1;
	A4988_stepMilliseconds(nr_of_steps, delay_between_steps_us);
}

void A4988_stepMilliseconds(uint16_t nr_of_steps, uint32_t delay_between_steps_ms){
	if(nr_of_steps > 0){
		/* Local variables */
		float halfCycleDelay;
		
		/* The function can receive ms or us values so we check the microTime flag
		to convert to microseconds if is necessary */
		
		#if USE_ACCELERATION == 1
			// Save desired speed in buffer
			uint32_t cruising_speed = delay_between_steps_ms;
			
			// Convert milliseconds to microseconds if it is the case
			if(microTime == 0){
				cruising_speed *= 1000;
			}
			
			// Set new speed to a lower predefined speed only if the cruising speed is greater.
			// There is no need for acceleration if the speed is slow.
			if(cruising_speed >= ACCELERATION_STARTING_SPEED){
				useAcceleration = 0;
			}else{
				delay_between_steps_ms = ACCELERATION_STARTING_SPEED;
				
				// Set microTime to true because ACCELERATION_STARTING_SPEED is in microseconds
				microTime = 1;
			}
			
			float halfCycleDelay_cruising = cruising_speed / 2.0;
		#endif
		
		// Convert milliseconds to microseconds if it is the case
		if(microTime == 0){
			delay_between_steps_ms *= 1000;
		}
		
		// Divide the delay between steps by 2 to double the speed because the ISR needs to trigger 2 times for 1 step
		halfCycleDelay = delay_between_steps_ms / 2.0;
		
		// Set the number of ticks for the ISR. Multiply by 2 because for one step is necessary a low
		// pulse and a high pulse
		numberOfPulsesNecessary = nr_of_steps * 2;
		
		/* Set microstepping */
		#if USE_MICROSTEPPING == 1
		if(useMicrosteppingGlobalVar){
			if(delay_between_steps_ms < FULL_STEP_THRESHOLD){
				// Full Step
				MS1_PORT &= ~(1 << MS1_PIN);
				MS2_PORT &= ~(1 << MS2_PIN);
				MS3_PORT &= ~(1 << MS3_PIN);
			}else if(delay_between_steps_ms < HALF_STEP_THRESHOLD){
				// 1/2 Step
				MS1_PORT |= (1 << MS1_PIN);
				MS2_PORT &= ~(1 << MS2_PIN);
				MS3_PORT &= ~(1 << MS3_PIN);
				
				numberOfPulsesNecessary = nr_of_steps * 2 * 2;
				
				#if MICROSTEPPING_DIVIDE_TIME == 1
					halfCycleDelay /= 2;
					
					#if USE_ACCELERATION == 1
						halfCycleDelay_cruising /= 2;
					#endif
				#endif
			}else if(delay_between_steps_ms < QUARTER_STEP_THRESHOLD){
				// 1/4 Step
				MS1_PORT &= ~(1 << MS1_PIN);
				MS2_PORT |= (1 << MS2_PIN);
				MS3_PORT &= ~(1 << MS3_PIN);
				
				numberOfPulsesNecessary = nr_of_steps * 2 * 4;
				
				#if MICROSTEPPING_DIVIDE_TIME == 1
					halfCycleDelay /= 4;
					
					#if USE_ACCELERATION == 1
						halfCycleDelay_cruising /= 4;
					#endif
				#endif
			}else if(delay_between_steps_ms < EIGHTH_STEP_THRESHOLD){
				// 1/8 Step
				MS1_PORT |= (1 << MS1_PIN);
				MS2_PORT |= (1 << MS2_PIN);
				MS3_PORT &= ~(1 << MS3_PIN);
				
				numberOfPulsesNecessary = nr_of_steps * 2 * 8;
				
				#if MICROSTEPPING_DIVIDE_TIME == 1
					halfCycleDelay /= 8;
					
					#if USE_ACCELERATION == 1
						halfCycleDelay_cruising /= 8;
					#endif
				#endif
			}else if(delay_between_steps_ms < SIXTEENTH_STEP_THRESHOLD){
				// 1/16 Step
				MS1_PORT |= (1 << MS1_PIN);
				MS2_PORT |= (1 << MS2_PIN);
				MS3_PORT |= (1 << MS3_PIN);
				
				numberOfPulsesNecessary = nr_of_steps * 2 * 16;
				
				#if MICROSTEPPING_DIVIDE_TIME == 1
					halfCycleDelay /= 16;
					
					#if USE_ACCELERATION == 1
						halfCycleDelay_cruising /= 16;
					#endif
				#endif
			}
			
		}else{
			#if USE_stepperRotateToDegree == 1
			if(useMicrosteppingGlobalVar == 0){
				// 1/16 Step
				MS1_PORT |= (1 << MS1_PIN);
				MS2_PORT |= (1 << MS2_PIN);
				MS3_PORT |= (1 << MS3_PIN);
				
				//halfCycleDelay /= 16;
				
				#if USE_ACCELERATION == 1
					halfCycleDelay_cruising /= 16;
				#endif
			}
			#endif
			
			// Reset the flag
			useMicrosteppingGlobalVar = 1;
		}
		#endif
		
		
		// Reset the flag
		if(microTime){
			microTime = 0;
		}
		
		// Save SREG (Status Register) and enable global interrupts
		sregSave = SREG;
		sei();
		
		#if USE_TIMER0 == 1
			// TOP value for Timer0
			OCR0A = OCR0A_TIMER0_TOP;
		#endif
		#if USE_TIMER1 == 1
			// TOP value for Timer1
			OCR1A = OCR1A_TIMER1_TOP;
		#endif
		
		// Calculate how many times the ISR must trigger to reach the desired time based on current timer resolution
		#if USE_TIMER0 == 1
		float ticksPerPulse_buffer = halfCycleDelay / TIMER0_RESOLUTION;
		#endif
		#if USE_TIMER1 == 1
		float ticksPerPulse_buffer = halfCycleDelay / TIMER1_RESOLUTION;
		#endif
		ticksPerPulse = ticksPerPulse_buffer;
		
		#if IMPROVE_TIME_PRECISION == 1 && USE_ACCELERATION == 0
		// ticksPerPulse_buffer (float) - ticksPerPulse (integer) e.g. 6.25 - 6 = 0.25
		// This is used to account for conversion from float to integer and added to ticksPerPulse
		float ticksPerPulse_diff = ticksPerPulse_buffer - ticksPerPulse;
		if(ticksPerPulse_diff == 0){
			correctionNeeded = 0;
		}else{
			pulsesAfterTickIsAdded = 1 / ticksPerPulse_diff;
			correctionNeeded = 1;
		}
		ticksPerPulseBuffer = ticksPerPulse;
		#endif
		
		// Acceleration, deceleration
		#if USE_ACCELERATION == 1
		if(useAcceleration){
			// Same as ticksPerPulse but used for cruising speed
			uint16_t ticks_per_pulse_cruising = halfCycleDelay_cruising / TIMER0_RESOLUTION;
			
			// Difference in time (ticks) between the acceleration speed and the cruising speed
			// The acceleration speed is used for the deceleration speed as well
			float start_end_diff = ticksPerPulse - ticks_per_pulse_cruising;
			
			// How many steps are used to accelerate/decelerate based on a percentage set by the user
			stepsToAccelerate = (numberOfPulsesNecessary * ACCELERATION) / 100;
			stepsToDecelerate = (numberOfPulsesNecessary * DECELERATION) / 100;
			
			// How much to accelerate/decelerate per step based on the number of steps
			accelerationPerStep = start_end_diff / stepsToAccelerate;
			decelerationPerStep = start_end_diff / stepsToDecelerate;
			
			// accelerationPerStep/decelerationPerStep may be less than 1 so accelerationPerStepInteger/decelerationPerStepInteger
			// are used by the ISR to sum the floats to 1
			accelerationPerStepInteger = accelerationPerStep;
			decelerationPerStepInteger = decelerationPerStep;
			
			// The step number after the cruising ends and deceleration starts
			decelerationStep = numberOfPulsesNecessary - stepsToDecelerate;
		}
		#endif
		
		// Set the prescaler and start Timer
		#if FIXED_PRESCALER == 1
			#if USE_TIMER0 == 1
				// Set prescaler to 1 and start the timer
				TCCR0B |= (1 << CS00);
			#endif
			#if USE_TIMER1 == 1
				// Set prescaler to 1 and start the timer
				TCCR1B |= (1 << CS10);
			#endif
		#elif FIXED_PRESCALER == 8
			#if USE_TIMER0 == 1
				// Set prescaler to 8 and start the timer
				TCCR0B |= (1 << CS01);
			#endif
			#if USE_TIMER1 == 1
				// Set prescaler to 8 and start the timer
				TCCR1B |= (1 << CS11);
			#endif
		#elif FIXED_PRESCALER == 64
			#if USE_TIMER0 == 1
				// Set prescaler to 64 and start the timer
				TCCR0B |= (1 << CS00) | (1 << CS01);
			#endif
			#if USE_TIMER1 == 1
				// Set prescaler to 64 and start the timer
				TCCR1B |= (1 << CS10) | (1 << CS11);
			#endif
		#elif FIXED_PRESCALER == 256
			#if USE_TIMER0 == 1
				// Set prescaler to 256 and start the timer
				TCCR0B |= (1 << CS02);
			#endif
			#if USE_TIMER1 == 1
				// Set prescaler to 256 and start the timer
				TCCR1B |= (1 << CS12);
			#endif
		#elif FIXED_PRESCALER == 1024
			#if USE_TIMER0 == 1
				// Set prescaler to 1024 and start the timer
				TCCR0B |= (1 << CS00) | (1 << CS02);
			#endif
			#if USE_TIMER1 == 1
				// Set prescaler to 1024 and start the timer
				TCCR1B |= (1 << CS10) | (1 << CS12);
			#endif
		#endif
	}
}

#if USE_DIRECTION_PIN == 1
void A4988_stepperDirection(uint8_t direction){
	if(direction)
		DIR_PORT |= 1 << DIR_PIN; // turn clockwise
	else
		DIR_PORT &= ~(1 << DIR_PIN); // turn counter-clockwise
}
#endif

void A4988_stepperRotateNTimes(uint16_t nr_of_rotations, uint16_t total_duration_ms){
	uint16_t total_steps = STEPS_PER_REVOLUTION * nr_of_rotations;
	uint32_t millisToMicro = 1000;
	millisToMicro = total_duration_ms * millisToMicro; // convert to us
	millisToMicro = (millisToMicro / total_steps);
	microTime = 1;
	A4988_stepMilliseconds(total_steps, millisToMicro);
}

#if USE_stepperRotateToDegree == 1
void A4988_stepperRotateToDegree(float degree, uint16_t delay_between_steps_us){
	microTime = 1;
	useMicrosteppingGlobalVar = 0;
	#if USE_ACCELERATION == 1
	//useAcceleration = 0;
	#endif
	
	float micro_degree = STEPPER_DEGREES / 16.0;
	int16_t degrees_to_move = degree - currentDegreePosition;
	if(degrees_to_move < 0) degrees_to_move *= -1; // Convert negative number to positive
	uint16_t steps_to_make = degrees_to_move / micro_degree;
	
	// Set direction
	if(degree > currentDegreePosition){
		A4988_stepperDirection(TURN_RIGHT);
	}else{
		A4988_stepperDirection(TURN_LEFT);
	}
	
	currentDegreePosition = degree;
	A4988_stepMilliseconds(steps_to_make, delay_between_steps_us);
}
#endif



/*************************************************************
	INTERRUPTS
**************************************************************/
#if USE_TIMER0 == 1
ISR(TIMER0_COMPA_vect){
#endif
#if USE_TIMER1 == 1
ISR(TIMER1_COMPA_vect){
#endif
	// Half cycle has passed
	if(ticksPassed >= ticksPerPulse){
		STEP_PORT ^= (1 << STEP_PIN);
		
		// Acceleration, deceleration
		#if USE_ACCELERATION == 1
		if(useAcceleration){
			uint16_t new_trigger_time = 0;
			// Accelerate
			if(numberOfPulsesMade < stepsToAccelerate){
				if(accelerationPerStepInteger < 1){
					accelerationPerStepInteger += accelerationPerStep;
				}else{
					new_trigger_time = ticksPerPulse - (uint16_t)accelerationPerStepInteger;
					accelerationPerStepInteger = 0;
					
					if(new_trigger_time > 0){
						ticksPerPulse = new_trigger_time;
					}
				}
			}else{
				#if PERPETUAL_MOTION == 0
				// Decelerate
				if(numberOfPulsesMade > decelerationStep){
					if(decelerationPerStepInteger < 1){
						decelerationPerStepInteger += decelerationPerStep;
					}else{
						ticksPerPulse += (uint16_t)decelerationPerStepInteger;
						decelerationPerStepInteger = 0;
					}
				}
				#else
					// Keep the numberOfPulsesMade = with stepsToAccelerate to prevent further acceleration
					numberOfPulsesMade = stepsToAccelerate;
				#endif
			}
		}
		#else
			#if IMPROVE_TIME_PRECISION == 1
				if(countCorrectionPulses == pulsesAfterTickIsAdded && correctionNeeded){
					ticksPerPulse++;
					countCorrectionPulses = 0;
				}else{
					ticksPerPulse = ticksPerPulseBuffer;
					countCorrectionPulses++;
				}
			#endif
		#endif
		
		numberOfPulsesMade++; // Two of these is one step for the motor
		ticksPassed = 0;
		
		// When the steps have been made, stop the timer interrupt, unless the PERPETUAL_MOTION is activated
		#if PERPETUAL_MOTION == 0
			if(numberOfPulsesMade >= numberOfPulsesNecessary){
				A4988_stepperStop();
			}
		#endif
	}
	
	// Count the number of times the ISR has been triggered
	ticksPassed++;
}

#endif