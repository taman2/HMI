/*
 *  Data_types.h
 *  Created: 11/1/2019 5:36:45 PM
 *  Author: Asaad
 */ 


#ifndef DATA_tYPES_H_
#define DATA_tYPES_H_



typedef   char					 char_t;
typedef   unsigned char			uinteg8_t;
typedef   signed char          integ8_t;
typedef   unsigned short int uinteg16_t;
typedef   signed short int    integ16_t;
typedef   unsigned int long   uinteg32_t;
typedef   signed int long     integ32_t;
typedef   unsigned long long uinteg64_t;
typedef   signed long  long  integ64_t;
typedef   float             float32_t;
typedef   double            float64_t;
typedef   long double      float128_t;
typedef           void(*PntrToFunc_t)(void)  ;   
#define   NullPointer      ((void *)0)


#endif /* Data_types.h */