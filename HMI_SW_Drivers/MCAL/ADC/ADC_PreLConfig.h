/*
 * ADC_PreLConfig.h
 *
 * Created: 06/01/2020 20:29:10
 *  Author: Native_programmer
 */

 
#ifndef ADC_PRELCONFIG_H_
#define ADC_PRELCONFIG_H_

#include "AtmegaPort.h"

/*- NickNames for Registers and configuration values--------*/

#define ADC_MUX_SELECT_REG                                            ADMUX
/**Configuration values of ADC_MUX_SELECT_REG**/
/*Reference voltage adjustment*/
                             
#define ADC__Voltage_Refrence_AREF_Bits                               0b00000000
#define ADC__Voltage_Refrence_AVCC_Bits                               0b01000000 /*Hint:Should connect external capacitor at AREF pin*/
#define ADC__Voltage_Internal_Bits                                    0b11000000 /*Hint:Should connect external capacitor at AREF pin*/

/*ADC Left or Right Adjust Result*/
#define ADC__Left_Adjust_Result_Bit                                  0b00100000
#define ADC__Right_Adjust_Result_Bit                                 0b00000000 

/*ADC Choose channel*/
#define ADC__Single_Ended_Channel(N)                                  N 
#define ADC__Single_Ended_Channel_0_Bit                               0
#define ADC__Single_Ended_Channel_1_Bit                               1
#define ADC__Single_Ended_Channel_2_Bit  				              2
#define ADC__Single_Ended_Channel_3_Bit   						      3
#define ADC__Single_Ended_Channel_4_Bit 						      4
#define ADC__Single_Ended_Channel_5_Bit 						      5
#define ADC__Single_Ended_Channel_6_Bit 						      6
#define ADC__Single_Ended_Channel_7_Bit                               7

#define ADC_DATA_LOW_REG                                              ADCL
/**Configuration values of ADC_DATA_LOW_REG**/
#define ADC_DATA_HIGH_REG                                             ADCH
/**Configuration values of ADC_DATA_HIGH_REG**/
#define ADC_CNTRL_STATUS_REG	                                      ADCSRA
/**Configuration values of ADC_CNTRL_STATUS_REG**/
#define ADC_Enable_Bit                                                0b10000000

#define ADC_Start_Conversion_Bit                                      0b01000000

#define ADC_Auto_Trigger_Bit                                          0b00100000

#define ADC_Interrupt_flag_Bit                                        4
/*- FUNCTION-LIKE MACROS -----------------------------------*/

#define ADC_Interrupt_Enable_Bit								      0b00001000

#define ADC_Frequency_4MHZ                                            0b00000000
#define ADC_Frequency_2MHZ                                            0b00000010
#define ADC_Frequency_1MHZ                                            0b00000011
#define ADC_Frequency_500KHZ                                          0b00000100
#define ADC_Frequency_250KHZ                                          0b00000101
#define ADC_Frequency_125KHZ                                          0b00000110
#define ADC_Frequency_62500                                           0b00000111

#define ADC_AUTO_Trigger_SELECT_REG                                   SFIOR
/**Configuration values of ADC_AUTO_Trigger_REG**/
#define ADC_Auto_Trigger_Source__Free_Running_mode_Bits               0b00000000
#define ADC_Auto_Trigger_Source__Analog_Comparator_Bits               0b00100000
#define ADC_Auto_Trigger_Source__External_Interrupt_Request_0_Bits    0b01000000
#define ADC_Auto_Trigger_Source__Timer_Counter_0_Compare_Match_Bits   0b01100000
#define ADC_Auto_Trigger_Source__Timer_Counte_0_Overflow_Bits         0b10000000
#define ADC_Auto_Trigger_Source__Timer_Counter1_Compare_Match_B_Bits  0b10100000
#define ADC_Auto_Trigger_Source__Timer_Counter1_Overflow_Bits         0b11000000
#define ADC_Auto_Trigger_Source__Timer_Counter1_Capture_Event_Bits    0b11100000

/*- ISR Definition------------------------------------------*/

#define ADC_ISR_CODE() \
void __vector_16 (void)__attribute((signal,used)); \
void __vector_16 (void)



#endif /* ADC_PRELCONFIG_H_ */