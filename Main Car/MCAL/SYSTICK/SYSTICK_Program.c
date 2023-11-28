/** ****************************************************************************
 *
 * @File SYSTICK_Program.c
 *
 * @brief this file contains functions related to SYSTICK Module
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
#include "SYSTICK_Interface.h"
#include "SYSTICK_Private.h"
#include "SYSTICK_Config.h"
/*******************************************************************************
 *                          	Global Variables	                           *
 *******************************************************************************/
static u8 MSTK_INTERVAL_MODE;
static void (* MSTK_single)(void)=NULL;
static void (* MSTK_periodic)(void)=NULL;
/*******************************************************************************
 *                          	APIs Implementation                            *
 *******************************************************************************/
/**
 * @brief Initialize the SysTick timer.
 *
 * This function configures the SysTick timer based on the selected clock source.
 * The clock source can be AHB divided by 8 or the AHB processor clock.
 * It sets the appropriate clock source bit in the STK_CTRL register.
 *
 * @note This function should be called at the beginning of the program.
 */
void MSTK_voidInit(void)
{
	//chossing clock source 
	#if 	CLK_SOURCE == AHB_OVER_8
	CLR_BIT( MSYSTICK->STK_CTRL ,CLKSOURCE);
	
	#elif  	CLK_SOURCE == AHB_PROCCESOR_CLOCK
	SET_BIT( MSYSTICK->STK_CTRL ,CLKSOURCE);
#endif
}
/**
 * @brief Implement a busy-wait delay using the SysTick timer.
 *
 * This function provides a simple busy-wait delay using the SysTick timer.
 *
 * @param Copy_u32Ticks The number of ticks to wait.
 */
void MSTK_voidSetBusyWait(u32 Copy_u32Ticks)
{
	MSYSTICK->STK_LOAD=0;
	MSYSTICK->STK_VAL=0;

	// setting start point first
	MSYSTICK->STK_LOAD=Copy_u32Ticks;
	//enable timer to move value from load reg to value reg and start counting 
	SET_BIT( MSYSTICK->STK_CTRL ,ENABLE);
	//waiting the falg to be sure that time has wasted 
	while (GET_BIT(MSYSTICK->STK_CTRL ,COUNTFLAG)==0);
	//clearing enable to stop timer from begining counting again (stops timer)
	CLR_BIT( MSYSTICK->STK_CTRL ,ENABLE);
	//deleting values in REGs (e7tyaty)(deleting it by writing any value in it) (clearing value reg also clearing flag)
	MSYSTICK->STK_LOAD=0;
	MSYSTICK->STK_VAL=0;
}
/**
 * @brief Set a single-shot delay using the SysTick timer.
 *
 * This function sets up a single-shot delay using the SysTick timer and associates a callback function.
 *
 * @param Copy_u32Ticks The number of ticks for the delay.
 * @param Copy_ptr A pointer to the callback function to be executed after the delay.
 */
void MSTK_voidSetIntervalSingle  (u32 Copy_u32Ticks , void (*Copy_ptr)(void) )
{
	MSYSTICK->STK_LOAD=0; // da 34an lw ana d5lt hna tany b EXTI msln we mknt4 5lst el interval el awlnya flma ad5l tany abd2 mn el awl
	MSYSTICK->STK_VAL=0;
	// setting start point first
	MSYSTICK->STK_LOAD=Copy_u32Ticks;
	// setting enable for ISR 
	SET_BIT( MSYSTICK->STK_CTRL ,TICKINT);
	//assignment call back fun to global variable to pass it to handler  
	MSTK_single=Copy_ptr;
	//enable timer to move value from load reg to value reg and start counting 
	SET_BIT( MSYSTICK->STK_CTRL ,ENABLE);
	// this line is like a flag to check which func is called 
	MSTK_INTERVAL_MODE=MSTK_SINGLE_INTERVAL;
}
/**
 * @brief Set a periodic delay using the SysTick timer.
 *
 * This function sets up a periodic delay using the SysTick timer and associates a callback function.
 *
 * @param Copy_u32Ticks The number of ticks for the delay.
 * @param Copy_ptr A pointer to the callback function to be executed periodically.
 */
void MSTK_voidSetIntervalPeriodic(u32 Copy_u32Ticks , void (*Copy_ptr)(void) )
{
	MSYSTICK->STK_LOAD=0;// da 34an lw ana d5lt hna tany b EXTI msln we mknt4 5lst el interval el awlnya flma ad5l tany abd2 mn el awl
	MSYSTICK->STK_VAL=0;
	// setting start point first
	MSYSTICK->STK_LOAD=Copy_u32Ticks;
	// setting enable for ISR 
	SET_BIT( MSYSTICK->STK_CTRL ,TICKINT);
	//assign call back fun to global variable to pass it to handler  
	MSTK_periodic=Copy_ptr;
	//enable timer to move value from load reg to value reg and start counting 
	SET_BIT( MSYSTICK->STK_CTRL ,ENABLE);
	// this line is like a flag to check which func is called 
	MSTK_INTERVAL_MODE=MSTK_Periodic_INTERVAL;
}
/**
 * @brief Stop the ongoing interval.
 *
 * This function stops the SysTick timer and clears its values registers.
 */
void MSTK_voidStopInterval(void )
{
	//disable timer to stop counter from 
	CLR_BIT( MSYSTICK->STK_CTRL ,ENABLE);
	//deleting values in REGs (e7tyaty)(deleting it by writing any value in it)
	MSYSTICK->STK_LOAD=0;
	MSYSTICK->STK_VAL=0;
}
/**
 * @brief Get the elapsed time since the last start point.
 *
 * @return The elapsed time in ticks.
 */
u32 MSTK_u32GetElapsedTime(void) 
{
	u32 Loc_startingValue;
	u32 Loc_remainingTime;
	u32 Loc_elapsedTime;
	//to get remaining time just read the Value Reg 
	Loc_remainingTime = MSYSTICK->STK_VAL;
	//read the start value 
	Loc_startingValue = MSYSTICK->STK_LOAD;
	//get elapsed time 
	Loc_elapsedTime=Loc_startingValue-Loc_remainingTime;

	return Loc_elapsedTime;
}
/**
 * @brief Get the remaining time until the next interrupt.
 *
 * @return The remaining time in ticks.
 */
u32 MSTK_u32GetRemainingTime(void) 
{
	u32 Loc_remainingTime;
	//to get remaining time just read the Value Reg 
	Loc_remainingTime=MSYSTICK->STK_VAL;
	return Loc_remainingTime;
}
/**
 * @brief SysTick Timer Interrupt Service Routine (ISR).
 *
 * This function is called when the SysTick timer interrupt occurs.
 * It clears the flag, disables the timer, clears the values registers, and executes the associated callback function.
 */
void SysTick_Handler (void)
{
	//clearing the flag 
	u8 Loc_readingFlag;
	Loc_readingFlag=GET_BIT(MSYSTICK->STK_CTRL,COUNTFLAG);
	if (MSTK_INTERVAL_MODE==MSTK_SINGLE_INTERVAL)
	{
		//first we have to disable timer and clearing vlaues registers and disable ISR
		//disable timer to stop counter from 
		CLR_BIT( MSYSTICK->STK_CTRL ,ENABLE);
		//deleting values in REGs (e7tyaty)(deleting it by writing any value in it)
		MSYSTICK->STK_LOAD=0;
		MSYSTICK->STK_VAL=0;
		//disable ISR
		CLR_BIT( MSYSTICK->STK_CTRL ,TICKINT);

		//calling callback fun to implement the action of ISR
		if (MSTK_single!=NULL)
		{
			MSTK_single();
		}
		else 
		{
			// error state
		}
	}
		
	else if (MSTK_INTERVAL_MODE==MSTK_Periodic_INTERVAL)
	{
		if (MSTK_periodic!=NULL)
		{
			MSTK_periodic();
		}
		else 
		{
			// error state
		}
	}
}
