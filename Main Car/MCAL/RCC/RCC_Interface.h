#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_
/** ****************************************************************************
 *
 * @File RCC_Interface.h
 *
 * @brief this file contains prototypes functions for RCC Module
 *
 * @author Project Team
 *
 * @date 6/11/2023
 ******************************************************************************* */
void MRCC_VoidInit(void);

void MRCC_VoidEnablePeriphral(u8 Copy_U8PeriphralBus,u8 Copy_U8PeriphralNumber);

void MRCC_VoidDisablePeriphral(u8 Copy_U8PeriphralBus,u8 Copy_U8PeriphralNumber);

// for the 4 kinds of bus in the ARM MP
#define AHB1_BUS	0
#define AHB2_BUS	1
#define APB1_BUS	2
#define APB2_BUS	3

#define RCC_APB1_TIMER2    0



#define RCC_APB2_USART1    4
#define RCC_APB2_USART6    5
#define RCC_APB1_USART2    17





#define SPI1_PERIPHRAL		12

#endif 
