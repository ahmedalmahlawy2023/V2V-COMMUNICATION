/***************************File Guard *****************************************/
#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_
/** ****************************************************************************
 *
 * @File NVIC_Interface.h
 *
 * @brief this file contains prototypes functions for NVIC Module
 *
 * @author Project Team
 *
 * @date 6/11/2023
 ******************************************************************************* */
#define NVIC_USART1   37
#define NVIC_USART2   38
#define NVIC_USART6   71


typedef enum 
{
	MNVIC_GROUPMODE_G16S0=3,
	MNVIC_GROUPMODE_G8S2,
	MNVIC_GROUPMODE_G4S4,
	MNVIC_GROUPMODE_G2S8,
	MNVIC_GROUPMODE_G0S16,
	
}MNVIC_GroupMode_t;


/*********************************Functions Prototypes**********************************/

void MNVIC_voidEnableInterrupt (u8 Copy_u8IntPos);

void MNVIC_voidDisableInterrupt (u8 Copy_u8IntPos);

void MNVIC_voidEnableInterruptPending (u8 Copy_u8IntPos);

void MNVIC_voidDisableInterruptPending (u8 Copy_u8IntPos);

u8 MNVIC_u8IsInterruptActive (u8 Copy_u8IntPos);

void MNVIC_voidSetInterruptPriority (u8 Copy_u8IntPos,MNVIC_GroupMode_t Copy_uddtGroupMode,u8 Copy_u8GroupNum,u8 Copy_u8SubGroupNum);

void MNVIC_voidSetInterruptGroupMode (MNVIC_GroupMode_t Copy_uddtGroupMode);



#endif 
