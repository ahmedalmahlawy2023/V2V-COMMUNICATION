/** ****************************************************************************
 *
 * @File GPIO_Private.h
 *
 * @brief this file contains private addresses and configurations related to GPIO Module
 *
 * @author Project Team
 *
 * @date 6/11/2023	
 *
 ****************************************************************************** */
#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_
/*******************************BASE Addresses for GPIOx*********************************************/

#define GPIOA_BASE_ADDRESS      (0x40020000)
#define GPIOB_BASE_ADDRESS		(0x40020400)
#define GPIOC_BASE_ADDRESS		(0x40020800)
#define GPIOD_BASE_ADDRESS		(0x40020C00)
#define GPIOE_BASE_ADDRESS		(0x40021000)
#define GPIOH_BASE_ADDRESS		(0x40021C00)

/******************************* GPIOA Register Map*********************************************/
/**********************  Define each register port for each GPIO  ************************/

//#define GPIO_MODER                   (*((volatile u32 *)GPIOA_BASE_ADDRESS+0x00)) this method willnot be used 

/******************************* GPIOx Register Map(register Definition)*********************************************/
typedef struct 
{
	volatile u32 MODER;   	// GPIO port mode register   address offset:0x00 
	volatile u32 OTYPER;	// GPIO port ------ register   address offset:0x04 
	volatile u32 OSPEEDR;	// GPIO port ------ register   address offset:0x08
	volatile u32 PUPDR;		// GPIO port ------ register   address offset:0x0C
	volatile u32 IDR;		// GPIO port ------ register   address offset:0x10 
	volatile u32 ODR;		// GPIO port output data register   address offset:0x14
	volatile u32 BSRR;		// GPIO port bit set reset register   address offset:0x18 
	volatile u32 LCKR;		// GPIO port Lock Pin register   address offset:0x1C 
	volatile u32 AFRL;		// GPIO port Alternate Func Low register   address offset:0x20
	volatile u32 AFRH;		// GPIO port Alternate Func High register   address offset:0x24 
}GPIOx_r;  
 
/******************************* Struct Base Address for GPIOA*****************************************/
#define MGPIOA			((volatile GPIOx_r*)GPIOA_BASE_ADDRESS)
/******************************* Struct Base Address for GPIOB*****************************************/
#define MGPIOB			((volatile GPIOx_r*)GPIOB_BASE_ADDRESS)
/******************************* Struct Base Address for GPIOC*****************************************/
#define MGPIOC			((volatile GPIOx_r*)GPIOC_BASE_ADDRESS)
/******************************* Struct Base Address for GPIOD*****************************************/
#define MGPIOD			((volatile GPIOx_r*)GPIOD_BASE_ADDRESS)
/******************************* Struct Base Address for GPIOE*****************************************/
#define MGPIOE			((volatile GPIOx_r*)GPIOE_BASE_ADDRESS)
/******************************* Struct Base Address for GPIOH*****************************************/
#define MGPIOH			((volatile GPIOx_r*)GPIOH_BASE_ADDRESS)

/*******************************Versions of MCU *******************************************************/
#define STM32F401cc  1
#endif