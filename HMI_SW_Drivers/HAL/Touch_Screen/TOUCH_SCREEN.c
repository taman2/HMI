/*
 * T_SCREEN.c
 *
 * Created: 9/26/2020 5:32:10 PM
 *  Author: Mohamed Salah Taman
 */
#include "TOUCH_SCREEN.h"
#include "UART.h"
#include "avr/eeprom.h"
#include "DHT.h"

volatile uinteg8_t TScreen_Recived_Buffer[15]={0};
volatile uinteg8_t TScreen_Send_Buffer[15]={0};
volatile uinteg8_t TScreen_Recived_Command=0;
volatile uinteg32_t TScreen_Recived_Var_Address=0;
volatile uinteg32_t TScreen_Recived_Var_Value=0;
volatile uinteg8_t TScreen_Recieve_Complete_Flag=0;
volatile uinteg8_t TScreen_Recieve_Data__Not_Complete_Flag=1;
volatile uinteg8_t TScreen_Recived_Buffer_Index=0;
volatile uinteg8_t TScreen_Recieved_current_Page=0;
volatile uinteg8_t TScreen_Recieved_key_pressed=0;

/*POINTER TO FUCTION CARRY THE ADRESS OF RX_ISR_FUNCTION  */




/***********************FOR VP Functions**************************************************************************/
/*********************************************************************************************************************************************/
 void TScreen_Generate_VpFunctions_packet(volatile uinteg8_t *Screen_packet ,uinteg8_t T_Screen_Command , uinteg32_t T_Screen_Var_Adress ,
                                            uinteg32_t T_Screen_Var_Value, uinteg8_t T_Screen_Var_Size )
{
	if(T_Screen_Var_Size ==T_SCREEN_VAR_SIZE_2)
	{
		Screen_packet[0]=T_SCREEN_HEADER_BYTE;
	    Screen_packet[1]=T_Screen_Command;
        Screen_packet[2]=(uinteg8_t)(T_Screen_Var_Adress>>24);
        Screen_packet[3]=(uinteg8_t)(T_Screen_Var_Adress>>16);
        Screen_packet[4]=(uinteg8_t)(T_Screen_Var_Adress>>8);
        Screen_packet[5]=(uinteg8_t)(T_Screen_Var_Adress);
		Screen_packet[6]=(uinteg8_t)(T_Screen_Var_Value>>8);
		Screen_packet[7]=(uinteg8_t)(T_Screen_Var_Value);
		Screen_packet[8]=(T_SCREEN_TAILE_BYTE1);
		Screen_packet[9]=(T_SCREEN_TAILE_BYTE2);
		Screen_packet[10]=(T_SCREEN_TAILE_BYTE3);
		Screen_packet[11]=(T_SCREEN_TAILE_BYTE4);
	}
	else if(T_Screen_Var_Size ==T_SCREEN_VAR_SIZE_1)
	{
		Screen_packet[0]=T_SCREEN_HEADER_BYTE;
		Screen_packet[1]=T_Screen_Command;
		Screen_packet[2]=(uinteg8_t)(T_Screen_Var_Adress>>24);
		Screen_packet[3]=(uinteg8_t)(T_Screen_Var_Adress>>16);
		Screen_packet[4]=(uinteg8_t)(T_Screen_Var_Adress>>8);
		Screen_packet[5]=(uinteg8_t)(T_Screen_Var_Adress);
		Screen_packet[6]=(uinteg8_t)(T_Screen_Var_Value);
		Screen_packet[7]=(T_SCREEN_TAILE_BYTE1);
		Screen_packet[8]=(T_SCREEN_TAILE_BYTE2);
		Screen_packet[9]=(T_SCREEN_TAILE_BYTE3);
		Screen_packet[10]=(T_SCREEN_TAILE_BYTE4);
	}
	else if(T_Screen_Var_Size ==T_SCREEN_VAR_SIZE_4)
	{
	    Screen_packet[0]=T_SCREEN_HEADER_BYTE;
		Screen_packet[1]=T_Screen_Command;
	    Screen_packet[2]=(uinteg8_t)(T_Screen_Var_Adress>>24);
		Screen_packet[3]=(uinteg8_t)(T_Screen_Var_Adress>>16);
	    Screen_packet[4]=(uinteg8_t)(T_Screen_Var_Adress>>8);
		Screen_packet[5]=(uinteg8_t)(T_Screen_Var_Adress);
		Screen_packet[6]=(uinteg8_t)(T_Screen_Var_Value>>24);
		Screen_packet[7]=(uinteg8_t)(T_Screen_Var_Value>>16);
		Screen_packet[8]=(uinteg8_t)(T_Screen_Var_Value>>8);
		Screen_packet[9]=(uinteg8_t)(T_Screen_Var_Value);
		Screen_packet[10]=(T_SCREEN_TAILE_BYTE1);
		Screen_packet[11]=(T_SCREEN_TAILE_BYTE2);
		Screen_packet[12]=(T_SCREEN_TAILE_BYTE3);
		Screen_packet[13]=(T_SCREEN_TAILE_BYTE4);
	}
	else if(T_Screen_Var_Size ==T_SCREEN_NO_DATA)
	{

		Screen_packet[0]=T_SCREEN_HEADER_BYTE;
		Screen_packet[1]=T_Screen_Command;
		Screen_packet[2]=(uinteg8_t)(T_Screen_Var_Adress>>24);
		Screen_packet[3]=(uinteg8_t)(T_Screen_Var_Adress>>16);
		Screen_packet[4]=(uinteg8_t)(T_Screen_Var_Adress>>8);
		Screen_packet[5]=(uinteg8_t)(T_Screen_Var_Adress);
		Screen_packet[6]=(T_SCREEN_TAILE_BYTE1);
		Screen_packet[7]=(T_SCREEN_TAILE_BYTE2);
		Screen_packet[8]=(T_SCREEN_TAILE_BYTE3);
		Screen_packet[9]=(T_SCREEN_TAILE_BYTE4);
	}
    else if(T_Screen_Var_Size ==T_SCREEN_TOGGLE_VAR_BIT)
	{

		Screen_packet[0]=T_SCREEN_HEADER_BYTE;
		Screen_packet[1]=T_Screen_Command;
		Screen_packet[2]=(uinteg8_t)(T_Screen_Var_Adress>>24);
		Screen_packet[3]=(uinteg8_t)(T_Screen_Var_Adress>>16);
		Screen_packet[4]=(uinteg8_t)(T_Screen_Var_Adress>>8);
		Screen_packet[5]=(uinteg8_t)(T_Screen_Var_Adress);
	    Screen_packet[6]=(uinteg8_t)(T_Screen_Var_Value);
		Screen_packet[7]=(T_SCREEN_TAILE_BYTE1);
		Screen_packet[8]=(T_SCREEN_TAILE_BYTE2);
		Screen_packet[9]=(T_SCREEN_TAILE_BYTE3);
		Screen_packet[10]=(T_SCREEN_TAILE_BYTE4);
	}

}

void TScreen_GenerateConfig_Status_Functions_packet( uinteg8_t *Screen_packet ,uinteg8_t T_Screen_Command , uinteg64_t T_Screen_Data_Value,
                                                    uinteg8_t T_Screen_Data_Size)
{
	if(T_Screen_Data_Size ==T_SCREEN_NO_DATA)
	{
		Screen_packet[0]=T_SCREEN_HEADER_BYTE;
		Screen_packet[1]=T_Screen_Command;
		Screen_packet[2]=(T_SCREEN_TAILE_BYTE1);
		Screen_packet[3]=(T_SCREEN_TAILE_BYTE2);
		Screen_packet[4]=(T_SCREEN_TAILE_BYTE3);
		Screen_packet[5]=(T_SCREEN_TAILE_BYTE4);
	}
	else if(T_Screen_Data_Size ==T_SCREEN_VAR_SIZE_4)
	{
		Screen_packet[0]=T_SCREEN_HEADER_BYTE;
		Screen_packet[1]=T_Screen_Command;
		Screen_packet[2]=(uinteg8_t)(T_Screen_Data_Value>>24);
		Screen_packet[3]=(uinteg8_t)(T_Screen_Data_Value>>16);
		Screen_packet[4]=(uinteg8_t)(T_Screen_Data_Value>>8);
		Screen_packet[5]=(uinteg8_t)(T_Screen_Data_Value);
		Screen_packet[6]=(T_SCREEN_TAILE_BYTE1);
		Screen_packet[7]=(T_SCREEN_TAILE_BYTE2);
		Screen_packet[8]=(T_SCREEN_TAILE_BYTE3);
		Screen_packet[9]=(T_SCREEN_TAILE_BYTE4);
	}
	else if(T_Screen_Data_Size ==T_SCREEN_VAR_SIZE_2)
	{
		Screen_packet[0]=T_SCREEN_HEADER_BYTE;
		Screen_packet[1]=T_Screen_Command;
		Screen_packet[2]=(uinteg8_t)(T_Screen_Data_Value>>8);
		Screen_packet[3]=(uinteg8_t)(T_Screen_Data_Value);
		Screen_packet[4]=(T_SCREEN_TAILE_BYTE1);
		Screen_packet[5]=(T_SCREEN_TAILE_BYTE2);
		Screen_packet[6]=(T_SCREEN_TAILE_BYTE3);
		Screen_packet[7]=(T_SCREEN_TAILE_BYTE4);
	}
	else if(T_Screen_Data_Size ==T_SCREEN_VAR_SIZE_1)
	{

		Screen_packet[0]=T_SCREEN_HEADER_BYTE;
		Screen_packet[1]=T_Screen_Command;
		Screen_packet[2]=(uinteg8_t)(T_Screen_Data_Value);
		Screen_packet[3]=(T_SCREEN_TAILE_BYTE1);
		Screen_packet[4]=(T_SCREEN_TAILE_BYTE2);
		Screen_packet[5]=(T_SCREEN_TAILE_BYTE3);
		Screen_packet[6]=(T_SCREEN_TAILE_BYTE4);
	}
    else if(T_Screen_Data_Size ==7)
	{
		Screen_packet[0]=T_SCREEN_HEADER_BYTE;
		Screen_packet[1]=T_Screen_Command;
		Screen_packet[2]=(uinteg8_t)(T_Screen_Data_Value>>48);
		Screen_packet[3]=(uinteg8_t)(T_Screen_Data_Value>>40);
		Screen_packet[4]=(uinteg8_t)(T_Screen_Data_Value>>32);
		Screen_packet[5]=(uinteg8_t)(T_Screen_Data_Value>>24);
		Screen_packet[6]=(uinteg8_t)(T_Screen_Data_Value>>16);
		Screen_packet[7]=(uinteg8_t)(T_Screen_Data_Value>>8);
		Screen_packet[8]=(uinteg8_t)(T_Screen_Data_Value);
		Screen_packet[9]=(T_SCREEN_TAILE_BYTE1);
		Screen_packet[10]=(T_SCREEN_TAILE_BYTE2);
		Screen_packet[11]=(T_SCREEN_TAILE_BYTE3);
		Screen_packet[12]=(T_SCREEN_TAILE_BYTE4);
	}

}
void TScreen_Send_Packet(volatile uinteg8_t *TScreen_sentPacket){
	USART_Send_Packet(TScreen_sentPacket,T_SCREEN_TAILE_BYTE4);
}
void TScreen_Recieve_Packet(void)
{
 USART_Receive_Byte_Iterrupt(&TScreen_Recived_Buffer[TScreen_Recived_Buffer_Index]);
  TScreen_Recieve_Data__Not_Complete_Flag=1;
  if(TScreen_Recived_Buffer[0]== T_SCREEN_HEADER_BYTE)
  {
	if(TScreen_Recived_Buffer[TScreen_Recived_Buffer_Index]!= T_SCREEN_TAILE_BYTE4)
	{
	  TScreen_Recived_Buffer_Index++;
	}
	else
	{
	  TScreen_Recived_Buffer_Index=0;
	  TScreen_Recieve_Complete_Flag=1;
	  TScreen_Recieve_Data__Not_Complete_Flag=0;
	}
  }
  else
  {
	  TScreen_Recived_Buffer_Index=0;
	  TScreen_Recieve_Complete_Flag=1;
      TScreen_Recieve_Data__Not_Complete_Flag=0;
  }
}
uinteg8_t TScreen_GetData_From_Recievd_Buffer(void)
{

	if(TScreen_Recived_Buffer[0]==T_SCREEN_HEADER_BYTE &&TScreen_Recived_Buffer[1]
	    ==T_RESPONSE_Normal &&TScreen_Recived_Buffer[3]==T_16BIT_ADDRESS)
	{
		TScreen_Recived_Var_Address=TScreen_Recived_Buffer[2];
		TScreen_Recived_Var_Address=(TScreen_Recived_Var_Address<<8);
		TScreen_Recived_Var_Address|=TScreen_Recived_Buffer[3];
		TScreen_Recived_Var_Address=(TScreen_Recived_Var_Address<<8);
		TScreen_Recived_Var_Address|=TScreen_Recived_Buffer[4];
		TScreen_Recived_Var_Address=(TScreen_Recived_Var_Address<<8);
		TScreen_Recived_Var_Address|=TScreen_Recived_Buffer[5];
		TScreen_Recived_Var_Value=TScreen_Recived_Buffer[6];
		TScreen_Recived_Var_Value=(TScreen_Recived_Var_Value<<8);
		TScreen_Recived_Var_Value|=TScreen_Recived_Buffer[7];
		TScreen_Recieve_Complete_Flag=0;
		return 1;
	}

	else if(TScreen_Recived_Buffer[0]==T_SCREEN_HEADER_BYTE &&TScreen_Recived_Buffer[1]
	        ==T_RESPONSE_Normal  &&TScreen_Recived_Buffer[3]==T_32BIT_ADDRESS)
	{
		TScreen_Recived_Var_Address=TScreen_Recived_Buffer[2];
		TScreen_Recived_Var_Address=(TScreen_Recived_Var_Address<<8);
		TScreen_Recived_Var_Address|=TScreen_Recived_Buffer[3];
		TScreen_Recived_Var_Address=(TScreen_Recived_Var_Address<<8);
		TScreen_Recived_Var_Address|=TScreen_Recived_Buffer[4];
		TScreen_Recived_Var_Address=(TScreen_Recived_Var_Address<<8);
		TScreen_Recived_Var_Address|=TScreen_Recived_Buffer[5];
		TScreen_Recived_Var_Value=TScreen_Recived_Buffer[6];
		TScreen_Recived_Var_Value=(TScreen_Recived_Var_Value<<8);
		TScreen_Recived_Var_Value|=TScreen_Recived_Buffer[7];
		TScreen_Recived_Var_Value=(TScreen_Recived_Var_Value<<8);
		TScreen_Recived_Var_Value|=TScreen_Recived_Buffer[8];
		TScreen_Recived_Var_Value=(TScreen_Recived_Var_Value<<8);
		TScreen_Recived_Var_Value|=TScreen_Recived_Buffer[9];

		TScreen_Recieve_Complete_Flag=0;
		return 1;

	}

	else if(TScreen_Recived_Buffer[0]==T_SCREEN_HEADER_BYTE &&TScreen_Recived_Buffer[1]
	         ==T_RESPONSE_PageID)
	{
		TScreen_Recieved_current_Page=TScreen_Recived_Buffer[3];
		TScreen_Recieved_key_pressed=TScreen_Recived_Buffer[4];
		TScreen_Recieve_Complete_Flag=0;
		return 1;

	}
	else if(TScreen_Recived_Buffer[0]==T_SCREEN_HEADER_BYTE &&TScreen_Recived_Buffer[1]==READ_PG_ID )
	{
		TScreen_Recieved_current_Page=TScreen_Recived_Buffer[3];
		TScreen_Recieved_key_pressed=0;
		TScreen_Recieve_Complete_Flag=0;
		return 1;
	}
	else if(TScreen_Recived_Buffer[0]==T_SCREEN_HEADER_BYTE &&TScreen_Recived_Buffer[1]==N32_READ)
	{

		TScreen_Recived_Var_Value=TScreen_Recived_Buffer[2];
		TScreen_Recived_Var_Value=(TScreen_Recived_Var_Value<<8);
		TScreen_Recived_Var_Value|=TScreen_Recived_Buffer[3];
		TScreen_Recived_Var_Value=(TScreen_Recived_Var_Value<<8);
		TScreen_Recived_Var_Value|=TScreen_Recived_Buffer[4];
		TScreen_Recived_Var_Value=(TScreen_Recived_Var_Value<<8);
		TScreen_Recived_Var_Value|=TScreen_Recived_Buffer[5];
		TScreen_Recieve_Complete_Flag=0;
	}
	else
	{
		TScreen_Recieve_Complete_Flag=0;
	}
   //}

return 0;


}
void TScreen_Get_KeyPressed_From_Recievd_Buffer(void)
{

  if(TScreen_Recived_Buffer[0]==T_SCREEN_HEADER_BYTE &&TScreen_Recived_Buffer[1]
                                  ==T_RESPONSE_PageID)
  {
	TScreen_Recieved_current_Page=TScreen_Recived_Buffer[3];
	TScreen_Recieved_key_pressed=TScreen_Recived_Buffer[4];
	TScreen_Recieve_Complete_Flag=0;

  }
  else
  {
	  	TScreen_Recieve_Complete_Flag=0;

  }
}
void TScreen_Get_Value32_From_Recievd_Buffer(void)
{

    if(TScreen_Recived_Buffer[0]==T_SCREEN_HEADER_BYTE &&TScreen_Recived_Buffer[1]==N32_READ)
	{

		TScreen_Recived_Var_Value=TScreen_Recived_Buffer[2];
		TScreen_Recived_Var_Value=(TScreen_Recived_Var_Value<<8);
		TScreen_Recived_Var_Value|=TScreen_Recived_Buffer[3];
		TScreen_Recived_Var_Value=(TScreen_Recived_Var_Value<<8);
		TScreen_Recived_Var_Value|=TScreen_Recived_Buffer[4];
		TScreen_Recived_Var_Value=(TScreen_Recived_Var_Value<<8);
		TScreen_Recived_Var_Value|=TScreen_Recived_Buffer[5];
		TScreen_Recieve_Complete_Flag=0;
	}
	else
	{
		TScreen_Recieve_Complete_Flag=0;
	}
}
void TScreen_Get_Value16_From_Recievd_Buffer(void)
{

	if(TScreen_Recived_Buffer[0]==T_SCREEN_HEADER_BYTE &&TScreen_Recived_Buffer[1]==N16_READ)
	{
		TScreen_Recived_Var_Value=0x00;
		TScreen_Recived_Var_Value=(TScreen_Recived_Var_Value<<8);
		TScreen_Recived_Var_Value|=0x00;
		TScreen_Recived_Var_Value=(TScreen_Recived_Var_Value<<8);
		TScreen_Recived_Var_Value|=TScreen_Recived_Buffer[2];
		TScreen_Recived_Var_Value=(TScreen_Recived_Var_Value<<8);
		TScreen_Recived_Var_Value|=TScreen_Recived_Buffer[3];

		TScreen_Recieve_Complete_Flag=0;
	}
	else
	{
		TScreen_Recieve_Complete_Flag=0;
	}
}

void TScreen_Start_Timer(uinteg8_t Timer_Num)
{
   switch(Timer_Num)
  {
	case(0):
     TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,SYSTEM_Register_Write,T_SCREEN_TIM0_CTR_ADDRESS,T_SCREEN_TIMER_DOWEN_COUNT,T_SCREEN_VAR_SIZE_1);
     TScreen_Send_Packet(TScreen_Send_Buffer);
	 break;
	case(1):
	 TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,SYSTEM_Register_Write,T_SCREEN_TIM1_CTR_ADDRESS,T_SCREEN_TIMER_UP_COUNT,T_SCREEN_VAR_SIZE_1);
	 TScreen_Send_Packet(TScreen_Send_Buffer);
	 break;
	case(2):
	 TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,SYSTEM_Register_Write,T_SCREEN_TIM2_CTR_ADDRESS,T_SCREEN_TIMER_UP_COUNT,T_SCREEN_VAR_SIZE_1);
	 TScreen_Send_Packet(TScreen_Send_Buffer);
	 break;
	case(3):
	 TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,SYSTEM_Register_Write,T_SCREEN_TIM3_CTR_ADDRESS,T_SCREEN_TIMER_UP_COUNT,T_SCREEN_VAR_SIZE_1);
	 TScreen_Send_Packet(TScreen_Send_Buffer);
	 break;
  }

}
void TScreen_Stop_Timer()
{
   TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,SYSTEM_Register_Write,T_SCREEN_TIM0_CTR_ADDRESS,T_SCREEN_TIMER_STOP,T_SCREEN_VAR_SIZE_1);
   TScreen_Send_Packet(TScreen_Send_Buffer);
   TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,SYSTEM_Register_Write,T_SCREEN_TIM1_CTR_ADDRESS,T_SCREEN_TIMER_STOP,T_SCREEN_VAR_SIZE_1);
   TScreen_Send_Packet(TScreen_Send_Buffer);
   /*TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,SYSTEM_Register_Write,T_SCREEN_TIM3_CTR_ADDRESS,T_SCREEN_TIMER_STOP,T_SCREEN_VAR_SIZE_1);
   TScreen_Send_Packet(TScreen_Send_Buffer);*/



}
void TScreen_Read_Timer_value(uinteg8_t Timer_Num)
{
	switch(Timer_Num)
	{
		case(0):
		TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,N32_READ,T_SCREEN_TIM0_VAR_ADDRESS,T_SCREEN_NO_DATA,T_SCREEN_NO_DATA);
		TScreen_Send_Packet(TScreen_Send_Buffer);
		break;
		case(1):
		TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,N32_READ,T_SCREEN_TIM1_VAR_ADDRESS,T_SCREEN_NO_DATA,T_SCREEN_NO_DATA);
		TScreen_Send_Packet(TScreen_Send_Buffer);
		break;
		case(2):
		TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,N32_READ,T_SCREEN_TIM2_VAR_ADDRESS,T_SCREEN_NO_DATA,T_SCREEN_NO_DATA);
		TScreen_Send_Packet(TScreen_Send_Buffer);
		break;
		case(3):
		TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,N32_READ,T_SCREEN_TIM3_VAR_ADDRESS,T_SCREEN_NO_DATA,T_SCREEN_NO_DATA);
		TScreen_Send_Packet(TScreen_Send_Buffer);
		break;
	}

}
void TScreen_Write_Timer_value(uinteg32_t Timer_Value,uinteg8_t Timer_Num)
{
	 switch(Timer_Num)
	 {
	   case(0):
		       TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,N32_WRITE,T_SCREEN_TIM0_VAR_ADDRESS,Timer_Value,T_SCREEN_VAR_SIZE_4);
		       TScreen_Send_Packet(TScreen_Send_Buffer);
		       break;
	   case(1):
	           TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,N32_WRITE,T_SCREEN_TIM1_VAR_ADDRESS,Timer_Value,T_SCREEN_VAR_SIZE_4);
	           TScreen_Send_Packet(TScreen_Send_Buffer);
			   break;
	   case(2):
	           TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,N32_WRITE,T_SCREEN_TIM2_VAR_ADDRESS,Timer_Value,T_SCREEN_VAR_SIZE_4);
	           TScreen_Send_Packet(TScreen_Send_Buffer);
	           break;
	   case(3):
	           TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,N32_WRITE,T_SCREEN_TIM3_VAR_ADDRESS,Timer_Value,T_SCREEN_VAR_SIZE_4);
	           TScreen_Send_Packet(TScreen_Send_Buffer);
	           break;

	 }
}
void TScreen_Disable_Item(uinteg32_t Item_Address){
	TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,N16_WRITE,Item_Address,(uinteg16_t)0x0000,T_SCREEN_VAR_SIZE_2);
	TScreen_Send_Packet(TScreen_Send_Buffer);

}
void TScreen_Enable_Item(uinteg32_t Item_Address){
		TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,N16_WRITE,Item_Address,(uinteg16_t)0x0001,T_SCREEN_VAR_SIZE_2);
        TScreen_Send_Packet(TScreen_Send_Buffer);
}
void TScreen_Chang_Page(uinteg8_t U8_PageNum)
{
	TScreen_GenerateConfig_Status_Functions_packet(TScreen_Send_Buffer,DISP_PAGE,(uinteg64_t)U8_PageNum,T_SCREEN_VAR_SIZE_2);
	TScreen_Send_Packet(TScreen_Send_Buffer);
}
void TScreen_Write_Var16(uinteg16_t U16_Value,uinteg32_t Address)
{
	TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,N16_WRITE,Address,(uinteg16_t)U16_Value,T_SCREEN_VAR_SIZE_2);
	TScreen_Send_Packet(TScreen_Send_Buffer);

}
void TScreen_Write_Var32(uinteg16_t U32_Value,uinteg32_t Address)
{
	TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,N32_WRITE,Address,(uinteg16_t)U32_Value,T_SCREEN_VAR_SIZE_4);
	TScreen_Send_Packet(TScreen_Send_Buffer);

}





