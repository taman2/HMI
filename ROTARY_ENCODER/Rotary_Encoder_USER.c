/*
 * Rotary_Encoder_USER.c
 *
 * Created: 1/1/2021 3:18:28 PM
 *  Author: Mohamed Salah Taman
 *************************************************************************************************
Interrupts based solution (example based on ATmega32)
The  example is the solution based on interrupts, in which we detect a falling and/or rising edge, 
and depending on the current state on the second pin we determine the shaft direction.
1-FULL RESOLTION
 If we connect our A and B encoder outputs to PD2 and PD3 micro-controller pins, we need to set PD2
 and PD3 as inputs:
2-HALF RESOLTION
 The second method is based on detecting falling edge of the output signal, on one of the output,
 and checking the current state on another output.
3-Two parameter that rotary encoder modifies them during its revolution
  U8_Rotary_Incoder_Direction;
  U8_Rotary_Incoder_Counte;
 
4-if  U8_Rotary_Incoder_OK_Flag==1 then rotary encoder push button is pressed, you have  reset this flag 
 by software   U8_Rotary_Incoder_OK_Flag=0; 
 
  note!!!!   note!!!!   note!!!!   note!!!!
   U8_Rotary_Incoder_Direction;
   U8_Rotary_Incoder_Counter;
   U8_Rotary_Incoder_OK_Flag;
   these are volatile extern global variable so you can use them directly without initialization  in your application 
   at main function just you have to #include "Rotary_Encoder_Design.h"
 5- you can use pulling or interrupt mode 
   also Half or Full Resolution by modifying parameters inside ROTARY_ENCODER_PRE_CONFIGRATION struct 
 
*/
#include "Rotary_Encoder_Design.h"
struct ROTARY_Config ROTARY_ENCODER_PRE_CONFIGRATION ={
														  .ROTARY_OPERATION_MODE=INTERRUP_MODE,
														  .ROTARY_RESOLUTION=HALF_RESOLUTION	                             
	
	                                                 };