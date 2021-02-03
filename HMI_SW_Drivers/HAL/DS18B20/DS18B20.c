/*
 * DS18B20.c
 *
 * Created: 9/22/2020 3:40:39 PM
 *  Author: HMI
 */




/********************Includes************************/
#define F_CPU 8000000UL
#include "avr/delay.h"
#include "UART.h"
#include "DS1820_PL_Confg.h"
#include "Data_Types.h"
#include "BitManipulation.h"
#include "DEBUG.h"
#include "Math.h"
#include "DS18B20.h"
#include "OneWire.h"
#include "Timer.h"
#include "Timer_PostBConfig.h"
volatile uinteg8_t  vgu8_DS18B20_Timer_Isr_Count=0;
volatile uinteg8_t  vgu8_Wait_Until_DS18B20_Temp_Converstion_Happens=DS18B20_START_CONVERSION;
volatile uinteg64_t gu64_DS18B20_Temprature_Reading_Buffer=0;
static   uinteg8_t  sgu8_DS18B20_Pin=0;



#if DS18B20_EXECUTION_WAY==DS18B20_EXECUTED_BY_POLLING_DIO

		void DS18B20_Init(void)
		{
           /* OneWire_Init(u8_DS18B20_Pin);*/
		}
		void DS18B20_Reset(uinteg8_t u8_DS18B20_Pin)
		{

            OneWire_Get_The_Reset_Respond(u8_DS18B20_Pin);
		}
		void DS18B20_Congfigure_Resolution(uinteg8_t u8_DS18B20_Pin,uinteg8_t u8_DS18B20_Resolution)
		{
			OneWire_Byte_Write(u8_DS18B20_Pin,DS18B20_SKIP_ROM_COMMAND);
			OneWire_Byte_Write(u8_DS18B20_Pin,DS18B20_WRITE_CONFIG_COMMAND);
			OneWire_Byte_Write(u8_DS18B20_Pin,DS18B20_NOTHING);
			OneWire_Byte_Write(u8_DS18B20_Pin,DS18B20_NOTHING);
			OneWire_Byte_Write(u8_DS18B20_Pin,u8_DS18B20_Resolution);

		}
		void DS18B20_Skip_Rom_Command(uinteg8_t u8_DS18B20_Pin)
		{
			OneWire_Byte_Write(u8_DS18B20_Pin,DS18B20_SKIP_ROM_COMMAND);
		}
		void DS18B20_Temprature_Convert_Command(uinteg8_t u8_DS18B20_Pin)
		{
			OneWire_Byte_Write(u8_DS18B20_Pin,DS18B20_TEMP_CONVERT_COMMAND);
			_delay_ms(750);
		}
		void DS18B20_Read_Scratchpad_Command(uinteg8_t u8_DS18B20_Pin)
		{
			OneWire_Byte_Write(u8_DS18B20_Pin,DS18B20_READ_SCRATCHPAD_COMMAND);
		}
		void DS18B20_Read_Two_Bytes_Of_Temprature(uinteg8_t u8_DS18B20_Pin,uinteg16_t*pu16_Temp_Value)
		{
            OneWire_Two_Bytes_Read(u8_DS18B20_Pin ,pu16_Temp_Value);
		}
		void DS18B20_Read_Temprature_Value_In_Float_Representation(uinteg8_t u8_DS18B20_Pin,volatile float64_t* pf64_DS18B20_Temp)
		{
			uinteg64_t gu64_DS18B20_Temprature_Reading_Buffer=0,u64_DS18B20_Temprature_Reading_Buffer=0;
			static uinteg8_t su8_DS18B20_Configuration_Finished=0;
			float64_t f64_DS18B20_Temp_Value=0.0,f64_DS18B20_Buffer=0.0,f64_DS18B20_Buffer_1;

			DS18B20_Reset(u8_DS18B20_Pin);

			if(su8_DS18B20_Configuration_Finished==0)
			{
				su8_DS18B20_Configuration_Finished=1;
				DS18B20_Congfigure_Resolution(u8_DS18B20_Pin,DS18B20_RESOLUTION_TYPE);
				//DS18B20 Reset
				DS18B20_Reset(u8_DS18B20_Pin);
			}


			//DS18B20 Skip ROM
			DS18B20_Skip_Rom_Command(u8_DS18B20_Pin);

			//DS18B20 Initiates temperature conversion.
			DS18B20_Temprature_Convert_Command(u8_DS18B20_Pin);

			//DS18B20 Reset
			DS18B20_Reset(u8_DS18B20_Pin);

			//DS18B20 Skip ROM
			DS18B20_Skip_Rom_Command(u8_DS18B20_Pin);
			//DS18B20 Read Scratch pad
			DS18B20_Read_Scratchpad_Command(u8_DS18B20_Pin);
			//DS18B20 Read Temperature
			DS18B20_Read_Two_Bytes_Of_Temprature(u8_DS18B20_Pin,&gu64_DS18B20_Temprature_Reading_Buffer);

			f64_DS18B20_Temp_Value=(gu64_DS18B20_Temprature_Reading_Buffer/16.0)-0.0300;

			/*f64_DS18B20_Temp_Value=(f64_DS18B20_Temp_Value+2.155)/1.0519;*/
			gu64_DS18B20_Temprature_Reading_Buffer=f64_DS18B20_Temp_Value*10.0;
			f64_DS18B20_Buffer=(f64_DS18B20_Temp_Value*10.0-gu64_DS18B20_Temprature_Reading_Buffer)*1000.0;

			gu64_DS18B20_Temprature_Reading_Buffer=f64_DS18B20_Temp_Value;
			f64_DS18B20_Buffer_1=(f64_DS18B20_Temp_Value-gu64_DS18B20_Temprature_Reading_Buffer);
			u64_DS18B20_Temprature_Reading_Buffer=f64_DS18B20_Buffer_1*10.0;

			if(f64_DS18B20_Buffer>=750)
			{
				gu64_DS18B20_Temprature_Reading_Buffer=f64_DS18B20_Temp_Value;
				f64_DS18B20_Buffer=(f64_DS18B20_Temp_Value-gu64_DS18B20_Temprature_Reading_Buffer)*10000.0;
				f64_DS18B20_Temp_Value-=f64_DS18B20_Buffer/10000.0;
				u64_DS18B20_Temprature_Reading_Buffer++;
				f64_DS18B20_Temp_Value+=u64_DS18B20_Temprature_Reading_Buffer/10.0;
			}

			*pf64_DS18B20_Temp=f64_DS18B20_Temp_Value;

		}

#elif DS18B20_EXECUTION_WAY==DS18B20_EXECUTED_BY_DIO_TIME_BASE

		void DS18B20_TIMER_ISR(void)
		{
/*			Debug_By_Toggle(0);*/
			vgu8_DS18B20_Timer_Isr_Count++;
			if(vgu8_DS18B20_Timer_Isr_Count==3u)
			{
				vgu8_Wait_Until_DS18B20_Temp_Converstion_Happens=DS18B20_END_COVERSION;
				/*Debug_By_Toggle(2);*/
				Timer_Pause(DS18B20_Timer_Init_Config.Timer_Channel);
				vgu8_DS18B20_Timer_Isr_Count=0;


			}
/*			Debug_By_Toggle(0);*/

		}
		void DS18B20_Init()
		{
			Timer_Init(&DS18B20_Timer_Init_Config);
		}
		void DS18B20_Reset(uinteg8_t u8_DS18B20_Pin)
		{
			sgu8_DS18B20_Pin=u8_DS18B20_Pin;
			OneWire_Get_The_Reset_Respond(u8_DS18B20_Pin);
		}
		void DS18B20_Congfigure_Resolution(uinteg8_t u8_DS18B20_Pin,uinteg8_t u8_DS18B20_Resolution)
		{
			OneWire_Byte_Write(u8_DS18B20_Pin,DS18B20_SKIP_ROM_COMMAND);
			OneWire_Byte_Write(u8_DS18B20_Pin,DS18B20_WRITE_CONFIG_COMMAND);
			OneWire_Byte_Write(u8_DS18B20_Pin,DS18B20_NOTHING);
			OneWire_Byte_Write(u8_DS18B20_Pin,DS18B20_NOTHING);
			OneWire_Byte_Write(u8_DS18B20_Pin,u8_DS18B20_Resolution);

		}
		void DS18B20_Skip_Rom_Command(uinteg8_t u8_DS18B20_Pin)
		{
			OneWire_Byte_Write(u8_DS18B20_Pin,DS18B20_SKIP_ROM_COMMAND);
		}
		void DS18B20_Temprature_Convert_Command(uinteg8_t u8_DS18B20_Pin)
		{
			OneWire_Byte_Write(u8_DS18B20_Pin,DS18B20_TEMP_CONVERT_COMMAND);
/*			Debug_By_Toggle(1);*/
			Timer_Start(DS18B20_Timer_Init_Config.Timer_Channel,DS18B20_TIMER_0_OUTPUT_COMAPRE_REGISTER_EQUIVALENT_TO_HALF_MILI,DS18B20_TIMER_ISR);
		}
		void DS18B20_Read_Scratchpad_Command(uinteg8_t u8_DS18B20_Pin)
		{
			OneWire_Byte_Write(u8_DS18B20_Pin,DS18B20_READ_SCRATCHPAD_COMMAND);
		}
		void DS18B20_Read_Two_Bytes_Of_Temprature(uinteg8_t u8_DS18B20_Pin,uinteg16_t*pu16_Temp_Value)
		{
			OneWire_Two_Bytes_Read(u8_DS18B20_Pin ,pu16_Temp_Value);
		}
		void DS18B20_Read_Temprature_Value_In_Float_Representation(uinteg8_t u8_DS18B20_Pin,volatile float64_t* pf64_DS18B20_Temp)
		{
			uinteg64_t u64_DS18B20_Temprature_Reading_Buffer=0;
			static uinteg8_t su8_DS18B20_Configuration_Finished=0;
			float64_t f64_DS18B20_Temp_Value=0.0,f64_DS18B20_Buffer=0.0,f64_DS18B20_Buffer_1;



		     if(vgu8_Wait_Until_DS18B20_Temp_Converstion_Happens==DS18B20_END_COVERSION)
			 {

                vgu8_Wait_Until_DS18B20_Temp_Converstion_Happens=DS18B20_START_CONVERSION;
				//DS18B20 Reset
				DS18B20_Reset(sgu8_DS18B20_Pin);
				//DS18B20 Skip ROM
				DS18B20_Skip_Rom_Command(sgu8_DS18B20_Pin);
				//DS18B20 Read Scratch pad
				DS18B20_Read_Scratchpad_Command(sgu8_DS18B20_Pin);
				//DS18B20 Read Temperature
				DS18B20_Read_Two_Bytes_Of_Temprature(sgu8_DS18B20_Pin,&gu64_DS18B20_Temprature_Reading_Buffer);
				f64_DS18B20_Temp_Value=(gu64_DS18B20_Temprature_Reading_Buffer/16.0)-0.0300;
				/*				f64_DS18B20_Temp_Value=(f64_DS18B20_Temp_Value+2.155)/1.0519;*/
				gu64_DS18B20_Temprature_Reading_Buffer=f64_DS18B20_Temp_Value*10.0;
				f64_DS18B20_Buffer=(f64_DS18B20_Temp_Value*10.0-gu64_DS18B20_Temprature_Reading_Buffer)*1000.0;

				gu64_DS18B20_Temprature_Reading_Buffer=f64_DS18B20_Temp_Value;
				f64_DS18B20_Buffer_1=(f64_DS18B20_Temp_Value-gu64_DS18B20_Temprature_Reading_Buffer);
				u64_DS18B20_Temprature_Reading_Buffer=f64_DS18B20_Buffer_1*10.0;

				if(f64_DS18B20_Buffer>=750)
				{
					gu64_DS18B20_Temprature_Reading_Buffer=f64_DS18B20_Temp_Value;
					f64_DS18B20_Buffer=(f64_DS18B20_Temp_Value-gu64_DS18B20_Temprature_Reading_Buffer)*10000.0;
					f64_DS18B20_Temp_Value-=f64_DS18B20_Buffer/10000.0;
					u64_DS18B20_Temprature_Reading_Buffer++;
					f64_DS18B20_Temp_Value+=u64_DS18B20_Temprature_Reading_Buffer/10.0;
				}
				*pf64_DS18B20_Temp=f64_DS18B20_Temp_Value;
				f64_DS18B20_Buffer=f64_DS18B20_Temp_Value;

			}
			if(vgu8_Wait_Until_DS18B20_Temp_Converstion_Happens==DS18B20_START_CONVERSION)
			{
					vgu8_Wait_Until_DS18B20_Temp_Converstion_Happens=DS18B20_DO_NOTHING;



					if(su8_DS18B20_Configuration_Finished==0)
					{
						DS18B20_Reset(u8_DS18B20_Pin);
						su8_DS18B20_Configuration_Finished=1;
						DS18B20_Congfigure_Resolution(u8_DS18B20_Pin,DS18B20_RESOLUTION_TYPE);
					}


					//DS18B20 Reset
					DS18B20_Reset(u8_DS18B20_Pin);				//DS18B20 Skip ROM
					DS18B20_Skip_Rom_Command(u8_DS18B20_Pin);

					//DS18B20 Initiates temperature conversion.
					DS18B20_Temprature_Convert_Command(u8_DS18B20_Pin);
					*pf64_DS18B20_Temp=f64_DS18B20_Buffer;
			}

		}

#endif
