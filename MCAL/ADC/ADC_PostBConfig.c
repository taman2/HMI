/*
 * ADC_PostBConfig.c
 *
 * Created: 06/01/2020 13:43:40
 *  Author: Native_programmer
 */ 
#include "ADC_PostBConfig.h"

gstrADC_Config_t gstr_Temp_sensorConfig={    ADC_Channel_0
											,ADC_Voltage_Refrence_AVCC
											,ADC_Freq_125KHZ
											,ADC_Auto_Trigger_Disable
											,ADC_No_Need_To_Trigger
											,ADC_Right_Adjustment
											,ADC_Executed_By_Time_Driven
										};