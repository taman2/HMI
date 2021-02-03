/*
 * T_SCREEN.h
 *
 * Created: 9/26/2020 5:38:47 PM
 *  Author: Mohamed
 */ 
#include "Data_Types.h"


#ifndef T_SCREEN_H_
#define T_SCREEN_H_

#define HAND_SHAKE               ( 0x30 )
#define READ_VERSION             ( 0x31 )
#define READ_PG_ID               ( 0x32 )
#define T_RESPONSE               ( 0x72/ 0x73/ 0x77/ 0x78/ 0x79)
#define T_RESPONSE_Normal        ( 0x77 )
#define T_RESPONSE_PageID        ( 0x78 )
#define SET_SYS_CONFIG           ( 0xE0 )
#define SEL_PROJECT              ( 0xE1 )
#define T_CALIB                  ( 0xE4 )
#define SCREEN_SAVER             ( 0x5E )
#define BACKLIGHT_CTRL           ( 0x5F )
#define BUZZER_T_SOUND           ( 0x79 )
#define BUZZER_CTRL              ( 0x7A )
#define FLASH_WRITE              ( 0x90 )
#define FLASH_READ               ( 0x91 )
#define RTC_READ                 ( 0x9B )
#define RTC_SET                  ( 0x9C )
#define USR_BIN_READ             ( 0x93 )
#define U_DRV_FORMAT             ( 0xE2 )
#define U_DRV_UNLOCK             ( 0xE3 )

/***************Display Control Function Commands Details***************************/
#define DISP_PAGE                ( 0x70 )
#define SET_ELEMENT_FG           ( 0x7E )
#define SET_ELEMENT_BG           ( 0x7F )
#define SET_CODEPAGE             ( 0xE7 )
#define SUSPEND_VP_REFRESH       ( 0xE8 )

/************VP Function Commands Details ********************************/
#define SUCCESSIVE_WRITE         ( 0x82 )
#define SUCCESSIVE_READ          ( 0x83 )
#define BP1_WRITE                ( 0x4B )
#define BP1_WRITE_COMPRESS       ( 0x4C )
#define G16_WRITE                ( 0x4D )
#define G16_WRITE_ROTATE         ( 0x4E )
#define SYSTEM_Register_Write    ( 0x3B )
#define SYSTEM_Register_Read     ( 0x3C )
#define STR_WRITE                ( 0x42 )
#define STR_READ                 ( 0x43 )
#define STR_FILL                 ( 0x46 )
#define N16_WRITE                ( 0x3D )
#define N16_READ                 ( 0x3E )
#define N16_FILL                 ( 0x3F )
#define N32_WRITE                ( 0x44 )
#define N32_READ                 ( 0x45 )
#define N32_FILL                 ( 0x47 )
#define N64_WRITE                ( 0x48 )
#define N64_READ                 ( 0x49 )
#define N64_FILL                 ( 0x4A )

#define T_SCREEN_HEADER_BYTE     (0XAA)
#define T_SCREEN_TAILE_BYTE1     (0XCC)
#define T_SCREEN_TAILE_BYTE2     (0X33)
#define T_SCREEN_TAILE_BYTE3     (0XC3)
#define T_SCREEN_TAILE_BYTE4     (0X3C)

#define Packet_OK                    1U
#define Packet_NOT_OK                0U
#define T_SCREEN_VAR_SIZE_1          1U
#define T_SCREEN_VAR_SIZE_2          2U
#define T_SCREEN_VAR_SIZE_4          4U
#define T_SCREEN_VAR_SIZE_8          8U
#define T_SCREEN_NO_DATA             0U
#define T_SCREEN_TOGGLE_VAR_BIT      7U
#define T_16BIT_ADDRESS            (0x08)
#define T_32BIT_ADDRESS            (0x02)
#define MAIN_PAGE                  (0x00)
#define TIMER_PAGE                 (0X01)
#define HOUER_METER_PAGE           (0X02)
#define INITIAL_PAGE               (0X03)
#define HOUER_SET_TEMPRATURE_PAGE  (0X04)
#define LED_CTRL_PAGE              (0x05)
#define T_SCREEN_KEY1              (0X01)
#define T_SCREEN_KEY2              (0X02)
#define T_SCREEN_KEY3              (0X03)
#define T_SCREEN_KEY4              (0X04)
#define T_SCREEN_KEY5              (0X05)
#define T_SCREEN_KEY6              (0X06)




/************************* T SCREEN SYSTEM CONFIGRATION COMMANDS ****************************/

#define  T_SCREEN_TIMER_UP_COUNT          03
#define  T_SCREEN_TIMER_DOWEN_COUNT       01
#define  T_SCREEN_TIMER_STOP              00



/******************** SCREEN USED 16bit VARIABLS ADDRESSES ***********************************/

   #define T_SCREEN_VAR16_ADDRESS0                0X00080000
   #define T_SCREEN_VAR16_ADDRESS1                0X00080002
   #define T_SCREEN_VAR16_ADDRESS2                0X00080004
   #define T_SCREEN_VAR16_ADDRESS3                0X00080006
   #define T_SCREEN_VAR16_ADDRESS4                0X00080008
   #define T_SCREEN_VAR16_ADDRESS5                0X0008000A
   #define T_SCREEN_VAR16_ADDRESS6                0X0008000C
   #define T_SCREEN_VAR16_ADDRESS7                0X0008000E
   #define T_SCREEN_VAR16_ADDRESS8                0X00080010
   #define T_SCREEN_VAR16_ADDRESS9                0X00080012
   #define T_SCREEN_VAR16_ADDRESS10               0X00080014
   #define T_SCREEN_VAR16_ADDRESS11               0X00080016

   
/*********************** SCREEN USED 32bit VARIABLS ADDRESSES *********************************************/


   #define T_SCREEN_VAR32_ADDRESS0                 0X00020000
   #define T_SCREEN_VAR32_ADDRESS1                 0X00020004
   #define T_SCREEN_VAR32_ADDRESS2                 0X00020008
   #define T_SCREEN_VAR32_ADDRESS3                 0X0002000C
   #define T_SCREEN_VAR32_ADDRESS4                 0X00020010
   #define T_SCREEN_VAR32_ADDRESS5                 0X00020014

   
   /*********************** SCREEN USED TIMER VARIABLS ADDRESSES *********************************************/
   
   #define T_SCREEN_TIM0_VAR_ADDRESS               0X0002FFE0
   #define T_SCREEN_TIM1_VAR_ADDRESS               0X0002FFE4
   #define T_SCREEN_TIM2_VAR_ADDRESS               0X0002FFE8
   #define T_SCREEN_TIM3_VAR_ADDRESS               0X0002FFEC
   #define T_SCREEN_TIM4_VAR_ADDRESS               0X0002FFF0

   /*************** SCREEN USED TIMER CTR RIGISRERs  VARIABLS ADDRESSES ********************************/

   #define T_SCREEN_TIM0_CTR_ADDRESS               0X00FFFF00
   #define T_SCREEN_TIM1_CTR_ADDRESS               0X00FFFF01
   #define T_SCREEN_TIM2_CTR_ADDRESS               0X00FFFF02
   #define T_SCREEN_TIM3_CTR_ADDRESS               0X00FFFF03
   #define T_SCREEN_TIM4_CTR_ADDRESS               0X00FFFF04
   
   
 /******************************************** SCREEN GLOBAL VARS  ************************** *********************************************/


   extern volatile uinteg8_t TScreen_Recived_Buffer[15];
   extern volatile uinteg8_t TScreen_Send_Buffer[15];
   extern volatile uinteg8_t TScreen_Recieve_Complete_Flag;
   extern volatile uinteg8_t TScreen_Recived_Buffer_Index;
   extern volatile uinteg8_t TScreen_Recieved_key_pressed;
   extern volatile uinteg8_t TScreen_Recieved_current_Page;
   //extern volatile uinteg32_t TScreen_Recived_Timer_Value;
   extern volatile uinteg8_t TScreen_Recieve_Data__Not_Complete_Flag;
   extern volatile uinteg32_t TScreen_Recived_Var_Value;
   extern volatile uinteg32_t TScreen_Recived_Var_Address;
   extern volatile uinteg32_t TScreen_Recived_Var_Value;
   //extern volatile uinteg8_t Send_Temprature_values_EverySec_Counter;
   //extern volatile uinteg16_t Send_Hour_Meter_value_EveryHour_Counter;
   //extern volatile uinteg16_t TScreen_Icon_Vlue;
   //extern  volatile uinteg8_t TScreen_Half_Power_LedCtrl;
  
/*  extern float32_t  f32_Humadity,f32_Temp;
  extern uinteg8_t u8_DHT_Result_State, u8_DHT_No_Error_Flag,u8_DHT_Check_Sum_Flag,u8_DHT_No_Response_Flag;
  uinteg8_t Air_High_Temp_Flag;
  uinteg8_t Air_Normal_Temp_Flag;
  extern  uinteg16_t TScreen_Recieved_BabyTemp;
  extern uinteg16_t TScreen_Recieved_AirTemp;*/
/***************************************** SCREEN MAIN  FUNCTIONS  ************************** *********************************************/

void TScreen_Init(void);
void TScreen_Send_Packet(volatile uinteg8_t *TScreen_sentPacket);
void TScreen_Recieve_Packet(void);
void TScreen_Generate_VpFunctions_packet(volatile uinteg8_t *Screen_packet ,uinteg8_t T_Screen_Command ,uinteg32_t T_Screen_Var_Adress
                                              ,uinteg32_t T_Screen_Var_Value, uinteg8_t T_Screen_Var_Size );
											  
void TScreen_GenerateConfig_Status_Functions_packet( uinteg8_t *Screen_packet ,uinteg8_t T_Screen_Command , uinteg64_t T_Screen_Data_Value, 
                                                         uinteg8_t T_Screen_Data_Size);

uinteg8_t TScreen_GetData_From_Recievd_Buffer(void);
void TScreen_Start_Timer(uinteg8_t Timer_Num);
void TScreen_Stop_Timer(void);
void TScreen_Start_Heater(void);
void TScreen_Stop_Heater(void);
void TScreen_Start_cooler(void);
void TScreen_Stop_cooler(void);
void TScreen_Read_Timer_value(uinteg8_t Timer_Num);
void TScreen_Write_Timer_value(uinteg32_t Timer_Value,uinteg8_t Timer_Num);
void TScreen_Read_Temp_value(uinteg8_t Command);
void TScreen_Write_Temp_value(float32_t Temp1,float32_t Temp2);
void TScreen_Disable_Item(uinteg32_t Item_Address);
void Send_Temprature_values_EverySec_ISR(void);
void Send_Temprature_values_EverySec(void);
void TScreen_Mian_State(void);
void TScreen_Set_Time_State(void);
void TScreen_Houer_Merter_Reset_State(void);
void TScreen_Set_Temprature_State(void);

void TScreen_Get_KeyPressed_From_Recievd_Buffer(void);
void TScreen_Get_Value32_From_Recievd_Buffer(void);
void TScreen_Get_Value16_From_Recievd_Buffer(void);

void TScreen_Send_Sensor_Not_Conn(uinteg8_t Error_State);
void TScreen_Send_Sensor_Check_Sum(uinteg8_t Error_State);
void TScreen_Write_HouerMeter_everyHouer(void);









#endif /* T_SCREEN_H_ */