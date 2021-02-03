/*
 * Switch.c
 *
 * Created: 7/2/2020 1:15:27 PM
 *  Author: HMI
 */




#include "Switch_LC.h"

#include "Timer.h"
#include "Timer_PostBConfig.h"
#include "DEBUG.h"

/*Definition of global variables*/
volatile uinteg8_t gau8_Switch_Sample_Closed_Count[NO_OF_SWITCHES]={0};
volatile uinteg8_t gau8_Switch_Last_Sample[NO_OF_SWITCHES]={0};
volatile uinteg8_t gau8_Switch_Last_State[NO_OF_SWITCHES]={0};
volatile uinteg8_t gau8_Switch_State[NO_OF_SWITCHES]={0};
volatile uinteg8_t sgu8_Switch_Pin=0;
/*Implementation of ISR*/
void Switch_Timer1_Isr(void)
{
/*	Debug_By_Toggle(13);*/
    static uinteg8_t su8_Delay_For_Deletion=4;
		   uinteg8_t u8_Buffer=0;
           uinteg8_t u8_Switch_Pin_Index=0;

	for(uinteg8_t u8_Switch_Pin_Index=0;u8_Switch_Pin_Index<NO_OF_SWITCHES;u8_Switch_Pin_Index++)
	{

		DIO_Read_Pin(gau8_Switches_Name[u8_Switch_Pin_Index],&u8_Buffer);

		if(      (gau8_Switch_Last_Sample[u8_Switch_Pin_Index]==SWITCH_IS_OPENED)  &&  (u8_Buffer==SWITCH_IS_CLOSED)  )
		{
			/*Debug_By_Toggle(18);*/
			gau8_Switch_Last_State[u8_Switch_Pin_Index]=SWITCH_STATE_NOT_CLICKED;
			gau8_Switch_Last_Sample[u8_Switch_Pin_Index]=SWITCH_IS_CLOSED;
			gau8_Switch_Sample_Closed_Count[u8_Switch_Pin_Index]++;
		}
		else if( (gau8_Switch_Last_Sample[u8_Switch_Pin_Index]==SWITCH_IS_CLOSED)  &&  (u8_Buffer==SWITCH_IS_CLOSED)  )
		{
		    /*Debug_By_Toggle(19);*/
			gau8_Switch_Last_Sample[u8_Switch_Pin_Index]=SWITCH_IS_CLOSED;
			gau8_Switch_Sample_Closed_Count[u8_Switch_Pin_Index]++;
			if(gau8_Switch_Sample_Closed_Count[u8_Switch_Pin_Index]>50)
			{

				/*su8_Delay_For_Deletion=5;*/
				gau8_Switch_State[u8_Switch_Pin_Index]=SWITCH_STATE_HOLD;
				gau8_Switch_Last_State[u8_Switch_Pin_Index]=SWITCH_STATE_HOLD;
				gau8_Switch_Sample_Closed_Count[u8_Switch_Pin_Index]=0;
			}
		}
		else if( (gau8_Switch_Last_Sample[u8_Switch_Pin_Index]==SWITCH_IS_CLOSED)  &&  (u8_Buffer==SWITCH_IS_OPENED)  )
		{
			/*Debug_By_Toggle(20);*/
			gau8_Switch_Last_Sample[u8_Switch_Pin_Index]=SWITCH_IS_OPENED;
			if((gau8_Switch_Sample_Closed_Count[u8_Switch_Pin_Index]>=2)&&(gau8_Switch_Sample_Closed_Count[u8_Switch_Pin_Index]<=30)&&(gau8_Switch_Last_State[u8_Switch_Pin_Index]==SWITCH_STATE_NOT_CLICKED))
			{

				su8_Delay_For_Deletion=2;
				gau8_Switch_State[u8_Switch_Pin_Index]=SWITCH_STATE_SINGLE_PUSH;
				gau8_Switch_Last_State[u8_Switch_Pin_Index]=SWITCH_STATE_SINGLE_PUSH;
			}
			gau8_Switch_Sample_Closed_Count[u8_Switch_Pin_Index]=0;

		}
		else if( (gau8_Switch_Last_Sample[u8_Switch_Pin_Index]==SWITCH_IS_OPENED)  &&  (u8_Buffer==SWITCH_IS_OPENED)  )
		{
			/*Debug_By_Toggle(21);*/

            /*
			if(su8_Delay_For_Deletion==0)
			{
				su8_Delay_For_Deletion--;
				gau8_Switch_State[u8_Switch_Pin_Index]=SWITCH_STATE_NOT_CLICKED;/ ** /
			}
			*/

            if(gau8_Switch_Last_State[u8_Switch_Pin_Index]==SWITCH_STATE_HOLD)
			{
				gau8_Switch_State[u8_Switch_Pin_Index]=SWITCH_STATE_NOT_CLICKED;
				gau8_Switch_Last_State[u8_Switch_Pin_Index]=SWITCH_STATE_NOT_CLICKED;

			}
			else if((gau8_Switch_Last_State[u8_Switch_Pin_Index]==SWITCH_STATE_SINGLE_PUSH)&&(su8_Delay_For_Deletion==0))
			{
				gau8_Switch_State[u8_Switch_Pin_Index]=SWITCH_STATE_NOT_CLICKED;
				gau8_Switch_Last_State[u8_Switch_Pin_Index]=SWITCH_STATE_NOT_CLICKED;

			}
			else if((gau8_Switch_Last_State[u8_Switch_Pin_Index]==SWITCH_STATE_SINGLE_PUSH)&&(su8_Delay_For_Deletion>0))
			{
				gau8_Switch_State[u8_Switch_Pin_Index]=SWITCH_STATE_NOT_CLICKED;
				gau8_Switch_Last_State[u8_Switch_Pin_Index]=SWITCH_STATE_NOT_CLICKED;
				su8_Delay_For_Deletion--;
			}
			gau8_Switch_Last_Sample[u8_Switch_Pin_Index]=SWITCH_IS_OPENED;
/*
			gau8_Switch_Last_State[u8_Switch_Pin_Index]=SWITCH_STATE_NOT_CLICKED;
			gau8_Switch_Last_Sample[u8_Switch_Pin_Index]=SWITCH_IS_OPENED;*/
		}
	}

}
/*Implementation of prototype*/
void Switch_Init(uinteg8_t u8_Pulled_Up)
{
    Timer_Init(&Switch_Timer_Init_Config);
	Timer_Start(Switch_Timer_Init_Config.Timer_Channel,78,&Switch_Timer1_Isr);

	for(uinteg8_t u8_Switch_Pin_Index=0;u8_Switch_Pin_Index<NO_OF_SWITCHES;u8_Switch_Pin_Index++)
	{
		DIO_Init_Pin(gau8_Switches_Name[u8_Switch_Pin_Index],INPUT,u8_Pulled_Up);
	    gau8_Switch_Last_Sample[u8_Switch_Pin_Index]=SWITCH_IS_OPENED;
	    gau8_Switch_Last_State[u8_Switch_Pin_Index]=SWITCH_STATE_NOT_CLICKED;
	}

}
void Switch_Read_Single_Sample(uinteg8_t u8_Switch_Pin,uinteg8_t* copy_of_address_of_Switch_State_Buffer)
{
	 DIO_Read_Pin(u8_Switch_Pin,copy_of_address_of_Switch_State_Buffer);
}
void Switch_Read(uinteg8_t u8_Copy_Switch_Pin , uinteg8_t*copy_of_address_of_Switch_State_Buffer)
{
     DisableGeneralInterrupt();
	 *copy_of_address_of_Switch_State_Buffer=gau8_Switch_State[u8_Copy_Switch_Pin];

	 if(gau8_Switch_State[u8_Copy_Switch_Pin]==SWITCH_STATE_SINGLE_PUSH)
	 {
		/*Debug_By_Toggle(22);*/
		gau8_Switch_State[u8_Copy_Switch_Pin]=SWITCH_STATE_NOT_CLICKED;
		gau8_Switch_Last_State[u8_Copy_Switch_Pin]=SWITCH_STATE_NOT_CLICKED;
	 }


     EnableGeneralInterrupt() ;
}
