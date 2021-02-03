/*
 * Rotary_Encoder.c
 *
 * Created: 12/31/2020 4:18:16 PM
 *  Author: Mohamed Salah Taman
 */ 
#include "Rotary_Encoder_Design.h"
#include "external_Interrupts.h"
#include "TOUCH_SCREEN.h"

volatile uinteg8_t U8_Rotary_Incoder_Direction=0;
volatile int U8_Rotary_Incoder_Counter=0;
volatile uinteg8_t U8_Rotary_Incoder_OK_Button_Flag=0;
volatile uinteg8_t Rotary_flag=0;
void Rotary_Incoder_Init(struct ROTARY_Config CONFIG){

/*set PD2 and PD3 as input*/
	DDRD &=~ (1 << PD2);				/* PD2 , PD3 & PB2 as input */
	DDRD &=~ (1 << PD3);
	clearBit(PORTB,PB2);
	PORTD |= (1 << PD3)|(1 << PD2)|(1<<PB2);   /* PB2, PD2 and PD3 pull-up enabled   */
    External_Interrupts_Init(2,FALLING_EDGE ,Rotary_Encoder_Ok_IsPressed);
	if(CONFIG.ROTARY_OPERATION_MODE==INTERRUP_MODE)
	{
		if(CONFIG.ROTARY_RESOLUTION== HALF_RESOLUTION)
		{
			/*use one interrupt connected to pinA of rotary encoder*/
			 External_Interrupts_Init(0,FALLING_EDGE ,Rotary_Incoder_DirectionINT0);
		}
		else
		{
			External_Interrupts_Init(0,FALLING_EDGE ,Rotary_Incoder_DirectionINT0);
			External_Interrupts_Init(1,FALLING_EDGE ,Rotary_Incoder_DirectionINT1);
		}
		
	}
	else
	{
        /*using interrupt mode more accurate and configurable to many applications */  	
    }
}
void Rotary_Incoder_DirectionINT0(void)
{

		if(!GET_BIT(PIND,PD3))
		{
			U8_Rotary_Incoder_Direction=CLK_WISE;
			U8_Rotary_Incoder_Counter++;
		}
		else
		{
			 U8_Rotary_Incoder_Direction=C_CLK_WISE;
			 U8_Rotary_Incoder_Counter--;

		}
		Rotary_flag=1;

		/*TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,N32_WRITE,T_SCREEN_VAR32_ADDRESS6,
		(int)U8_Rotary_Incoder_Counter,T_SCREEN_VAR_SIZE_4);
		TScreen_Send_Packet(TScreen_Send_Buffer);*/

}
void Rotary_Incoder_DirectionINT1(void)
{

	if(GET_BIT(PIND,PD2))
	{
		U8_Rotary_Incoder_Direction=CLK_WISE;
		U8_Rotary_Incoder_Counter++;
	}
	else
	{
		U8_Rotary_Incoder_Direction=C_CLK_WISE;
		U8_Rotary_Incoder_Counter--;

	}
			Rotary_flag=1;


			/*TScreen_Generate_VpFunctions_packet(TScreen_Send_Buffer,N32_WRITE,T_SCREEN_VAR32_ADDRESS6,
			(int)U8_Rotary_Incoder_Counter,T_SCREEN_VAR_SIZE_4);
			TScreen_Send_Packet(TScreen_Send_Buffer);*/

	
}
void Rotary_Encoder_Ok_IsPressed(void)
{
	U8_Rotary_Incoder_OK_Button_Flag=1;
}