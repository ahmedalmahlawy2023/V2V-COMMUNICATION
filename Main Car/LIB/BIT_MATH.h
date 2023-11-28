#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(VAR,BIT_NUM)    (VAR|=(1<<BIT_NUM))
#define CLR_BIT(VAR,BIT_NUM)    ((VAR)&= (~(1<<(BIT_NUM))))
#define TOG_BIT(VAR,BIT_NUM)   	((VAR)^=(1<<(BIT_NUM)))
#define GET_BIT(VAR,BIT_NUM)    (((VAR)>>(BIT_NUM))&1)

#define Set_BITS(REG,MSK)			(REG) |=  (MSK)
#define Clr_BITS(REG,MSK)			(REG) &= ~(MSK)
#define Toggle_BITS(REG,MSK)		(REG) ^=  (MSK)

#define Set_ALL_BITS(REG)			(REG) =  (0xFFFFFFFF)
#define Clr_ALL_BITS(REG)			(REG) =  (0x00000000)
#define Toggle_ALL_BITS(REG)		(REG) ^= (0xFFFFFFFF)





#endif 
