/*- INCLUDES ----------------------------------------------*/
#include"Data_types.h"
#include<math.h>
#include "DEBUG.h"
/*- LOCAL MACROS ------------------------------------------*/
#define NEGATIVE_SIGN 0
#define POSTIVE_SIGN  1
/*- LOCAL Dataypes ----------------------------------------*/
/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
/*- GLOBAL STATIC VARIABLES -------------------------------*/
/*- GLOBAL EXTERN VARIABLES -------------------------------*/
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/*- APIs IMPLEMENTATION -----------------------------------*/

void TransformIntToString ( integ64_t Integr_Number, char *pntrToChar,char c_number_of_digits)
{
	unsigned char          Buffer_String[20]   = { 0 };
	unsigned char          Buffer_String_Index  = 0;
	unsigned char          Integer_String_Index = 0;


	if(Integr_Number==0)
	{
	    while(Integer_String_Index<c_number_of_digits)
	    {
		    pntrToChar[Integer_String_Index] = '0';
		    Integer_String_Index++;
	    }
	}
	else
	{

		if((Integr_Number&(0x80000000)))
		{
			Integr_Number = (~Integr_Number) + 1;
			pntrToChar[Integer_String_Index] ='-';
			Integer_String_Index++;
			c_number_of_digits--;
		}
		while(Integr_Number)
		{
			Buffer_String[Buffer_String_Index] = (Integr_Number % 10) + 48;
			Integr_Number = Integr_Number/10;
			Buffer_String_Index++;
		}
		while(Buffer_String_Index<c_number_of_digits)
		{
			c_number_of_digits--;
			pntrToChar[Integer_String_Index]='0';
			Integer_String_Index++;
		}
		while (Buffer_String_Index > 0)
		{
			Buffer_String_Index--;
			pntrToChar[Integer_String_Index] = Buffer_String[Buffer_String_Index];
			Integer_String_Index++;
		}
	}
	pntrToChar[Integer_String_Index] = 0;
	
	
}

void TransformFloatToString(double Float_Number,char How_Many_Sign_Before_Point,char How_Many_Sign_After_Point,char* pntrToChar)
{
	unsigned long long int Integer_Number_For_Float_String_Representation=(long long int)Float_Number;
	char                   Buffer_String[100]={0};
	int                    Buffer_String_Index=0;
	int                    Integer_String_Index=0;
	unsigned int           points_Number=0;
	double                 Float_Number_Buffer=0.0;
	Float_Number_Buffer=Float_Number;
	unsigned char          u_char_Total_Number_Of_Digits=How_Many_Sign_Before_Point+How_Many_Sign_After_Point+1;
	int                    Integer_Number_For_Float_String_Representation_buffer=0;
	if(Float_Number_Buffer<0)
	{
		Float_Number_Buffer*=-1.0;
	}
	do
	{
		Float_Number_Buffer*=10;
		Integer_Number_For_Float_String_Representation=Float_Number_Buffer;
		points_Number++;
	}while((points_Number!=How_Many_Sign_After_Point+1));
	
	points_Number--;
	Integer_Number_For_Float_String_Representation=Integer_Number_For_Float_String_Representation/10;

	Integer_Number_For_Float_String_Representation_buffer=Integer_Number_For_Float_String_Representation;
	

	while (Integer_Number_For_Float_String_Representation)
	{
		if(Buffer_String_Index==points_Number)
		{
			if(How_Many_Sign_After_Point!=0)
			{
				Buffer_String[Buffer_String_Index]='.';
				Buffer_String_Index++;
			}
			else
			{
				u_char_Total_Number_Of_Digits--;
			}
			
		}
		Buffer_String[Buffer_String_Index] = (Integer_Number_For_Float_String_Representation%10)+48 ;
		Integer_Number_For_Float_String_Representation= Integer_Number_For_Float_String_Representation/10;
		Buffer_String_Index++;
		
	}
	if(Float_Number<0)
	{
		pntrToChar[Integer_String_Index] = '-' ;
		Integer_String_Index++;
		How_Many_Sign_Before_Point--;
		u_char_Total_Number_Of_Digits-=1;
	}
	if((((int)(Float_Number))==0)&&(Integer_Number_For_Float_String_Representation_buffer!=0))
	{
		for(int i=0;i<How_Many_Sign_Before_Point;i++)
		{
			pntrToChar[Integer_String_Index++]='0';
			u_char_Total_Number_Of_Digits--;
		}
		if(How_Many_Sign_After_Point!=0)
		{
			Buffer_String[Buffer_String_Index]='.';
			Buffer_String_Index++;
		}
		else
		{
			u_char_Total_Number_Of_Digits--;
		}
		


	}

	while((u_char_Total_Number_Of_Digits>Buffer_String_Index)&&(Integer_String_Index!=0))
	{
		pntrToChar[Integer_String_Index] = '0' ;
		Integer_String_Index++;
		u_char_Total_Number_Of_Digits--;

	}
	while(Buffer_String_Index>0)
	{
		Buffer_String_Index--;
		pntrToChar[Integer_String_Index]=Buffer_String[Buffer_String_Index];
		Integer_String_Index++;
	}
	if(Integer_String_Index==0)
	{
		for(int i=0;i<How_Many_Sign_Before_Point;i++)
		{
			pntrToChar[Integer_String_Index++]='0';
		}
		if(How_Many_Sign_After_Point!=0)
		{
			pntrToChar[Integer_String_Index++]='.';
		}

		for(int i=0;i<How_Many_Sign_After_Point;i++)
		{
			pntrToChar[Integer_String_Index++]='0';
		}
		
	}
	pntrToChar[Integer_String_Index]=0;
}
