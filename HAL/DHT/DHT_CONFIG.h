/*
 * DHT_Config.h
 *
 * Created: 10/22/2020 10:14:24 AM
 *  Author: HMI
 */ 


#ifndef DHT_CONFIG_H_
#define DHT_CONFIG_H_

#include "DHT.h"

/***
	   Configure using DHT_OPERATEED_BY_POLLING to work with delay 1 second 
	   to using time base instead of delay use DHT_OPERATEED_BY_TIME_BASE   
                                                                              ***/
#define DHT_OPEERATION                       DHT_OPERATEED_BY_TIME_BASE



#endif /* DHT_CONFIG_H_ */