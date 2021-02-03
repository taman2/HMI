/*
 * ADC_User_Interface.h
 *
 * Created: 06/01/2020 14:44:48
 *  Author: Native_programmer
 */ 

#ifndef ADC_USER_INTERFACE_H_
#define ADC_USER_INTERFACE_H_

/*- INCLUDES -----------------------------------------------*/
#include "ADC_Designer.h"
#include "Data_Types.h"
/*- CONSTANTS ----------------------------------------------*/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*- User_Defined TYPES -------------------------------------*/

/***********************************************************/
/*              Structure for configuration                */
/***********************************************************/
typedef struct
{
 integ32_t ADC_Channel_Choose;
 integ32_t ADC_Reference_Voltage;
 integ32_t ADC_Frequency;
 integ32_t ADC_Auto_Trig_Enable;
 integ32_t ADC_Auto_Trig_Source; 
 integ32_t ADC_Left_Right_Adjustment;
 integ32_t ADC_Execution_Method;
}gstrADC_Config_t;

/*- ENUMS AND DEFINES LIKE ENUMS ---------------------------*/

/****Configuration Defines like enums****/
/************************************************************************/
/*	The successive approximation circuitry requires an input clock 
	frequency between 50kHz and 200 kHz to get maximum resolution. 
	If a lower resolution than 10 bits is needed, the input clock 
	frequency to the ADC can be higher than 200 kHz to get a 
	higher sample rate.(In this case we can take value of ADCL when 
	the left adjustment is disabled as it stores the least significant 
	byte of ADC Data register
	Higher sample rate--->>>Lower resolution                            */                                                
/************************************************************************/
/*ADC_Channel_Choose*/
#define ADC_Channel_0                                                0
#define ADC_Channel_1                                                1
#define ADC_Channel_2                                                2
#define ADC_Channel_3                                                3
#define ADC_Channel_4                                                4
#define ADC_Channel_5                                                5
#define ADC_Channel_6                                                6
#define ADC_Channel_7                                                7
/*ADC_Reference_Voltage*/
#define ADC_Voltage_Refrence_AREF                                    0
#define ADC_Voltage_Refrence_AVCC                                    64
#define ADC_Voltage_Internal                                         192

/*ADC_Frequency*/
#define ADC_Freq_4MHZ                                                0
#define ADC_Freq_2MHZ                                                2
#define ADC_Freq_1MHZ                                                3
#define ADC_Freq_500KHZ											     4
#define ADC_Freq_250KHZ												 5
#define ADC_Freq_125KHZ                                              6
#define ADC_Freq_62500                                               7
/*ADC_Single_or_Double_Ended*/
#define ADC_Single_Ended                                             19
#define ADC_Double_Ended                                             20
/*ADC_Auto_Trigger_Enable*/
#define ADC_Auto_Trigger_Enable                                      21
#define ADC_Auto_Trigger_Disable                                     22
/*ADC_Auto_Trig_Source*/
#define ADC_Auto_Trig_Source_Free_Running_mode_Bits                  0
#define ADC_Auto_Trig_Source_Analog_Comparator_Bits                  32
#define ADC_Auto_Trig_Source_External_Interrupt_Request_0_Bits       64
#define ADC_Auto_Trig_Source_Timer_Counter_0_Compare_Match_Bits      96
#define ADC_Auto_Trig_Source_Timer_Counte_0_Overflow_Bits            128
#define ADC_Auto_Trig_Source_Timer_Counter1_Compare_Match_B_Bits     160
#define ADC_Auto_Trig_Source_Timer_Counter1_Overflow_Bits            192
#define ADC_Auto_Trig_Source_Timer_Counter1_Capture_Event_Bits       224
#define ADC_No_Need_To_Trigger                                       225

/*ADC_Left_Right_Adjust*/
#define ADC_Left_Adjustment                                          32
#define ADC_Right_Adjustment                                         33
/*Execution method */
#define ADC_Executed_By_Interrupt                                    34
#define ADC_Executed_By_Polling                                      35
#define ADC_Executed_By_Time_Driven                                  36
#define ADC_Executed_By_Event_Driven                                 37
#endif /* ADC_USER_INTERFACE_H_ */


/*- APIS Implementation-------------------------------------------*/

/************************************************************************/
/*ADC_INIT-->> This API for initialization the Unit of ADC              */
/************************************************************************/
extern  ADC_Error_t ADC_INIT(gstrADC_Config_t*Copy_PntrStr_ADC_Init_Config);

/***ADC INIT API ERRORS***/
#define ADC_INIT_API_NO_ERROR                                        0
#define ADC_INIT_ERROR_CHANNEL_CHOOSE                                1
#define ADC_INIT_ERROR_VOLTAGE_REFRENCE_CHOOSE                       2
#define ADC_INIT_ERROR_FREQUENCY_CHOOSE                              3
#define ADC_INIT_ERROR_NEITHER_SINGLE_NOR_DOUBLE                     4
#define ADC_INIT_ERROR_NEITHER_TRIGGER_ENABLE_NOR_DISABLE            5
#define ADC_INIT_ERROR_NO_DEFINED_TRIGGER                            6
#define ADC_INIT_ERROR_NEITHER_LEFT_NOR_RIGHT                        7
#define ADC_INIT_ERROR_NEITHER_INTERRUPT_ENABLE_NOR_DISABLE          8
#define ADC_INIT_ERROR_Config_Pointer_Point_To_NULL                  9
#define ADC_INIT_ERROR_NO_DEFINED_EXECUTION_METHOD                   10

/************************************************************************/
/* ADC_READ-->> This API for reading ADC register as a range from 0-1024*/
/************************************************************************/

extern ADC_Error_t ADC_READ(uinteg32_t* Copyu32_ADC_Value);

/**ADC API ERRORS**/
#define ADC_READ_API_NO_ERROR                                       30
#define ADC_READ_ERROR_Due_To_ADC_INIT_ERROR                        31
#define ADC_READ_CALL_BACK_POITNER_IS_NULL                          2