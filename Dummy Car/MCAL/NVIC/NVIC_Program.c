/** ****************************************************************************
 *
 * @File NVIC_Program.c
 *
 * @brief this file contains functions related to NVIC Module
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
#include "NVIC_Interface.h"
#include "NVIC_Private.h"
#include "NVIC_Config.h"

/*******************************************************************************
 *                          	APIs Implementation                            *
 *******************************************************************************/
/**
 * @brief Enable an interrupt in the NVIC.
 *
 * This function enables an interrupt at a specific position in the NVIC interrupt set-enable registers.
 *
 * @param Copy_u8IntPos The interrupt position to enable (0 to 84).
 *
 * @note The function sets the corresponding bit in the NVIC_ISER register based on the interrupt position.
 */
void MNVIC_voidEnableInterrupt (u8 Copy_u8IntPos) //there are 85 inturrept source position as there are 85 position in vector table (85 Periphral)
{
	if(Copy_u8IntPos<32)
		{
			//MNVIC_REG->ISER[0] = (1<<copy_u8IntPos);
			SET_BIT(NVIC_P->NVIC_ISER[0],(Copy_u8IntPos));
		}
		else if(Copy_u8IntPos<64)
		{
			//MNVIC_REG->ISER[1] = (1<<(copy_u8IntPos-32));
			SET_BIT(NVIC_P->NVIC_ISER[1],(Copy_u8IntPos-32));

		}
		else if(Copy_u8IntPos<96)
		{
			//MNVIC_REG->ISER[2] = (1<<(copy_u8IntPos-64));
			SET_BIT(NVIC_P->NVIC_ISER[2],(Copy_u8IntPos-64));
		}
		else
		{
			//wrong position
		}
}
/**
 * @brief Disable an interrupt in the NVIC.
 *
 * This function disables an interrupt at a specific position in the NVIC interrupt clear-enable registers.
 *
 * @param Copy_u8IntPos The interrupt position to disable (0 to 84).
 *
 * @note The function clears the corresponding bit in the NVIC_ICER register based on the interrupt position.
 */
void MNVIC_voidDisableInterrupt (u8 Copy_u8IntPos)
{
	// to get the place of this position in which register and the position in this register 
	u8 L_u8RegPos;
	u8 L_u8BitPos;
	L_u8RegPos=Copy_u8IntPos/32; //to know which register 
	L_u8BitPos=Copy_u8IntPos-(32*L_u8RegPos);//to know which bit in register 
	//Clearing NVIC Enable for This Periphral ( each bit corresponding to position)	
	SET_BIT(NVIC_P->NVIC_ICER[L_u8RegPos],L_u8BitPos);
	//or NVIC_P->NVIC_ICER[L_u8RegPos]=(1<<L_u8BitPos);	
}
/**
 * @brief Set the pending flag for an interrupt in the NVIC.
 *
 * This function sets the pending flag for an interrupt at a specific position in the NVIC interrupt set-pending registers.
 *
 * @param Copy_u8IntPos The interrupt position to set as pending (0 to 84).
 *
 * @note Writing 1 to the ISPR bit corresponding to a disabled interrupt sets the state of that interrupt to pending.
 */
void MNVIC_voidEnableInterruptPending (u8 Copy_u8IntPos)//Writing 1 to the ISPR bit corresponding to a disabled interrupt sets the state of that interrupt to pending
{
	// to get the place of this position in which register and the position in this register 
	u8 L_u8RegPos;
	u8 L_u8BitPos;
	L_u8RegPos=Copy_u8IntPos/32; //to know which register 
	L_u8BitPos=Copy_u8IntPos-(32*L_u8RegPos);//to know which bit in register 
	//Setting Pending Flag for This Periphral ( each bit corresponding to position)	
	SET_BIT(NVIC_P->NVIC_ISPR[L_u8RegPos],L_u8BitPos);
}
/**
 * @brief Clear the pending flag for an interrupt in the NVIC.
 *
 * This function clears the pending flag for an interrupt at a specific position in the NVIC interrupt clear-pending registers.
 *
 * @param Copy_u8IntPos The interrupt position to clear as pending (0 to 84).
 *
 * @note Writing 1 to an ICPR bit does not affect the active state of the corresponding interrupt.
 */
void MNVIC_voidDisableInterruptPending (u8 Copy_u8IntPos)//Writing 1 to an ICPR bit does not affect the active state of the corresponding interrupt
{
	// to get the place of this position in which register and the position in this register 
	u8 L_u8RegPos;
	u8 L_u8BitPos;
	L_u8RegPos=Copy_u8IntPos/32; //to know which register 
	L_u8BitPos=Copy_u8IntPos-(32*L_u8RegPos);//to know which bit in register 
	//Setting Pending Flag for This Periphral ( each bit corresponding to position)	
	SET_BIT(NVIC_P->NVIC_ICPR[L_u8RegPos],L_u8BitPos);
}
/**
 * @brief Check if an interrupt is active.
 *
 * This function checks whether an interrupt is active (pending) at a specific position in the NVIC.
 *
 * @param Copy_u8IntPos The interrupt position to check (0 to 84).
 *
 * @return 1 if the interrupt is active, 0 if not.
 */
u8 MNVIC_u8IsInterruptActive (u8 Copy_u8IntPos)
{
	// to get the place of this position in which register and the position in this register 
	u8 L_u8RegPos;
	u8 L_u8BitPos;
	u8 L_u8ActiveState;
	L_u8RegPos=Copy_u8IntPos/32; //to know which register 
	L_u8BitPos=Copy_u8IntPos-(32*L_u8RegPos);//to know which bit in register 
	//Setting Pending Flag for This Periphral ( each bit corresponding to position)	
	L_u8ActiveState=GET_BIT(NVIC_P->NVIC_IABR[L_u8RegPos],L_u8BitPos);
	
	return L_u8ActiveState;
}
/**
 * @brief Set the priority of an interrupt.
 *
 * This function sets the priority of an interrupt at a specific position in the NVIC.
 *
 * @param Copy_u8IntPos The interrupt position to set the priority for (0 to 84).
 * @param Copy_uddtGroupMode The group mode for interrupt priority grouping.
 * @param Copy_u8GroupNum The group number (if applicable based on the group mode).
 * @param Copy_u8SubGroupNum The sub-group number (if applicable based on the group mode).
 *
 * @note The function calculates the priority value based on the group mode, group number, and sub-group number.
 *       It then sets the priority in the NVIC_IPR register.
 */
void MNVIC_voidSetInterruptPriority (u8 Copy_u8IntPos,MNVIC_GroupMode_t Copy_uddtGroupMode,u8 Copy_u8GroupNum,u8 Copy_u8SubGroupNum)
{
	u8 LOC_u8PrioValue =0;
	switch (Copy_uddtGroupMode)
	{
		case MNVIC_GROUPMODE_G0S16 : LOC_u8PrioValue =Copy_u8SubGroupNum;    break;
		case MNVIC_GROUPMODE_G16S0 : LOC_u8PrioValue =Copy_u8GroupNum;       break;
		case MNVIC_GROUPMODE_G4S4 :LOC_u8PrioValue =(Copy_u8GroupNum<<2) | Copy_u8SubGroupNum;    	break;
		case MNVIC_GROUPMODE_G2S8 :LOC_u8PrioValue =(Copy_u8GroupNum<<3) | Copy_u8SubGroupNum; 		break;
		case MNVIC_GROUPMODE_G8S2 :LOC_u8PrioValue =(Copy_u8GroupNum<<1) | Copy_u8SubGroupNum;		break;
	}
	NVIC_P->NVIC_IPR[Copy_u8IntPos]=(LOC_u8PrioValue<<4);
}

void MNVIC_voidSetInterruptGroupMode (MNVIC_GroupMode_t Copy_uddtGroupMode)
{
	SCB_AIRCR= NVIC_VECTKEY; // unlock the register first
	SCB_AIRCR= NVIC_VECTKEY | (Copy_uddtGroupMode<<8); //shifting by 8 to can write on bit number 8 
}
