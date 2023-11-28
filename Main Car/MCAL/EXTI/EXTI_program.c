/** ****************************************************************************
 *
 * @File EXTI_Program.c
 *
 * @brief this file contains functions related to External Interrupt Module
 *
 * @author Project Team
 *
 * @date 6/11/2023
 *
 ****************************************************************************** */
 
/*******************************************************************************
 *                          	Standard Types                                 *
 *******************************************************************************/

#include "../../LIB/ITI_STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/*******************************************************************************
 *                          	MCAL Components                                 *
 *******************************************************************************/
#include "EXTI_Config.h"
#include "EXTI_Interface.h"
#include "EXTI_Private.h"

/*******************************************************************************
 *                           	   Definitions                                 *
 *******************************************************************************/
 static void (*EXTI0_CallBack)(void) = 0;
 static void (*EXTI1_CallBack)(void) = 0;
 static void (*EXTI8_CallBack)(void) = 0;
 
/*******************************************************************************
 *                          	APIs Implementation                            *
 *******************************************************************************/
 /**
 * @brief Enable an external interrupt line.
 *
 * This function enables an external interrupt line for a specified line number.
 *
 * @param Copy_uddtLineNum The line number to enable (e.g., MEXTI_LINE_0, MEXTI_LINE_1).
 *
 * @note The function sets the corresponding bit in the EXTI_IMR register to enable the interrupt line.
 */
 
void MEXTI_voidEnableEXTI(MEXTI_LINE_t Copy_uddtLineNum)
{
	SET_BIT(MEXTI->EXTI_IMR, Copy_uddtLineNum);
}
/**
 * @brief Disable an external interrupt line.
 *
 * This function disables an external interrupt line for a specified line number.
 *
 * @param Copy_uddtLineNum The line number to disable (e.g., MEXTI_LINE_0, MEXTI_LINE_1).
 *
 * @note The function clears the corresponding bit in the EXTI_IMR register to disable the interrupt line.
 */
void MEXTI_voidDisableEXTI(MEXTI_LINE_t Copy_uddtLineNum)
{
	CLR_BIT(MEXTI->EXTI_IMR, Copy_uddtLineNum);
}
/**
 * @brief Generate a software interrupt on an external interrupt line.
 *
 * This function generates a software interrupt on a specified external interrupt line.
 *
 * @param Copy_uddtLineNum The line number to generate the software interrupt (e.g., MEXTI_LINE_0, MEXTI_LINE_1).
 *
 * @note The function sets the corresponding bit in the EXTI_SWIER register to trigger a software interrupt on the line.
 */
void MEXTI_voidSoftwareInterrupt(MEXTI_LINE_t Copy_uddtLineNum)
{
	SET_BIT(MEXTI->EXTI_SWIER, Copy_uddtLineNum);
}
/**
 * @brief Set the trigger source for an external interrupt line.
 *
 * This function configures the trigger source (rising edge, falling edge, or both) for a specified external interrupt line.
 *
 * @param Copy_uddtLineNum The line number to configure the trigger source for (e.g., MEXTI_LINE_0, MEXTI_LINE_1).
 * @param Copy_uddtTriggerMode The trigger mode to set (e.g., MEXTI_RISING_EDGE, MEXTI_FALLING_EDGE, MEXTI_ON_CHANGE).
 *
 * @note The function configures the EXTI_RTSR and EXTI_FTSR registers based on the provided trigger mode.
 */
void MEXTI_voidSetTriggerSource(MEXTI_LINE_t Copy_uddtLineNum, MEXTI_TRIGGER_MODE_t Copy_uddtTriggerMode)
{
	switch(Copy_uddtTriggerMode)
	{
		case MEXTI_RISING_EDGE  : SET_BIT(MEXTI->EXTI_RTSR, Copy_uddtLineNum); break;
		case MEXTI_FALLING_EDGE : SET_BIT(MEXTI->EXTI_FTSR, Copy_uddtLineNum); break;
		case MEXTI_ON_CHANGE    : SET_BIT(MEXTI->EXTI_RTSR, Copy_uddtLineNum);
								  SET_BIT(MEXTI->EXTI_FTSR, Copy_uddtLineNum); 		
								  break;
	}
}
/**
 * @brief Configure the EXTI line to a specific GPIO port.
 *
 * This function configures an EXTI line to use a specific GPIO port.
 *
 * @param Copy_uddtLineNum The EXTI line number to configure (e.g., MEXTI_LINE_0, MEXTI_LINE_1).
 * @param Copy_uddtGPIOPortNum The GPIO port to associate with the EXTI line.
 *
 * @note The function configures the SYSCFG_EXTICR registers based on the provided EXTI line number and GPIO port.
 */
void MEXTI_voidSetEXTIConfig(MEXTI_LINE_t Copy_uddtLineNum, MEXTI_PORT_t Copy_uddtGPIOPortNum) ////////********* leh b3ml and m3 FFFFF kda ana bktb fe elreserved 
{
	// this fun to configure which pin to be setted 
	switch(Copy_uddtLineNum)
	{
		// PIN0x will be configured on EXTI0 only and so on
		// there is 4 registers and each register is responsible for 4 lines or 4 pins in each port
		case MEXTI_LINE_0 : MSYSCFG->SYSCFG_EXTICR1 = (((MSYSCFG->SYSCFG_EXTICR1) & 0xFFFFFFF0) | (Copy_uddtGPIOPortNum << 0)); //the correct MSYSCFG->SYSCFG_EXTICR1 = ((u16)(MSYSCFG->SYSCFG_EXTICR1) & 0xFFF0 | (Copy_uddtGPIOPortNum << 0));
						    break;
		case MEXTI_LINE_1 : MSYSCFG->SYSCFG_EXTICR1 = (((MSYSCFG->SYSCFG_EXTICR1) & 0xFFFFFF0F) | (Copy_uddtGPIOPortNum << 4));
						    break;
		case MEXTI_LINE_2 : MSYSCFG->SYSCFG_EXTICR1 = (((MSYSCFG->SYSCFG_EXTICR1) & 0xFFFFF0FF) | (Copy_uddtGPIOPortNum << 8));
						    break;
		case MEXTI_LINE_3 : MSYSCFG->SYSCFG_EXTICR1 = (((MSYSCFG->SYSCFG_EXTICR1) & 0xFFFF0FFF) | (Copy_uddtGPIOPortNum << 12));
						    break;
		case MEXTI_LINE_4 : MSYSCFG->SYSCFG_EXTICR2 = (((MSYSCFG->SYSCFG_EXTICR2) & 0xFFFFFFF0) | (Copy_uddtGPIOPortNum << 0));
						    break;
		case MEXTI_LINE_5 : MSYSCFG->SYSCFG_EXTICR2 = (((MSYSCFG->SYSCFG_EXTICR2) & 0xFFFFFF0F) | (Copy_uddtGPIOPortNum << 4));
						    break;
		case MEXTI_LINE_6 : MSYSCFG->SYSCFG_EXTICR2 = (((MSYSCFG->SYSCFG_EXTICR2) & 0xFFFFF0FF) | (Copy_uddtGPIOPortNum << 8));
						    break;
		case MEXTI_LINE_7 : MSYSCFG->SYSCFG_EXTICR2 = (((MSYSCFG->SYSCFG_EXTICR2) & 0xFFFF0FFF) | (Copy_uddtGPIOPortNum << 12));
						    break;
		case MEXTI_LINE_8 : MSYSCFG->SYSCFG_EXTICR3 = (((MSYSCFG->SYSCFG_EXTICR3) & 0xFFFFFFF0) | (Copy_uddtGPIOPortNum << 0));
						    break;
		case MEXTI_LINE_9 : MSYSCFG->SYSCFG_EXTICR3 = (((MSYSCFG->SYSCFG_EXTICR3) & 0xFFFFFF0F) | (Copy_uddtGPIOPortNum << 4));
						    break;
		case MEXTI_LINE_10: MSYSCFG->SYSCFG_EXTICR3 = (((MSYSCFG->SYSCFG_EXTICR3) & 0xFFFFF0FF) | (Copy_uddtGPIOPortNum << 8));
						    break;
		case MEXTI_LINE_11: MSYSCFG->SYSCFG_EXTICR3 = (((MSYSCFG->SYSCFG_EXTICR3) & 0xFFFF0FFF) | (Copy_uddtGPIOPortNum << 12));
						    break;
		case MEXTI_LINE_12: MSYSCFG->SYSCFG_EXTICR4 = (((MSYSCFG->SYSCFG_EXTICR4) & 0xFFFFFFF0) | (Copy_uddtGPIOPortNum << 0));
						    break;
		case MEXTI_LINE_13: MSYSCFG->SYSCFG_EXTICR4 = (((MSYSCFG->SYSCFG_EXTICR4) & 0xFFFFFF0F) | (Copy_uddtGPIOPortNum << 4));
						    break;
		case MEXTI_LINE_14: MSYSCFG->SYSCFG_EXTICR4 = (((MSYSCFG->SYSCFG_EXTICR4) & 0xFFFFF0FF) | (Copy_uddtGPIOPortNum << 8));
						    break;
		case MEXTI_LINE_15: MSYSCFG->SYSCFG_EXTICR4 = (((MSYSCFG->SYSCFG_EXTICR4) & 0xFFFF0FFF) | (Copy_uddtGPIOPortNum << 12));
						    break;
		default  		  : break;
	}
}
/**
 * @brief Call back function for external line 0.
 *
 * This function to assign address of function to be implemnted in ISR.
 *
 * @param (void (*ptr) (void)) The function to be implemented.
 *
 */
void MEXTI_voidSetCallBack_EXTI0(void (*ptr) (void)) //elmfroof ykon feh mnha 16 as there is 16 extenal interrupt line 
{
	EXTI0_CallBack = ptr;

}
/**
 * @brief Call back function for external line 1.
 *
 * This function to assign address of function to be implemnted in ISR.
 *
 * @param (void (*ptr) (void)) The function to be implemented.
 *
 */
void MEXTI_voidSetCallBack_EXTI1(void (*ptr) (void))
{
	EXTI1_CallBack = ptr;
}
/**
 * @brief Call back function for external line 8.
 *
 * This function to assign address of function to be implemnted in ISR.
 *
 * @param (void (*ptr) (void)) The function to be implemented.
 *
 */
void MEXTI_voidSetCallBack_EXTI8(void (*ptr) (void))
{
	EXTI8_CallBack = ptr;
}

void EXTI0_IRQHandler(void)  //elmfroof ykon feh mnha 16 as there is 16 extenal interrupt line
{
	// clear PR Flag for EXTI0 by writing 1 on it, without clearing it will do interrupt always
	// we may need to leave the flag without clearing, to avoid sniffing on the system, and keep system in thread
	SET_BIT(MEXTI->EXTI_PR, 0);
	EXTI0_CallBack();
	//SET_BIT(MEXTI->EXTI_PR, 0);
}

void EXTI1_IRQHandler(void)
{
	// clear PR Flag for EXTI1 by writing 1 on it, without clearing it will do interrupt always
	// we may need to leave the flag without clearing, to avoid sniffing on the system, and keep system in thread
	SET_BIT(MEXTI->EXTI_PR, 1); 
	EXTI1_CallBack();
}

void EXTI9_5_IRQHandler(void)
{
	// clear PR Flag for EXTI1 by writing 1 on it, without clearing it will do interrupt always
	// we may need to leave the flag without clearing, to avoid sniffing on the system, and keep system in thread
	SET_BIT(MEXTI->EXTI_PR, 8);
	EXTI8_CallBack();
}

