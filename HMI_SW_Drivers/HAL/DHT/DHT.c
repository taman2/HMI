
/* DHT.c
*
* Created: 10/14/2020 1:38:52 AM
*  Author: HMI
*/

/**********Macros**************/
#define  F_CPU 16000000UL
#include <util/delay.h>
#include "Data_Types.h"
#include "DIO.h"
#include "DHT.h"
#include "DHT_Config.h"
#include "Lcd.h"
/***This is a local function can't call outside it waits for the pin until the state
passes or the time passes and it also returns the count that represents the state hold
time in micro**/

/****************************************************************************************
Parameters
--------------
u8_DHT_Pin-> the pin that you are going to do in it the processing(Type->uinteg8_t)
u16_DHT_Pin_State-> the current state that we want to make in it the hold(Type->uinteg16_t)
u16_DHT_Wait_Time-> the time of hold (Type->uinteg8_t)
uinteg8_t volatile* volatile u8_Count_Reached_To_Stop->pass to it the buffer that you
the function is going to put on it the count of hold on state(Pointer to uinteg8_t)

******************************************************************************************/
static void DHT_Wait_While_Certain_Pin_State_And_Time_Do_Not_Reach(uinteg8_t u8_DHT_Pin,uinteg16_t u16_DHT_Pin_State,uinteg16_t u16_DHT_Wait_Time,uinteg8_t volatile* volatile u8_Count_Reached_To_Stop)
{
uinteg8_t u8_DHT_Wait_While_Pin_State_And_Time_Is_Pin_State;
uinteg16_t u16_DHT_Counter=0;

DIO_Read_Pin(u8_DHT_Pin,&u8_DHT_Wait_While_Pin_State_And_Time_Is_Pin_State);

u16_DHT_Counter=0;
while((u8_DHT_Wait_While_Pin_State_And_Time_Is_Pin_State==u16_DHT_Pin_State)&&(u16_DHT_Counter<u16_DHT_Wait_Time))
{
u16_DHT_Counter++;
DIO_Read_Pin(u8_DHT_Pin,&u8_DHT_Wait_While_Pin_State_And_Time_Is_Pin_State);
}
*u8_Count_Reached_To_Stop=u16_DHT_Counter;


/* check received bit 0 or 1 */
}

/****************************************************************************************
This is a Local function used to request from DHT22 to respond and start transmission
operation
****************************************************************************************/
/****************************************************************************************
Parameters
--------------
u8_DHT_Pin-> It the pin of the DHT  that done over it the operation
*******************************************************************************************/
void DHT_Request(uinteg8_t u8_DHT_Pin)
{

DIO_Init_Pin(u8_DHT_Pin,OUTPUT,DIO_PIN_OUTPUT);
DIO_Write_Pin(u8_DHT_Pin,LOW);  /* set to low pin */
_delay_ms(1);        /* wait for 1ms  */
DIO_Init_Pin(u8_DHT_Pin,INPUT,DIO_PIN_LEFT_FLOAT);
}
/****************************************************************************************
This is a Local function that respond to the request where it returns the respond
****************************************************************************************/
/****************************************************************************************
Parameters
--------------
u8_DHT_Pin-> It the pin of the DHT  that done over it the operation(uinteg8_t)
pu8_DHT_Response_State->(Pointer to uinteg8_t) where the respond is returned in it
----------
Responds:
----------
1-DHT_NO_ERROR -> The bus is ok and the node is connected
2-DHT_NO_RESPONSE_ON_THE_BUS -> The node is not connected to the bus
*******************************************************************************************/
static void DHT_Response(uinteg8_t u8_DHT_Pin,uinteg8_t* pu8_DHT_Response_State)                                    /* receive response from DHT11 */
{
uinteg16_t u16_DHT_Response_Count=0;
*pu8_DHT_Response_State=DHT_NO_ERROR;


DHT_Wait_While_Certain_Pin_State_And_Time_Do_Not_Reach(u8_DHT_Pin,HIGH,DHT_MAX_TIME_US_TO_WAIT,&u16_DHT_Response_Count);
if(u16_DHT_Response_Count!=0)
{

DHT_Wait_While_Certain_Pin_State_And_Time_Do_Not_Reach(u8_DHT_Pin,LOW,DHT_MAX_TIME_US_TO_WAIT,NullPointer);
DHT_Wait_While_Certain_Pin_State_And_Time_Do_Not_Reach(u8_DHT_Pin,HIGH,DHT_MAX_TIME_US_TO_WAIT,NullPointer);

}
else
{
*pu8_DHT_Response_State=DHT_NO_RESPONSE_ON_THE_BUS;
}



}
/****************************************************************************************
This is a Local function that receives the ones and zeros and transfer it to byte
and that helps on receiving the bytes of temperature and humidity
****************************************************************************************/
/****************************************************************************************
Parameters
--------------
u8_DHT_Pin-> It the pin of the DHT  that done over it the operation(uinteg8_t)
pu8_DHT_CopyOfValueReceived->(Pointer to uinteg8_t) It returns the byte that received

*******************************************************************************************/
static void DHT_Receive_data(uinteg8_t u8_DHT_Pin,uinteg8_t*pu8_DHT_CopyOfValueReceived)
{
uinteg16_t u16_DHT_Receive_data_Count=0;
*pu8_DHT_CopyOfValueReceived=0;

for (integ8_t i8_DHT_Receive_data_index=7; i8_DHT_Receive_data_index>=0; i8_DHT_Receive_data_index--)
{
DHT_Wait_While_Certain_Pin_State_And_Time_Do_Not_Reach(u8_DHT_Pin,LOW,DHT_MAX_TIME_US_TO_WAIT,NullPointer);
DHT_Wait_While_Certain_Pin_State_And_Time_Do_Not_Reach(u8_DHT_Pin,HIGH,DHT_MAX_TIME_US_TO_WAIT,&u16_DHT_Receive_data_Count);

if(u16_DHT_Receive_data_Count>=DHT_TIME_WAIT_FOR_HIGH_VALUE_OF_DATA_BIT)
{
SET_BIT(*pu8_DHT_CopyOfValueReceived,i8_DHT_Receive_data_index);
}
else
{
CLR_BIT(*pu8_DHT_CopyOfValueReceived,i8_DHT_Receive_data_index);
}

}

}
/****************************************************************************************
This is a Local function that receives the ones and zeros and transfer it to byte
and that helps on receiving the bytes of temperature and humidity
****************************************************************************************/
/***************************************************************************************
Parameters
--------------
u8_DHT_Pin-> It the pin of the DHT  that done over it the operation(uinteg8_t)
pu8_DHT_Sensor_State->(Pointer to uinteg8_t)  It returns the DHT sensor state
Sensor states:
1-DHT_NO_ERROR -> The bus is ok and the node is connected
2-DHT_NO_RESPONSE_ON_THE_BUS -> The node is not connected to the bus
3-DHT_CHECK_SUM_ERROR->There is checksum error

pf32_Temp->Returns Float value of temprature
pf32_Hum->Returns Float value of humidaty
*******************************************************************************************/
void DHT_Read_The_Value_Of_Temp_Humdity(uinteg8_t u8_Pin,uinteg8_t*pu8_DHT_Sensor_State,float32_t*pf32_Temp,float32_t*pf32_Hum)
{
uinteg8_t u8_DHT_Read_The_Value_Of_Temp_Humdity_Response;
uinteg8_t  u8_I_RH,u8_D_RH,u8_I_Temp,u8_D_Temp,u8_CheckSum=0;

*pu8_DHT_Sensor_State=DHT_NO_ERROR;

#if DHT_OPEERATION == DHT_OPERATEED_BY_POLLING
/***Delay the sensor for 2 second as mentioned in datasheet***/
_delay_ms(2000);

#else

#endif
/***DHT send request***/
DHT_Request(u8_Pin);
/***DHT take the response***/
DHT_Response(u8_Pin,&u8_DHT_Read_The_Value_Of_Temp_Humdity_Response);
/***Take the decision if the response reslut is no response on the bus ***/
if(u8_DHT_Read_The_Value_Of_Temp_Humdity_Response==DHT_NO_RESPONSE_ON_THE_BUS)
{
*pu8_DHT_Sensor_State=DHT_NO_RESPONSE_ON_THE_BUS;
}
else/***Receive the data of temprature and humidity ***/
{

DHT_Receive_data(u8_Pin,&u8_I_RH);        /* store first eight bit in I_RH     */
DHT_Receive_data(u8_Pin,&u8_D_RH);      /* store next  eight bit in D_RH     */
DHT_Receive_data(u8_Pin,&u8_I_Temp);    /* store next  eight bit in I_Temp   */
DHT_Receive_data(u8_Pin,&u8_D_Temp);    /* store next  eight bit in D_Temp   */
DHT_Receive_data(u8_Pin,&u8_CheckSum);      /* store next  eight bit in CheckSum */

/****If the summation of all data not equal to checksum return DHT_CHECK_SUM_ERROR***/
if ((u8_I_RH + u8_D_RH + u8_I_Temp + u8_D_Temp) != u8_CheckSum)
{
*pu8_DHT_Sensor_State=DHT_CHECK_SUM_ERROR;
}
else/****Else return the data of Humidaty and Temprature***/
{



}
*pf32_Hum=((uinteg16_t)((u8_I_RH<<8)|(u8_D_RH)))/10.0;
*pf32_Temp=((uinteg16_t)((u8_I_Temp<<8)|(u8_D_Temp)))/10.0;
}


}
