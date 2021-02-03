/*
 * BitManipulation.h
 *
 * Created: 02/11/2019 00:43:50
 *  Author: Amgad_HMI
 */ 


#ifndef BITMANIPULATION_H_
#define BITMANIPULATION_H_
#define CLR_INT_FLAG(REG,N)  REG=1<<N
#define SET_PORT(REG)	(PortREG|=0xff)
#define SET_PORT_WITH_VALUE(REG,VALUE) (REG|=VALUE )
#define RESET_PORT_WITH_VALUE(REG,VALUE) (REG&=~VALUE)
#define CLR_PORT(REG)	(REG=(0x00))
#define SET_BIT(REG,sgu16_index) (REG|=(1<<sgu16_index))
#define CLR_BIT(REG,sgu16_index) (REG&=(~(1<<sgu16_index)))
#define SET_REG_VALUE(REG,VALUE)           (   REG| = (VALUE))



/*  
 *  Reset bit
 *  _________
 *	|A|B->>O|
 *	---------  
 *	|0|0->>0|
 *	|0|1->>1|
 *	|1|0->>0|
 *	|1|1->>0|
 *  ---------   
 */
/*-->>O=~1&B   B=B&(~1)  B&=~(1<<X)  X->postion of bit */
#define GET_BIT(REG,sgu16_index) ((REG>>sgu16_index)&0x01)
#define TOGGLE_BIT(REG,sgu16_index) (REG^=(1<<sgu16_index))
#define TOGGLE_PORT(REG) (REG^=0xff)
#define BIT_IS_SET(REG,sgu16_index) (REG&(1<<sgu16_index))
#define BIT_IS_CLR(REG,sgu16_index) (!(REG&(1<<sgu16_index)))
/**        Advice :Write the value is binary     **/
/**             |0|0|0|0|0|1|1|1|                **/
/**SET_VAlUE_IN_POSTION_FROM_tO(5,7,REG1,0b111;) **/
#define SET_VAlUE_IN_POSTION_FROM_tO(i,j,REG,VALUE) REG=(  ( (~((~( 0XFF<<(j-i+1) ))<<i))&REG ) |   (VALUE<<i) )
#define SET_LOWER_NIBBLE(REG)  SET_VAlUE_IN_POSTION_FROM_tO(0,3,REG,0b1111)///////////////////////////////////////////////////
#define CLR_LOWER_NIBBLE(REG)  SET_VAlUE_IN_POSTION_FROM_tO(0,3,REG,0b0000)
#define SET_HIGHER_NIBBLE(REG) SET_VAlUE_IN_POSTION_FROM_tO(4,7,REG,0b1111)
#define CLR_HIGHER_NIBBLE(REG) SET_VAlUE_IN_POSTION_FROM_tO(4,7,REG,0b0000)
#define GET_LOWER_NIBBLE_AT_LOW_BITS(REG) (REG&0x0f) /////////////////////////////////////
#define GET_HIGHER_NIBBLE_AT_LOW_BITS(REG) ((REG>>4)&0x0f)
#define GET_LOWER_NIBBLE_AT_HIGH_BITS(REG) ((REG<<4)&0xf0)
#define GET_HIGHER_NIBBLE_AT_HIGH_BITS(REG) (REG&0xf0)




#define setBit(REG,BIT)       REG |=(1<<BIT) /*set bit*/
#define clearBit(REG,BIT)     REG &= ~(1<<BIT)
#define ToggleBit(REG,BIT)    (REG ^=(1<<BIT))
#define GetBit(REG,BIT)       (REG &(1<<BIT))

#define setBits(REG,BM)       REG |=(BM)  /*set mask? chang some bits in register without affecting other bits */
#define clearBits(REG,BM)     REG &=(BM) /*mask clear */
#define ToggleBits(REG)    REG ^=(REG)
#define MaskBits(REG,BM)      REG = (BM)



#endif