/*
 * ADC_Designer.h
 *
 * Created: 06/01/2020 14:58:18
 *  Author: Native_programmer
 */ 


#ifndef ADC_DESIGNER_H_
#define ADC_DESIGNER_H_

/*- INCLUDES -----------------------------------------------*/
#include "ADC_PreLConfig.h"
#include "BitManipulation.h"
#include "Data_Types.h"
/*- CONSTANTS ----------------------------------------------*/

/*- ENUMS --------------------------------------------------*/
/*- User_Defined TYPES -------------------------------------*/
/***********************************************************/
/*                  Error data type                        */
/***********************************************************/

typedef uinteg8_t ADC_Error_t;

/*- FUNCTION-LIKE MACROS -----------------------------------*/

#define ADC_Channel_Set(N)                                         RESET_PORT_WITH_VALUE(ADC_CNTRL_STATUS_REG,ADC__Single_Ended_Channel(N) ); \
																   SET_PORT_WITH_VALUE(ADMUX,ADC__Single_Ended_Channel(N) )
#define ADC_Channel_Reset(N)                                       RESET_PORT_WITH_VALUE(ADMUX,ADC__Single_Ended_Channel(N) )

#define ADC_Voltage_Refrence_Set(Voltage_Source)                   RESET_PORT_WITH_VALUE(ADC_CNTRL_STATUS_REG,Voltage_Source); \
																   SET_PORT_WITH_VALUE(ADC_MUX_SELECT_REG,Voltage_Source)
#define ADC_Voltage_Refrence_Reset(Voltage_Source)                 RESET_PORT_WITH_VALUE(ADC_MUX_SELECT_REG,Voltage_Source)

#define ADC_Unit_Enable()                                          RESET_PORT_WITH_VALUE(ADC_CNTRL_STATUS_REG,ADC_Enable_Bit); \
																   SET_PORT_WITH_VALUE(ADC_CNTRL_STATUS_REG,ADC_Enable_Bit)
#define ADC_Unit_Disable()                                         RESET_PORT_WITH_VALUE(ADC_CNTRL_STATUS_REG,ADC_Enable_Bit)

#define ADC_Start_Conversion()	                                   SET_BIT(ADC_CNTRL_STATUS_REG,6)
																   
#define ADC_Auto_Trigger_Set()                                     RESET_PORT_WITH_VALUE(ADC_CNTRL_STATUS_REG,ADC_Auto_Trigger_Bit); \
                                                                   SET_PORT_WITH_VALUE(ADC_CNTRL_STATUS_REG,ADC_Auto_Trigger_Bit)
#define ADC_Auto_Trigger_Reset()                                   RESET_PORT_WITH_VALUE(ADC_CNTRL_STATUS_REG,ADC_Auto_Trigger_Bit)

#define ADC_Auto_Trigger_Source_Set(Trigger_Source)                RESET_PORT_WITH_VALUE(SFIOR,Trigger_Source); \
                                                                   SET_PORT_WITH_VALUE(SFIOR,Trigger_Source)
#define ADC_Auto_Trigger_Source_Reset(Trigger_Source)              RESET_PORT_WITH_VALUE(SFIOR,Trigger_Source)

#define ADC_Data_Left_Adjustment_Set()                             RESET_PORT_WITH_VALUE(ADC_MUX_SELECT_REG,ADC__Left_Adjust_Result_Bit); \
																   SET_PORT_WITH_VALUE(ADC_MUX_SELECT_REG,ADC__Left_Adjust_Result_Bit)
#define ADC_Data_Left_Adjustment_Reset()                           RESET_PORT_WITH_VALUE(ADC_MUX_SELECT_REG,ADC__Left_Adjust_Result_Bit)

#define ADC_Read_Interrupt_Flag_State()                            GET_BIT(ADC_CNTRL_STATUS_REG,ADC_Interrupt_flag_Bit)

#define ADC_Interrupt_Enable()                                     RESET_PORT_WITH_VALUE(ADC_CNTRL_STATUS_REG,ADC_Interrupt_Enable_Bit); \
                                                                   SET_PORT_WITH_VALUE(ADC_CNTRL_STATUS_REG,ADC_Interrupt_Enable_Bit)
#define ADC_Interrupt_Disable()                                    RESET_PORT_WITH_VALUE(ADC_CNTRL_STATUS_REG,ADC_Interrupt_Enable_Bit); \
																   SET_PORT_WITH_VALUE(ADC_CNTRL_STATUS_REG,ADC_Interrupt_Enable_Bit)
																   
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
#define ADC_Choose_Frequency(Frequency)                            RESET_PORT_WITH_VALUE(ADCSRA,0b00000111); \ 
                                                                   SET_PORT_WITH_VALUE(ADCSRA,Frequency)   
#endif /* ADC_DESIGNER_H_ */