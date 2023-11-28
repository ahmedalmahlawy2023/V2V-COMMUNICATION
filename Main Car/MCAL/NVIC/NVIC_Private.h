#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_

/** ****************************************************************************
 *
 * @File NVIC_Private.h
 *
 * @brief this file contains private addresses and configurations related to NVIC Module
 *
 * @author Project Team
 *
 * @date 6/11/2023	
 *
 ****************************************************************************** */

#define NVIC_BASE_ADDRESS    		0xE000E100

#define SCB_AIRCR 					(*(volatile u32*)0xE000ED0C)

#define NVIC_VECTKEY 				0x05FA0000



typedef struct 
{
	u32 NVIC_ISER[8];
	u32 NVIC_RESERVED1[24];    // 0x180-0x11C=64(byte) then 64/4=19-1 (as i start from end of register 7 of iser not start of it)  memory loc (register) then take the decimal number
	u32 NVIC_ICER[8];
	u32 NVIC_RESERVED2[24];
	u32 NVIC_ISPR[8];
	u32 NVIC_RESERVED3[24];
	u32 NVIC_ICPR[8];
	u32 NVIC_RESERVED4[24];
	u32 NVIC_IABR[8];
	u32 NVIC_RESERVED5[56]; 
	u8  NVIC_IPR[240];
	u32 NVIC_RESERVED6[580];
	u32 NVIC_STIR;
	
}NVIC_R;

#define NVIC_P      ((volatile NVIC_R *)NVIC_BASE_ADDRESS)



#endif