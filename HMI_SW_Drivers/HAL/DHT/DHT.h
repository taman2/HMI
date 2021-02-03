/*
 * DHT.h
 *
 * Created: 10/14/2020 1:39:16 AM
 *  Author:Amgad_HMI 
 */


#ifndef DHT_H_
#define DHT_H_
/*****************Defines*************************/

#define DHT_TIME_WAIT_FOR_HIGH_VALUE_OF_DATA_BIT 5U
#define DHT_MAX_TIME_US_TO_WAIT                  15U
#define DHT_NO_ERROR                 2u
#define DHT_CHECK_SUM_ERROR                      3u
#define DHT_NO_RESPONSE_ON_THE_BUS               4u  
#define DHT_OPERATEED_BY_TIME_BASE               5u
#define DHT_OPERATEED_BY_POLLING                 6u

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
void DHT_Read_The_Value_Of_Temp_Humdity(uinteg8_t u8_Pin,uinteg8_t*pu8_DHT_Sensor_State,float32_t*pf32_Temp,float32_t*pf32_Hum);
#endif /* DHT_H_ */
