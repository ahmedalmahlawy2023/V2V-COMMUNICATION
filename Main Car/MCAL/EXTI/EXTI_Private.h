#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_
/** ****************************************************************************
 *
 * @File EXTI_Private.h
 *
 * @brief this file contains private addresses and configurations related to EXTI Module
 *
 * @author Project Team
 *
 * @date 6/11/2023	
 *
 ****************************************************************************** */

#define EXTI_BASE_ADDRESS     	(0x40013C00)
#define SYSCFG_BASE_ADDRESS     (0x40013800)

typedef struct 
{
	u32 EXTI_IMR;
	u32 EXTI_EMR;
	u32 EXTI_RTSR;
	u32 EXTI_FTSR;
	u32 EXTI_SWIER;
	u32 EXTI_PR;
	
}EXTI_R;

typedef struct {

volatile u32 SYSCFG_MEMRMP;  
volatile u32 SYSCFG_PMC;  
volatile u32 SYSCFG_EXTICR1; 
volatile u32 SYSCFG_EXTICR2; 
volatile u32 SYSCFG_EXTICR3; 
volatile u32 SYSCFG_EXTICR4; 
// fe el data sheet t2rebn feh reserved bs m4 mt2kd
volatile u32 SYSCFG_CMPCR; 
	
}SYSCFG;


#define MEXTI              	 	((volatile EXTI_R *) EXTI_BASE_ADDRESS)
//#define MSYSCFG_EXTICR1      	*((volatile u16*) (SYSCFG_BASE_ADDRESS+0x08))
#define MSYSCFG		        	((volatile SYSCFG *) SYSCFG_BASE_ADDRESS) 
#endif
