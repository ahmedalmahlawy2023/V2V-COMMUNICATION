#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

/** ****************************************************************************
 *
 * @File RCC_Private.h
 *
 * @brief this file contains private addresses and configurations related to RCC Module
 *
 * @author Project Team
 *
 * @date 6/11/2023	
 *
 ****************************************************************************** */

#define BASE_ADDRESS  0x40023800

// each periphral i make for it struct and base address and the same steps
typedef struct 
{
	volatile u32 RCC_CR;
	volatile u32 RCC_PLLCFGR;
	volatile u32 RCC_CFGR;
	volatile u32 RCC_CIR;
	volatile u32 RCC_AHB1RSTR;
	volatile u32 RCC_AHB2RSTR;
	
    volatile u32 Reserved1;
    volatile u32 Reserved2;
	
    volatile u32 RCC_APB1RSTR;
    volatile u32 RCC_APB2RSTR;
	
	volatile u32 Reserved3;
    volatile u32 Reserved4;
	
    volatile u32 RCC_AHB1ENR;
    volatile u32 RCC_AHB2ENR;
	
	volatile u32 Reserved5;
	volatile u32 Reserved6;
	
	volatile u32 RCC_APB1ENR;
	volatile u32 RCC_APB2ENR;
	
	volatile u32 Reserved7;
	volatile u32 Reserved8;
	
	volatile u32 RCC_AHB1LPENR;
	volatile u32 RCC_AHB2LPENR;
	
	volatile u32 Reserved9;
	volatile u32 Reserved10;
	
	volatile u32 RCC_APB1LPENR;
	volatile u32 RCC_APB2LPENR;
	
	volatile u32 Reserved11;
	volatile u32 Reserved12;
	
	volatile u32 RCC_BDCR;
	volatile u32 RCC_CSR;
	
	volatile u32 Reserved13;
	volatile u32 Reserved14;
	
	volatile u32 RCC_SSCGR;
	volatile u32 RCC_PLLI2SCFGR;
}RCC;

#define MRCC  ((volatile RCC *)BASE_ADDRESS) //MRCC is pointer to struct 

//for sourse of clock  
#define HSI 0
#define HSE 1
#define PLL 2


//  Bits in RCC_CR register
#define HSION  0
#define HSEON  16
#define PLLON  24


//  Bits in RCC_PLLCFGR register
#define PLLSRC 22
#define PLLP0  16
#define PLLN0  6
#define PLLM0  0


// PLLP values
#define _2_Prescaler   	0
#define _4_Prescaler	1
#define _6_Prescaler	2
#define _8_Prescaler	3

// First 2 Bits in RCC_CFGR register 
#define SW0    0
#define SW1    1


// for the 4 kinds of bus in the ARM MP
#define AHB1_BUS	0
#define AHB2_BUS	1
#define APB1_BUS	2
#define APB2_BUS	3


//Peripheral Clock Enable For APB1 Bus  
/*
#define    TIM2_RCC         0
#define    TIM3_RCC         1
#define    TIM4_RCC         2
#define    TIM5_RCC         3
#define    TIM6_RCC         4
#define    TIM7_RCC         5
#define    TIM12_RCC        6
#define    TIM13_RCC        7
#define    TIM14_RCC        8
#define    WWDG_RCC         11
#define    SPI2_RCC         14
#define    SPI3_RCC         15
#define    USART2_RCC       17
#define    USART3_RCC       18
#define    UART4_RCC        19
#define    UART5_RCC        20
#define    I2C1_RCC         21
#define    I2C2_RCC         22
#define    USB_RCC          23
#define    CAN_RCC          25
#define    BKP_RCC          27
#define    PWR_RCC          28
#define    DAC_RCC          29


//Peripheral Clock Enable For APB2 Bus
#define    AFIO_RCC         0
#define    GPIOA_RCC        2
#define    GPIOB_RCC        3
#define    GPIOC_RCC        4
#define    GPIOD_RCC        5
#define    GPIOE_RCC        6
#define    GPIOF_RCC        7
#define    GPIOG_RCC        8
#define    ADC1_RCC         9
#define    ADC2_RCC         10
#define    TIM1_RCC         11
#define    SPI1_RCC         12
#define    TIM8_RCC         13
#define    USART1_RCC       14
#define    ADC3_RCC         15
#define    TIM9_RCC         19
#define    TIM10_RCC        20
#define    TIM11_RCC        21

*/

//AHB PRESCALER OPTIONS
#define AHP_NO_PRESCALAR	      7
#define AHP_2_PRESCALAR 	      8
#define AHP_4_PRESCALAR 	      9
#define AHP_8_PRESCALAR 	      10
#define AHP_16_PRESCALAR 	      11
#define AHP_64_PRESCALAR 	      12
#define AHP_128_PRESCALAR       13
#define AHP_256_PRESCALAR       14
#define AHP_512_PRESCALAR       15


#define AHB_PRESCALAR_MASK 0xFFFFFF0F

#endif 
