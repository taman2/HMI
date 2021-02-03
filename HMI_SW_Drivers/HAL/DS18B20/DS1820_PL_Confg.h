/*
 * DS1820_PL_Confg.h
 *
 * Created: 9/23/2020 5:31:18 PM
 *  Author: HMI
 */ 


#ifndef DS1820_PL_CONFG_H_
#define DS1820_PL_CONFG_H_

        /**********************DESIGNERS MACROS****************************/
        #define DS18B20_EXECUTED_BY_EVENT_BASE      1U
        #define DS18B20_EXECUTED_BY_POLLING			2U
		#define DS18B20_EVENT_BASE_BY_INTERRUPT     3U
		#define DS18B20_EVENT_BASE_BY_TIME          4U		
		#define DS18B20_EXECUTED_BY_POLLING_DIO     5U
		#define DS18B20_EXECUTED_BY_DIO_TIME_BASE   6U		
        #define DS18B20_RESOLUTION_9_BITS			0x1FU
        #define DS18B20_RESOLUTION_10_BITS		    0x3FU
        #define DS18B20_RESOLUTION_11_BITS          0x5FU
        #define DS18B20_RESOLUTION_12_BITS          0x7FU
		/**********************CONFIGURATION MACROS***********************/
        #define DS18B20_EXECUTION_WAY				DS18B20_EXECUTED_BY_DIO_TIME_BASE
        #define DS18B20_RESOLUTION_TYPE			    DS18B20_RESOLUTION_12_BITS


#endif /* DS1820_PL_CONFG_H_ */  