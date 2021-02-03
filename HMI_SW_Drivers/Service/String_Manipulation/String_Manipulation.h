/*
 * String_Manipulation.h
 *
 * Created: 17/02/2020 17:56:08
 *  Author: HMI
 */ 


#ifndef STRING_MANIPULATION_H_
#define STRING_MANIPULATION_H_

void TransformIntToString (integ64_t Integr_Number, uinteg8_t *pntrToChar,uinteg8_t c_number_of_digits);
void TransformFloatToString(double Float_Number,char How_Many_Sign_Before_Point,char How_Many_Sign_After_Point,char* pntrToChar);


#endif /* STRING_MANIPULATION_H_ */