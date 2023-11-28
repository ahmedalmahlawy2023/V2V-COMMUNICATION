/******************************************************************************
 *
 * @File: Ultrasonic_Program.c
 *
 * @Brief: Implementation of functions for the Ultrasonic Module
 *
 * @Author: Project Team 
 *
 * @Date: November 11, 2023
 *
 ******************************************************************************/


/*******************************************************************************
 *                           Standard Types                                  *
 *******************************************************************************/
#include "../../LIB/ITI_STD_Types.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/ERROR_STATE.h"

/*******************************************************************************
 *                          	MCAL Components                                 *
 *******************************************************************************/
#include "../../MCAL/RCC/RCC_Interface.h"
#include "../../MCAL/GPIOx/GPIO_Interface.h"
#include "../../MCAL/SYSTICK/SYSTICK_Interface.h"
#include"../../MCAL/NVIC/NVIC_Interface.h"
#include "../../MCAL/EXTI/EXTI_Interface.h"
/** @} */ // end of MCAL Components
/*******************************************************************************
 *                          	HAL Components                                 *
 *******************************************************************************/
#include"../../HAL/Ultrasonic/Ultrasonic_Interface.h"
#include"../../HAL/Ultrasonic/Ultrasonic_Config.h"

/**
 * @brief Initialize Ultrasonic module.
 *
 * This function initializes the GPIO pins for Ultrasonic Trigger and Echo.
 */
void HUS_voidInit(void)
{
	MGPIO_voidSetPinMode(TRIGGER_PORT1,TRIGGER_PIN1,GPIO_MODE_OUTPUT);  //for TRIGGER_PIN1  --> output   forward
	MGPIO_voidSetOutPutMode(TRIGGER_PORT1,TRIGGER_PIN1,GPIO_OUTPUT_TYPE_PUSH_PULL);
	MGPIO_voidSetOutputSpeed(TRIGGER_PORT1,TRIGGER_PIN1,GPIO_OUTPUT_SPEED_LOW);
	MGPIO_voidSetPinMode(ECHO_PORT1,ECHO_PIN1,GPIO_MODE_INPUT);  //for ECHO_PIN1  --> input
	MGPIO_voidSetPullState(ECHO_PORT1,ECHO_PIN1,GPIO_PULL_PULL_DOWN);

	MGPIO_voidSetPinMode(TRIGGER_PORT2,TRIGGER_PIN2,GPIO_MODE_OUTPUT);  //for TRIGGER_PIN2  --> output    left
	MGPIO_voidSetOutPutMode(TRIGGER_PORT2,TRIGGER_PIN2,GPIO_OUTPUT_TYPE_PUSH_PULL);
	MGPIO_voidSetOutputSpeed(TRIGGER_PORT2,TRIGGER_PIN2,GPIO_OUTPUT_SPEED_LOW);
	MGPIO_voidSetPinMode(ECHO_PORT2,ECHO_PIN2,GPIO_MODE_INPUT);  //for ECHO_PIN2 --> input
	MGPIO_voidSetPullState(ECHO_PORT2,ECHO_PIN2,GPIO_PULL_PULL_DOWN);

	MGPIO_voidSetPinMode(TRIGGER_PORT3,TRIGGER_PIN3,GPIO_MODE_OUTPUT);  //for TRIGGER_PIN3  --> output    right
	MGPIO_voidSetOutPutMode(TRIGGER_PORT3,TRIGGER_PIN3,GPIO_OUTPUT_TYPE_PUSH_PULL);
	MGPIO_voidSetOutputSpeed(TRIGGER_PORT3,TRIGGER_PIN3,GPIO_OUTPUT_SPEED_LOW);
	MGPIO_voidSetPinMode(ECHO_PORT3,ECHO_PIN3,GPIO_MODE_INPUT);  //for ECHO_PIN3  --> input
	MGPIO_voidSetPullState(ECHO_PORT3,ECHO_PIN3,GPIO_PULL_PULL_DOWN);

	MGPIO_voidSetPinMode(TRIGGER_PORT4,TRIGGER_PIN4,GPIO_MODE_OUTPUT);  //for TRIGGER_PIN4  --> output    backward
	MGPIO_voidSetOutPutMode(TRIGGER_PORT4,TRIGGER_PIN4,GPIO_OUTPUT_TYPE_PUSH_PULL);
	MGPIO_voidSetOutputSpeed(TRIGGER_PORT4,TRIGGER_PIN4,GPIO_OUTPUT_SPEED_LOW);
	MGPIO_voidSetPinMode(ECHO_PORT4,ECHO_PIN4,GPIO_MODE_INPUT);  //for ECHO_PIN4  --> input
	MGPIO_voidSetPullState(ECHO_PORT4,ECHO_PIN4,GPIO_PULL_PULL_DOWN);
}

/**
 * @brief Calculate distance using Ultrasonic sensors.
 *
 * This function triggers Ultrasonic pulses based on the specified Ultrasonic sensor,
 * measures the echo duration, and calculates the distance based on the speed of sound.
 *
 * @param A_USNUM_t_Ultrasonic_Num The Ultrasonic sensor number (1-4) to calculate distance for.
 * @return The calculated distance in centimeters.
 */

f32 HUS_f32CalcDistance (USNUM_t A_USNUM_t_Ultrasonic_Num)
{
	u32 L_u32TicksNumber = 0   ;
	f32 L_f32Distance    = 0.0 ;

	/*trig pulse to trigger pin
	 * 3us low
	 * 10us high
	 * then low
	 */

	if(A_USNUM_t_Ultrasonic_Num == 1)
	{ // Forward US
		MGPIO_voidSetPinValue(TRIGGER_PORT1,TRIGGER_PIN1,GPIO_LOW);
		MSTK_voidSetBusyWait(6) ;
		MGPIO_voidSetPinValue(TRIGGER_PORT1,TRIGGER_PIN1,GPIO_HIGH);
		MSTK_voidSetBusyWait(20) ;
		MGPIO_voidSetPinValue(TRIGGER_PORT1,TRIGGER_PIN1,GPIO_LOW);

		//wait to generate 8 pulses (40KHZ)/
		MSTK_voidSetBusyWait(500);

		//wait until generating rising edge for echo pin/
		while (MGPIO_u8GetPinValue(ECHO_PORT1, ECHO_PIN1) == 0);
		while (MGPIO_u8GetPinValue(ECHO_PORT1, ECHO_PIN1) == 1)
		{
			//each iteration takes 2.45 us/
			L_u32TicksNumber ++;
			MSTK_voidSetBusyWait(4);   // why busy wait ?
		}
	}

	else if(A_USNUM_t_Ultrasonic_Num == 2)
	{ // Left US
		MGPIO_voidSetPinValue(TRIGGER_PORT2,TRIGGER_PIN2,GPIO_LOW);
		MSTK_voidSetBusyWait(6) ;
		MGPIO_voidSetPinValue(TRIGGER_PORT2,TRIGGER_PIN2,GPIO_HIGH);
		MSTK_voidSetBusyWait(20) ;
		MGPIO_voidSetPinValue(TRIGGER_PORT2,TRIGGER_PIN2,GPIO_LOW);

		//wait to generate 8 pulses (40KHZ)/
		MSTK_voidSetBusyWait(500);

		//wait until generating rising edge for echo pin/
		while (MGPIO_u8GetPinValue(ECHO_PORT2, ECHO_PIN2) == 0);
		while (MGPIO_u8GetPinValue(ECHO_PORT2, ECHO_PIN2) == 1)
		{
			//each iteration takes 2.45 us/
			L_u32TicksNumber ++;
			MSTK_voidSetBusyWait(4);
		}
	}

	else if(A_USNUM_t_Ultrasonic_Num == 3)
	{ // Right US
		MGPIO_voidSetPinValue(TRIGGER_PORT3,TRIGGER_PIN3,GPIO_LOW);
		MSTK_voidSetBusyWait(6) ;
		MGPIO_voidSetPinValue(TRIGGER_PORT3,TRIGGER_PIN3,GPIO_HIGH);
		MSTK_voidSetBusyWait(20) ;
		MGPIO_voidSetPinValue(TRIGGER_PORT3,TRIGGER_PIN3,GPIO_LOW);

		//wait to generate 8 pulses (40KHZ)/
		MSTK_voidSetBusyWait(500);

		//wait until generating rising edge for echo pin/
		while (MGPIO_u8GetPinValue(ECHO_PORT3, ECHO_PIN3) == 0);
		while (MGPIO_u8GetPinValue(ECHO_PORT3, ECHO_PIN3) == 1)
		{
			//each iteration takes 2.45 us/
			L_u32TicksNumber++;
			MSTK_voidSetBusyWait(4);
		}
	}
	else if(A_USNUM_t_Ultrasonic_Num == 4)
	{ // backward US
		MGPIO_voidSetPinValue(TRIGGER_PORT4,TRIGGER_PIN4,GPIO_LOW);
		MSTK_voidSetBusyWait(6) ;
		MGPIO_voidSetPinValue(TRIGGER_PORT4,TRIGGER_PIN4,GPIO_HIGH);
		MSTK_voidSetBusyWait(20) ;
		MGPIO_voidSetPinValue(TRIGGER_PORT4,TRIGGER_PIN4,GPIO_LOW);

		//wait to generate 8 pulses (40KHZ)/
		MSTK_voidSetBusyWait(500);

		//wait until generating rising edge for echo pin/
		while (MGPIO_u8GetPinValue(ECHO_PORT4, ECHO_PIN4) == 0);
		while (MGPIO_u8GetPinValue(ECHO_PORT4, ECHO_PIN4) == 1)
		{
			//each iteration takes 2.45 us/
			L_u32TicksNumber++;
			MSTK_voidSetBusyWait(4);
		}
	}

	else
	{
		// do nothing
	}

	L_f32Distance = ((float)L_u32TicksNumber)*(6.125)*(0.0343) ;   // how to get time of iteration
	L_f32Distance = L_f32Distance / 2 ;

	//initialize L_u32TicksNumber for next read/
	L_u32TicksNumber = 0 ;
	return L_f32Distance ;
}








