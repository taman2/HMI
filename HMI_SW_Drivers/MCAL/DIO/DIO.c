/*
 * DIO.c
 *
 * Created: 02/11/2019 00:35:26
 *  Author: HMI
 */
#include "DIO.h"
#include "Math.h"

uinteg8_t DIO_Init_Part_In_Port(uinteg8_t Port_Name,uinteg8_t Port_From,uinteg8_t Port_To,uinteg8_t Value)
{
	uinteg64_t u64_Value=1;

	if(Value==OUTPUT)
	{
		Power_For_Two(&u64_Value,(uinteg8_t)(Port_To-Port_From+1));
		Value=(char)(u64_Value-1U);
	}
	switch(Port_Name)
	{


		#if (ATMEGA!= 8)

			case 'A':

				SET_VAlUE_IN_POSTION_FROM_tO(Port_From,Port_To,DirectionRegisterA,Value);

			break;

		#endif

			case 'B':

				SET_VAlUE_IN_POSTION_FROM_tO(Port_From,Port_To,DirectionRegisterB,Value);

			break;

			case 'C':

				SET_VAlUE_IN_POSTION_FROM_tO(Port_From,Port_To,DirectionRegisterC,Value);

			break;

			case 'D':

				SET_VAlUE_IN_POSTION_FROM_tO(Port_From,Port_To,DirectionRegisterD,Value);

			break;

		#if ATMEGA == 128

			case 'E':

				SET_VAlUE_IN_POSTION_FROM_tO(Port_From,Port_To,DirectionRegisterE,Value);

			break;

			case 'F':

				SET_VAlUE_IN_POSTION_FROM_tO(Port_From,Port_To,DirectionRegisterF,Value);

			break;

			case 'G':

				SET_VAlUE_IN_POSTION_FROM_tO(Port_From,Port_To,DirectionRegisterG,Value);

			break;

		#endif

		default :

		return DIO_ERROR_NOK;

		break;
	}

	return DIO_ERROR_OK;

}
uinteg8_t DIO_Init_PORT(uinteg8_t Port_Name,uinteg8_t direction)
{


    switch(Port_Name)
    {
    #if (ATMEGA!= 8)

    case 'A':
       if(direction==0)
	   {
		   DirectionRegisterA=0x00;}else{DirectionRegisterA=0xFF;}
    break;
	#endif

    case 'B':
        if(direction==0){DirectionRegisterB=0x00;}else{DirectionRegisterB=0xFF;}
        break;

    case 'C':
        if(direction==0){DirectionRegisterC=0x00;}else{DirectionRegisterC=0xFF;}
        break;

    case 'D':
        if(direction==0){DirectionRegisterD=0x00;}else{DirectionRegisterD=0xFF;}
        break;
#if ATMEGA == 128
	case 'E':
		if(direction==0){DDRE=0x00;}else{DDRE=0xFF;}
		break;
	case 'F':
		if(direction==0){DDRF=0x00;}else{DDRF=0xFF;}
		break;
	case 'G':
		if(direction==0){DDRG=0x00;}else{DDRG=0xFF;}
		break;
#endif
    default :
	           return DIO_ERROR_OK;
        break;
    }
	return DIO_ERROR_OK;
}
uinteg8_t DIO_Init_Nibble(uinteg8_t por,uinteg8_t nibble,uinteg8_t direction)
{
	switch(por)
	{
	#if (ATMEGA!= 8)


	case 'A': if (nibble==LOWER_NIBBLE)
               {
					  if(direction==INPUT)
					  {
						  CLR_LOWER_NIBBLE(DirectionRegisterA);
					  }
					  else if(direction==OUTPUT)
					  {
						  SET_LOWER_NIBBLE(DirectionRegisterA);
					  }
			   }
			   else if(nibble==HIGHER_NIBBLE)
			   {
				      if(direction==INPUT)
				      {
					      CLR_HIGHER_NIBBLE(DirectionRegisterA);
				      }
				      else if(direction==OUTPUT)
				      {
					      SET_HIGHER_NIBBLE(DirectionRegisterA);
				      }
			   }
	          break;
    #endif
    case 'B': if (nibble==LOWER_NIBBLE)
			  {
					if(direction==INPUT)
					{
						CLR_LOWER_NIBBLE(DirectionRegisterB);
					}
					else if(direction==OUTPUT)
					{
						SET_LOWER_NIBBLE(DirectionRegisterB);
					}
			  }
			else if(nibble==HIGHER_NIBBLE)
			{
					if(direction==INPUT)
					{
						CLR_HIGHER_NIBBLE(DirectionRegisterB);
					}
					else if(direction==OUTPUT)
					{
						SET_HIGHER_NIBBLE(DirectionRegisterB);
					}
			}
              break;

    case 'C':  if (nibble==LOWER_NIBBLE)
	         {
		         if(direction==INPUT)
		         {
			         CLR_LOWER_NIBBLE(DirectionRegisterC);
		         }
		         else if(direction==OUTPUT)
		         {
			         SET_LOWER_NIBBLE(DirectionRegisterC);
		         }
	         }
	         else if(nibble==HIGHER_NIBBLE)
	         {
		         if(direction==INPUT)
		         {
			         CLR_HIGHER_NIBBLE(DirectionRegisterC);
		         }
		         else if(direction==OUTPUT)
		         {
			         SET_HIGHER_NIBBLE(DirectionRegisterC);
		         }
	         }
              break;

    case 'D': if (nibble==LOWER_NIBBLE)
	          {
		          if(direction==INPUT)
		          {
			          CLR_LOWER_NIBBLE(DirectionRegisterD);
		          }
		          else if(direction==OUTPUT)
		          {
			          SET_LOWER_NIBBLE(DirectionRegisterD);
		          }
	          }
	          else if(nibble==HIGHER_NIBBLE)
	          {
		          if(direction==INPUT)
		          {
			          CLR_HIGHER_NIBBLE(DirectionRegisterD);
		          }
		          else if(direction==OUTPUT)
		          {
			          SET_HIGHER_NIBBLE(DirectionRegisterD);
		          }
	          }
			  break;
#if ATMEGA == 128
	    case 'E': if (nibble==LOWER_NIBBLE)
	    {
		    if(direction==INPUT)
		    {
			    CLR_LOWER_NIBBLE(DDRE);
		    }
		    else if(direction==OUTPUT)
		    {
			    SET_LOWER_NIBBLE(DDRE);
		    }
	    }
	    else if(nibble==HIGHER_NIBBLE)
	    {
		    if(direction==INPUT)
		    {
			    CLR_HIGHER_NIBBLE(DDRE);
		    }
		    else if(direction==OUTPUT)
		    {
			    SET_HIGHER_NIBBLE(DDRE);
		    }
	    }
	    break;
	    case 'F': if (nibble==LOWER_NIBBLE)
	    {
		    if(direction==INPUT)
		    {
			    CLR_LOWER_NIBBLE(DDRF);
		    }
		    else if(direction==OUTPUT)
		    {
			    SET_LOWER_NIBBLE(DDRF);
		    }
	    }
	    else if(nibble==HIGHER_NIBBLE)
	    {
		    if(direction==INPUT)
		    {
			    CLR_HIGHER_NIBBLE(DDRF);
		    }
		    else if(direction==OUTPUT)
		    {
			    SET_HIGHER_NIBBLE(DDRF);
		    }
	    }
	    break;
	    case 'G': if (nibble==LOWER_NIBBLE)
	    {
		    if(direction==INPUT)
		    {
			    CLR_LOWER_NIBBLE(DDRG);
		    }
		    else if(direction==OUTPUT)
		    {
			    SET_LOWER_NIBBLE(DDRG);
		    }
	    }
	    else if(nibble==HIGHER_NIBBLE)
	    {
		    if(direction==INPUT)
		    {
			    CLR_HIGHER_NIBBLE(DDRG);
		    }
		    else if(direction==OUTPUT)
		    {
			    SET_HIGHER_NIBBLE(DDRG);
		    }
	    }
	    break;
#endif
		default :
		return DIO_ERROR_NOK;
		break;
}
return DIO_ERROR_OK;
}
uinteg8_t DIO_Init_Pin(uinteg8_t pin, uinteg8_t direction,uinteg8_t u8_Pull_up)
{
	uinteg8_t por;

	if(pin>=PinsNeeded || pin>=No_of_pins ) return DIO_ERROR_NOK;
    else
	{

		#if (ATMEGA!= 8)

			por='A'+pin/PortSize;
			pin=pin%PortSize;

		#else

			por='B'+pin/PortSize;
			pin=pin%PortSize;

		#endif
	}

    switch(por)
    {
			#if (ATMEGA!= 8)

			case 'A':
			{
					if(direction==INPUT)
					{
						CLR_BIT(DirectionRegisterA,pin);
						if(u8_Pull_up==DIO_PIN_PULLED_UP)SET_BIT(WriteRegisterA,pin);
					}
					else
					{
						SET_BIT(DirectionRegisterA,pin);
					}
			}
			break;

			#endif

			case 'B':
			{
					if(direction==INPUT)
					{
						CLR_BIT(DirectionRegisterB,pin);
						if(u8_Pull_up==DIO_PIN_PULLED_UP)SET_BIT(WriteRegisterB,pin);
					}
					else
					{
						SET_BIT(DirectionRegisterB,pin);
					}
			}
			break;

			case 'C':
			{
				if(direction==INPUT)
				{
					CLR_BIT(DirectionRegisterC,pin);
					if(u8_Pull_up==DIO_PIN_PULLED_UP)SET_BIT(WriteRegisterC,pin);
				}
				else
				{
					SET_BIT(DirectionRegisterC,pin);
				}
			}
			break;


			case 'D':
			{
				if(direction==INPUT)
				{
					CLR_BIT(DirectionRegisterD,pin);
					if(u8_Pull_up==DIO_PIN_PULLED_UP)SET_BIT(WriteRegisterD,pin);
				}
				else
				{
					SET_BIT(DirectionRegisterD,pin);
				}
			}
			break;
		#if ATMEGA == 128

			case 'E': if(direction==INPUT){CLR_BIT(DirectionRegisterE,pin);if(u8_Pull_up==DIO_PIN_PULLED_UP)SET_BIT(WriteRegisterE,pin);}else{SET_BIT(DDRE,pin);}
					  break;
			case 'F': if(direction==INPUT){CLR_BIT(DirectionRegisterF,pin);if(u8_Pull_up==DIO_PIN_PULLED_UP)SET_BIT(WriteRegisterF,pin);}else{SET_BIT(DDRF,pin);}
					  break;
			case 'G': if(direction==INPUT){CLR_BIT(DirectionRegisterG,pin);if(u8_Pull_up==DIO_PIN_PULLED_UP)SET_BIT(WriteRegisterG,pin);}else{SET_BIT(DDRG,pin);}
					  break;
		#endif
			default :
			return DIO_ERROR_NOK;
			break;
	}

return DIO_ERROR_OK;
}
uinteg8_t DIO_Read_Port (uinteg8_t por, uinteg8_t * ReadData)
{
    switch(por)
    {
	#if (ATMEGA!= 8)
    case 'A': * ReadData=WriteRegisterA;
              break;
	#endif
    case 'B': * ReadData=WriteRegisterB;
              break;

    case 'C': * ReadData=WriteRegisterC;
              break;

    case 'D': * ReadData=WriteRegisterD;
			  break;

#if ATMEGA == 128

	case 'E': * ReadData=PORTE;
			  break;

	case 'F': * ReadData=PORTF;
			  break;

	case 'G': * ReadData=PORTG;
			  break;
#endif

    default : return DIO_ERROR_NOK;
              break;
    }
	return DIO_ERROR_OK;
}
uinteg8_t DIO_Write_Port(uinteg8_t por,uinteg8_t Data)
{
    switch(por)
    {
	#if (ATMEGA!= 8)

    case 'A': WriteRegisterA=Data;
			  break;
	#endif
    case 'B': WriteRegisterB=Data;
              break;

    case 'C': WriteRegisterC=Data;
              break;

    case 'D': WriteRegisterD=Data;
              break;

#if ATMEGA == 128

	case 'E': PORTE=Data;
			  break;
	case 'F': PORTF=Data;
			  break;
	case 'G': PORTG=Data;
			  break;
	#endif
	default :
	return DIO_ERROR_NOK;
	break;
	}
return DIO_ERROR_OK;
}
uinteg8_t DIO_Read_Pin (uinteg8_t pin, uinteg8_t * ReadData)
{
	uinteg8_t por;
	if(pin>=PinsNeeded || pin>=No_of_pins ) return DIO_ERROR_NOK;
	else
	{
		#if (ATMEGA!= 8)
		por='A'+pin/PortSize;
		pin=pin%PortSize;
		#else
		por='B'+pin/PortSize;
		pin=pin%PortSize;
		#endif
	}

    switch(por)
    {
	#if (ATMEGA!= 8)
   case 'A':  * ReadData=GET_BIT(ReadRegisterA,pin);
              break;
   #endif
    case 'B': * ReadData=GET_BIT(ReadRegisterB,pin);
			  break;

    case 'C': * ReadData=GET_BIT(ReadRegisterC,pin);
              break;

	case 'D': * ReadData=GET_BIT(ReadRegisterD,pin);
	          break;
#if ATMEGA == 128


	case 'E': * ReadData=GET_BIT(PINE,pin);
			  break;
	case 'F': * ReadData=GET_BIT(PINF,pin);
			  break;
	case 'G': * ReadData=GET_BIT(PING,pin);
			  break;

	#endif
	default :
	return DIO_ERROR_NOK;
	break;
	}
return DIO_ERROR_OK;
}
uinteg8_t DIO_Write_Pin(uinteg8_t pin,uinteg8_t BitValue)
{
	uinteg8_t por;
 	if(pin>=PinsNeeded || pin>=No_of_pins ) return DIO_ERROR_NOK;
 	else
 	{
		#if (ATMEGA!= 8)
		por='A'+pin/PortSize;
		pin=pin%PortSize;
		#else
		por='B'+pin/PortSize;
		pin=pin%PortSize;
		#endif
 	}

    switch(por)
    {
	#if (ATMEGA!= 8)
   case 'A': if(BitValue==0){CLR_BIT(WriteRegisterA,pin);}else{SET_BIT(WriteRegisterA,pin);}
              break;
   #endif
    case 'B': if(BitValue==0){CLR_BIT(WriteRegisterB,pin);}else{SET_BIT(WriteRegisterB,pin);}
              break;

    case 'C': if(BitValue==0){CLR_BIT(WriteRegisterC,pin);}else{SET_BIT(WriteRegisterC,pin);}
              break;

    case 'D': if(BitValue==0){CLR_BIT(WriteRegisterD,pin);}else{SET_BIT(WriteRegisterD,pin);}
              break;

#if ATMEGA == 128

	case 'E': if(BitValue==0){CLR_BIT(PORTE,pin);}else{SET_BIT(PORTE,pin);}
			  break;

	case 'F': if(BitValue==0){CLR_BIT(PORTF,pin);}else{SET_BIT(PORTF,pin);}
			  break;

	case 'G': if(BitValue==0){CLR_BIT(PORTG,pin);}else{SET_BIT(PORTG,pin);}
			  break;

	#endif
	default :
	return DIO_ERROR_NOK;
	break;
	}
	return DIO_ERROR_OK;
}
uinteg8_t DIO_toggle_Port(uinteg8_t por)
{
	switch(por)
	{
	    #if (ATMEGA!= 8)
		case 'A':TOGGLE_PORT(WriteRegisterA);
			  break;
	    #endif
		case 'B':TOGGLE_PORT(WriteRegisterB);
		      break;
		case 'C':TOGGLE_PORT(WriteRegisterC);
			  break;
		case 'D':TOGGLE_PORT(WriteRegisterD);
		      break;
		#if ATMEGA == 128
		case 'E':TOGGLE_PORT(PORTE);
			  break;
		case 'F':TOGGLE_PORT(PORTF);
			 break;
		case 'G':TOGGLE_PORT(PORTG);
			 break;
		#endif
		default :
		return DIO_ERROR_NOK;
		break;
		}
return DIO_ERROR_OK;
}
uinteg8_t DIO_toggle_Pin(uinteg8_t pin)
{
	uinteg8_t por;
	if(pin>=PinsNeeded || pin>=No_of_pins ) return DIO_ERROR_NOK;
	else
	{
		#if (ATMEGA!= 8)
		por='A'+pin/PortSize;
		pin=pin%PortSize;
		#else
		por='B'+pin/PortSize;
		pin=pin%PortSize;
		#endif
	}

	switch(por)
	{
		#if (ATMEGA!= 8)
		case 'A':TOGGLE_BIT(WriteRegisterA,pin);
			 break;
		#endif
		case 'B':TOGGLE_BIT(WriteRegisterB,pin);
			 break;
		case 'C':TOGGLE_BIT(WriteRegisterC,pin);
			 break;
		case 'D':TOGGLE_BIT(WriteRegisterD,pin);
			 break;
#if ATMEGA == 128
		case 'E':TOGGLE_BIT(PORTE,pin);
			 break;
		case 'F':TOGGLE_BIT(PORTF,pin);
			 break;
		case 'G':TOGGLE_BIT(PORTG,pin);
			 break;
#endif
		default :
		return DIO_ERROR_NOK;
		break;

	}
	return DIO_ERROR_OK;
}
uinteg8_t DIO_Read_Nibble(uinteg8_t por,uinteg8_t nibble,uinteg8_t shifted_left_or_not,uinteg8_t * ReadData)
{
	switch(por)
	{
		#if (ATMEGA!= 8)
		case 'A': if (nibble==HIGHER_NIBBLE)
					{
			          if (shifted_left_or_not==NOT_SHIFTED)
			          {
						  *ReadData=GET_HIGHER_NIBBLE_AT_LOW_BITS(WriteRegisterA);
			          }
					  else if(shifted_left_or_not==SHIFTED_LEFT)
					  {
						  *ReadData=GET_HIGHER_NIBBLE_AT_HIGH_BITS(WriteRegisterA);
					  }
					}
					else if (nibble==LOWER_NIBBLE)
					{
						if(shifted_left_or_not==NOT_SHIFTED)
						 {
							 *ReadData=GET_LOWER_NIBBLE_AT_LOW_BITS(WriteRegisterA);
						 }
						 else if(shifted_left_or_not==SHIFTED_LEFT)
						 {
							 *ReadData=GET_LOWER_NIBBLE_AT_HIGH_BITS(WriteRegisterA);
						 }
					}
		break;
       #endif
		case 'B': if (nibble==HIGHER_NIBBLE)
		{
			if (shifted_left_or_not==NOT_SHIFTED)
			{
				*ReadData=GET_HIGHER_NIBBLE_AT_LOW_BITS(WriteRegisterB);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				*ReadData=GET_HIGHER_NIBBLE_AT_HIGH_BITS(WriteRegisterB);
			}
		}
		else if (nibble==LOWER_NIBBLE)
		{
			if(shifted_left_or_not==NOT_SHIFTED)
			{
				*ReadData=GET_LOWER_NIBBLE_AT_LOW_BITS(WriteRegisterB);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				*ReadData=GET_LOWER_NIBBLE_AT_HIGH_BITS(WriteRegisterB);
			}
		}
		break;

		case 'C': if (nibble==HIGHER_NIBBLE)
		{
			if (shifted_left_or_not==NOT_SHIFTED)
			{
				*ReadData=GET_HIGHER_NIBBLE_AT_LOW_BITS(WriteRegisterC);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				*ReadData=GET_HIGHER_NIBBLE_AT_HIGH_BITS(WriteRegisterC);
			}
		}
		else if (nibble==LOWER_NIBBLE)
		{
			if(shifted_left_or_not==NOT_SHIFTED)
			{
				*ReadData=GET_LOWER_NIBBLE_AT_LOW_BITS(WriteRegisterC);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				*ReadData=GET_LOWER_NIBBLE_AT_HIGH_BITS(WriteRegisterC);
			}
		}
		break;

		case 'D': if (nibble==HIGHER_NIBBLE)
		{
			if (shifted_left_or_not==NOT_SHIFTED)
			{
				*ReadData=GET_HIGHER_NIBBLE_AT_LOW_BITS(WriteRegisterD);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				*ReadData=GET_HIGHER_NIBBLE_AT_HIGH_BITS(WriteRegisterD);
			}
		}
		else if (nibble==LOWER_NIBBLE)
		{
			if(shifted_left_or_not==NOT_SHIFTED)
			{
				*ReadData=GET_LOWER_NIBBLE_AT_LOW_BITS(WriteRegisterD);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				*ReadData=GET_LOWER_NIBBLE_AT_HIGH_BITS(WriteRegisterD);
			}
		}
		break;

		#if ATMEGA == 128

		case 'E': if (nibble==HIGHER_NIBBLE)
		{
			if (shifted_left_or_not==NOT_SHIFTED)
			{
				*ReadData=GET_HIGHER_NIBBLE_AT_LOW_BITS(PORTE);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				*ReadData=GET_HIGHER_NIBBLE_AT_HIGH_BITS(PORTE);
			}
		}
		else if (nibble==LOWER_NIBBLE)
		{
			if(shifted_left_or_not==NOT_SHIFTED)
			{
				*ReadData=GET_LOWER_NIBBLE_AT_LOW_BITS(PORTE);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				*ReadData=GET_LOWER_NIBBLE_AT_HIGH_BITS(PORTE);
			}
		}
		break;

		case 'F': if (nibble==HIGHER_NIBBLE)
		{
			if (shifted_left_or_not==NOT_SHIFTED)
			{
				* ReadData=GET_HIGHER_NIBBLE_AT_LOW_BITS(PORTF);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				*ReadData=GET_HIGHER_NIBBLE_AT_HIGH_BITS(PORTF);
			}
		}
		else if (nibble==LOWER_NIBBLE)
		{
			if(shifted_left_or_not==NOT_SHIFTED)
			{
				*ReadData=GET_LOWER_NIBBLE_AT_LOW_BITS(PORTF);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				*ReadData=GET_LOWER_NIBBLE_AT_HIGH_BITS(PORTF);
			}
		}
		break;

		case 'G': if (nibble==HIGHER_NIBBLE)
		{
			if (shifted_left_or_not==NOT_SHIFTED)
			{
				*ReadData=GET_HIGHER_NIBBLE_AT_LOW_BITS(PORTG);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				*ReadData=GET_HIGHER_NIBBLE_AT_HIGH_BITS(PORTG);
			}
		}
		else if (nibble==LOWER_NIBBLE)
		{
			if(shifted_left_or_not==NOT_SHIFTED)
			{
				* ReadData=GET_LOWER_NIBBLE_AT_LOW_BITS(PORTG);
			}
			else if(shifted_left_or_not==SHIFTED_LEFT)
			{
				* ReadData=GET_LOWER_NIBBLE_AT_HIGH_BITS(PORTG);
			}
		}
		break;
		#endif

		default :
		return DIO_ERROR_NOK;
		break;

	}
	return DIO_ERROR_OK;
}

uinteg8_t DIO_Write_Nibble(uinteg8_t por ,uinteg8_t lower_or_higher_nibble,uinteg8_t data)
{
	switch(por)
	{
		#if (ATMEGA!= 8)

				case 'A':
							if (lower_or_higher_nibble==LOWER_NIBBLE)
							{
								SET_VAlUE_IN_POSTION_FROM_tO(0,3,WriteRegisterA,data);
							}
							else if(lower_or_higher_nibble==HIGHER_NIBBLE)
							{
								SET_VAlUE_IN_POSTION_FROM_tO(4,7,WriteRegisterA,data);
							}
				break;

		#endif

				case 'B':

				if (lower_or_higher_nibble==LOWER_NIBBLE)
				{
					SET_VAlUE_IN_POSTION_FROM_tO(0,3,WriteRegisterB,data);
				}
				else if(lower_or_higher_nibble==HIGHER_NIBBLE)
				{
					SET_VAlUE_IN_POSTION_FROM_tO(4,7,WriteRegisterB,data);
				}

				break;

				case 'C':

						if (lower_or_higher_nibble==LOWER_NIBBLE)
						{
							SET_VAlUE_IN_POSTION_FROM_tO(0,3,WriteRegisterC,data);
						}
						else if(lower_or_higher_nibble==HIGHER_NIBBLE)
						{
							SET_VAlUE_IN_POSTION_FROM_tO(4,7,WriteRegisterC,data);
						}
				break;

				case 'D':

						if (lower_or_higher_nibble==LOWER_NIBBLE)
						{
							SET_VAlUE_IN_POSTION_FROM_tO(0,3,WriteRegisterD,data);
						}
						else if(lower_or_higher_nibble==HIGHER_NIBBLE)
						{
							SET_VAlUE_IN_POSTION_FROM_tO(4,7,WriteRegisterD,data);
						}
				break;

        #if ATMEGA == 128

				case 'E':

						if (lower_or_higher_nibble==LOWER_NIBBLE)
						{
							SET_VAlUE_IN_POSTION_FROM_tO(0,3,WriteRegisterE,data);
						}
						else if(lower_or_higher_nibble==HIGHER_NIBBLE)
						{
							SET_VAlUE_IN_POSTION_FROM_tO(4,7,WriteRegisterE,data);
						}
				break;

				case 'F':

						if (lower_or_higher_nibble==LOWER_NIBBLE)
						{
							SET_VAlUE_IN_POSTION_FROM_tO(0,3,WriteRegisterF,data);
						}
						else if(lower_or_higher_nibble==HIGHER_NIBBLE)
						{
							SET_VAlUE_IN_POSTION_FROM_tO(4,7,WriteRegisterF,data);
						}

				break;

				case 'G':

						if (lower_or_higher_nibble==LOWER_NIBBLE)
						{
							SET_VAlUE_IN_POSTION_FROM_tO(0,3,WriteRegisterG,data);
						}
						else if(lower_or_higher_nibble==HIGHER_NIBBLE)
						{
							SET_VAlUE_IN_POSTION_FROM_tO(4,7,WriteRegisterG,data);
						}

				break;
		#endif

				default :
						return DIO_ERROR_NOK;
				break;
		}

		return DIO_ERROR_OK;
}
/*
	#define SET_VAlUE_IN_POSTION_FROM_tO(i,j,REG,VALUE) REG=(  ( (~((~( 0XFF<<(j-i+1) ))<<i))&REG ) |   (VALUE<<i) )
*/
uinteg8_t DIO_Write_Part_In_Port(uinteg8_t Port_Name,uinteg8_t Port_From,uinteg8_t Port_To,uinteg8_t Value)
{
	switch(Port_Name)
	{
		#if (ATMEGA!= 8)

		case 'A':

			SET_VAlUE_IN_POSTION_FROM_tO(Port_From,Port_To,WriteRegisterA,Value);

		break;

		#endif

		case 'B':

			SET_VAlUE_IN_POSTION_FROM_tO(Port_From,Port_To,WriteRegisterB,Value);

		break;

		case 'C':

			SET_VAlUE_IN_POSTION_FROM_tO(Port_From,Port_To,WriteRegisterC,Value);

		break;

		case 'D':

			SET_VAlUE_IN_POSTION_FROM_tO(Port_From,Port_To,WriteRegisterD,Value);

		break;

		#if ATMEGA == 128

		case 'E':

			SET_VAlUE_IN_POSTION_FROM_tO(Port_From,Port_To,WriteRegisterE,Value);

		break;

		case 'F':

			SET_VAlUE_IN_POSTION_FROM_tO(Port_From,Port_To,WriteRegisterF,Value);

		break;

		case 'G':

			SET_VAlUE_IN_POSTION_FROM_tO(Port_From,Port_To,WriteRegisterG,Value);

		break;

		#endif

		default :

		return DIO_ERROR_NOK;

		break;
	}

	return DIO_ERROR_OK;
}
