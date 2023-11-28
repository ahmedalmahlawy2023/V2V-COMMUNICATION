/** ****************************************************************************
 *
 * @File TIMER_Program.c
 *
 * @brief this file contains functions related to Timer Module
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
#include "TIMER_interface.h"
#include "TIMER_private.h"


/**
 * @brief this function is used to start the timer
 * 
 * @param Copy_uddtTMR_no [TMR2 - TMR3 - TMR4 - TMR5]
 * @return void
 */
void MTMR_voidStart(TMRN_t Copy_uddtTMR_no)
{
	switch(Copy_uddtTMR_no)
	{
	case TMR_2:
		/* Enable Timer */
		SET_BIT(TMR2 -> CR1, CEN_BIT);
		break;
	case TMR_3:
		/* Initialize all the registers */
		SET_BIT(TMR3 -> EGR, 0);
		/* Enable Timer */
		SET_BIT(TMR3 -> CR1, CEN_BIT);
		break;
	case TMR_4:
		/* Initialize all the registers */
		SET_BIT(TMR4 -> EGR, 0);
		/* Enable Timer */
		SET_BIT(TMR4 -> CR1, CEN_BIT);
		break;
	case TMR_5:
		/* Initialize all the registers */
		SET_BIT(TMR5 -> EGR, 0);
		/* Enable Timer */
		SET_BIT(TMR5 -> CR1, CEN_BIT);
		break;

	default  : 								break;
	}
}

/**
 * @brief this function is used to stop the timer
 * 
 * @param Copy_uddtTMR_no [TMR2 - TMR3 - TMR4 - TMR5]
 * @return void
 */
void MTMR_voidStop(TMRN_t Copy_uddtTMR_no)
{
	switch(Copy_uddtTMR_no)
	{
		case TMR_2: CLR_BIT(TMR2 -> CR1, CEN_BIT); break;
		case TMR_3: CLR_BIT(TMR3 -> CR1, CEN_BIT); break;
		case TMR_4: CLR_BIT(TMR4 -> CR1, CEN_BIT); break;
		case TMR_5: CLR_BIT(TMR5 -> CR1, CEN_BIT); break;
		default  : 									  break;
	}
}

/**
 * @brief this function is used to set the prescaler
 * 
 * @param Copy_uddtTMR_no [TMR2 - TMR3 - TMR4 - TMR5]
 * @param Copy_u16Value value from 1 to 65536
 * @return void
 */
void MTMR_voidSetPrescaler(TMRN_t Copy_uddtTMR_no, u16 Copy_u16Value)
{
	switch(Copy_uddtTMR_no)
	{
		case TMR_2: /* Clear all bits*/
				   Clr_ALL_BITS(TMR2 -> PSC);
				   /* Set prescaler value */
				   TMR2 -> PSC |= Copy_u16Value - 1;
				   break;
		case TMR_3: /* Clear all bits*/
				   Clr_ALL_BITS(TMR3 -> PSC);
				   /* Set prescaler value */
				   TMR3 -> PSC |= Copy_u16Value - 1;
				   break;
		case TMR_5: /* Clear all bits*/
			       Clr_ALL_BITS(TMR5 -> PSC);
			       /* Set prescaler value */
			       TMR5 -> PSC |= Copy_u16Value - 1;
			       break;
		default  :									 break;
	}
}

/**
 * @brief this function is used to set the timer mode when generating a signal
 * 
 * @param Copy_uddtTMR_no timer number [TMR2 - TMR3 - TMR4 - TMR5]
 * @param Copy_uddtFn timer mode [FROZEN - ACTIVE - INACTIVE - TOGGLE - INACTIVE_FORCE - ACTIVE_FORCE - PWM_MODE1 - PWM_MODE2]
 * @param Copy_uddtChNo Channel number [CH1 ~ CH4]
 * @return void
 */
void MTMR_voidSetChannelOutput(TMRN_t Copy_uddtTMR_no, CMPFn_t Copy_uddtFn, CHN_t Copy_uddtChNo)
{
	switch(Copy_uddtTMR_no)
	{
	case TMR_2:
		switch(Copy_uddtChNo)
		{
		case CH1: /* Set Capture/Compare 1 as output */
			CLR_BIT(TMR2 -> CCMR1, 1);
			CLR_BIT(TMR2 -> CCMR1, 0);
			//Clr_BITS(TMR2 -> CCMR1, 0x00000073);
			/* Output Compare 1 pre-load enable */
			SET_BIT(TMR2 -> CCMR1, 3);
			/* Select Output Compare 1 */
			//TMR2 -> CCMR1 |= (Copy_uddtFn << OC1M_SHIFT);
			TMR2 -> CCMR1 = ((TMR2 -> CCMR1) &(0xFFFFFF8F)) | (Copy_uddtFn << OC1M_SHIFT);
			/* Select Capture/Compare 1 output polarity active high */
			//CLR_BIT(TMR2 -> CCER, 1);
			/* Initialize all the registers (ana kda bn2l el compare value we el auto reload value we el prescaler ll shadow reg 34an tt7t fe elregister bta3tha ) */
			SET_BIT(TMR2 -> EGR, 0);
			/* Enable Capture/Compare 1 output */
			SET_BIT(TMR2 -> CCER, CC1EN_BIT);
			break;

		case CH2:
			/* Set Capture/Compare 1 as output */
			CLR_BIT(TMR2 -> CCMR1, 8);
			CLR_BIT(TMR2 -> CCMR1, 9);
			//Clr_BITS(TMR2 -> CCMR1, 0x00000073);
			/* Output Compare 1 pre-load enable */
			SET_BIT(TMR2 -> CCMR1, 11);
			/* Select Output Compare 1 */
			//TMR2 -> CCMR1 |= (Copy_uddtFn << OC2M_SHIFT);
			TMR2 -> CCMR1 = ((TMR2 -> CCMR1) &(0xFFFF8FFF)) | (Copy_uddtFn << 12);
			/* Initialize all the registers (ana kda bn2l el compare value we el auto reload value we el prescaler ll shadow reg 34an tt7t fe elregister bta3tha ) */
			SET_BIT(TMR2 -> EGR, 0);
			/* Enable Capture/Compare 1 output */
			SET_BIT(TMR2 -> CCER, 4);
			break;

		case CH3:
			/* Set Capture/Compare 1 as output */
			CLR_BIT(TMR2 -> CCMR2, 0);
			CLR_BIT(TMR2 -> CCMR2, 1);
			//Clr_BITS(TMR2 -> CCMR1, 0x00000073);
			/* Output Compare 1 pre-load enable */
			SET_BIT(TMR2 -> CCMR2, 3);
			/* Select Output Compare 1 */
			//TMR2 -> CCMR1 |= (Copy_uddtFn << OC3M_SHIFT);
			TMR2 -> CCMR2 = ((TMR2 -> CCMR2) &(0xFFFFFF8F)) | (Copy_uddtFn << 4);
			/* Initialize all the registers (ana kda bn2l el compare value we el auto reload value we el prescaler ll shadow reg 34an tt7t fe elregister bta3tha ) */
			SET_BIT(TMR2 -> EGR, 0);
			/* Enable Capture/Compare 1 output */
			SET_BIT(TMR2 -> CCER, 8);
			break;

		case CH4:
			/* Set Capture/Compare 1 as output */
			CLR_BIT(TMR2 -> CCMR2, 8);
			CLR_BIT(TMR2 -> CCMR2, 9);
			//Clr_BITS(TMR2 -> CCMR1, 0x00000073);
			/* Output Compare 1 pre-load enable */
			SET_BIT(TMR2 -> CCMR2, 11);
			/* Select Output Compare 1 */
			//TMR2 -> CCMR1 |= (Copy_uddtFn << OC4M_SHIFT);
			TMR2 -> CCMR2 = ((TMR2 -> CCMR2) &(0xFFFF8FFF)) | (Copy_uddtFn << 12);
			/* Initialize all the registers (ana kda bn2l el compare value we el auto reload value we el prescaler ll shadow reg 34an tt7t fe elregister bta3tha ) */
			SET_BIT(TMR2 -> EGR, 0);
			/* Enable Capture/Compare 1 output */
			SET_BIT(TMR2 -> CCER, 12);
			break;
		}
		break;

		default:                               break;
	}
}

/**
 * @brief this function is used to set the compare value at the CCR_REG
 * 
 * @param Copy_uddtTMR_no timer number [TMR2 - TMR3 - TMR4 - TMR5]
 * @param Copy_uddtChNo Channel number [CH1 ~ CH4]
 * @param cmpValue compare value [0 ~ 65536]
 * @return void
 */
void MTMR_voidSetCMPVal(TMRN_t Copy_uddtTMR_no, CHN_t Copy_uddtChNo, u32 cmpValue)
{
	switch(Copy_uddtTMR_no)
	{
	case TMR_2:
		switch(Copy_uddtChNo)
		{
		case CH1: /* Set Compare Value*/
			TMR2 -> CCR1 = cmpValue;
			break;
		case CH2: /* Set Compare Value*/
			TMR2 -> CCR2 = cmpValue;
			break;
		case CH3: /* Set Compare Value*/
			TMR2 -> CCR3 = cmpValue;
			break;
		case CH4: /* Set Compare Value*/
			TMR2 -> CCR4 = cmpValue;
			break;
		default: 										break;
		}  												break;
		default: 										break;
	}
}

/**
 * @brief this function is used to set the Auto Reload Preload Value - ARR
 * 
 * @param Copy_uddtTMR_no timer number [TMR2 - TMR3 - TMR4 - TMR5]
 * @param Copy_u32Value value [0 ~ 65536]
 * @return void
 */
void MTMR_voidSetARR(TMRN_t Copy_uddtTMR_no, u32 Copy_u32Value)
{
	// enabling auto reload pre-load
	SET_BIT(TMR2->CR1,7);
	// set auto reload value
	switch(Copy_uddtTMR_no)
	{
		case TMR_2: /* Set Auto-reload Value*/
				   TMR2 -> ARR = Copy_u32Value;
				   break;

		case TMR_3: /* Set Auto-reload Value*/
				   TMR3 -> ARR = (u16)Copy_u32Value;
			       break;

		case TMR_5: /* Set Auto-reload Value*/
				   TMR5 -> ARR = Copy_u32Value;
				   break;
		default:   							break;
	}
}

/**
 * @brief this function is used to reset count (clear the CNT_REG)
 * 
 * @param Copy_uddtTMR_no timer number [TMR2 - TMR3 - TMR4 - TMR5]
 * @return void
 */
void MTMR_voidClearCount(TMRN_t Copy_uddtTMR_no)
{
	switch(Copy_uddtTMR_no)
	{
	case TMR_2:
		TMR2 -> CNT = 0;
		break;
	case TMR_3:
		TMR3 -> CNT = 0;
		break;
	case TMR_5:
		TMR5 -> CNT = 0;
		break;
	default:                               break;
	}
}

