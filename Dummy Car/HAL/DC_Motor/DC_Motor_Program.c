
/******************************************************************************
 *
 * @File: DC_MOTOR_Program.c
 *
 * @Brief: Implementation of functions for the DC Motor Module
 *
 * @Author: Project Team 
 *
 * @Date: November 11, 2023
 *
 ******************************************************************************/

/*******************************************************************************
 *                          	Standard Types                                 *
 *******************************************************************************/
#include "../../LIB/ITI_STD_Types.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/ERROR_STATE.h"
/*******************************************************************************
 *                          	MCAL Components                                 *
 *******************************************************************************/
#include "../../MCAL/GPIOx/GPIO_Interface.h"
#include "../../MCAL/GPTimer/TIMER_interface.h"
#include "../../MCAL/RCC/RCC_Interface.h"

/*******************************************************************************
 *                          	HAL Components                                *
 *******************************************************************************/

#include "DC_Motor_Interface.h"
#include "DC_Motor_Config.h"
#include "DC_Motor_Private.h"

/**
 * @brief Global variable for speed indication during PWM-based speed control.
 *
 * This variable is used to initialize the speed requirement when configuring PWM for speed control.
 * It represents the desired speed, and its value is used as the compare value for the PWM timer.
 * Changing this value will adjust the speed of the DC_Motor system component .
 *
 * The default value is set to 4000. Ensure that the value is within the acceptable range for PWM control.
 *
 * @note This variable is directly tied to PWM configuration and speed control.
 *
 */
u32 G_u32SpeedIndicator=4000;


/**
 * @brief Initialize the DC motor control module.
 *
 * This function enables the motor driver port and configures its pins as outputs
 * for controlling the DC motors in both forward and backward directions for two motor channels (M1, M2).
 *
 * @note The configuration includes setting the pin modes and output types for both forward
 * and backward directions of each motor channel.
 *
 * @see MRCC_VoidEnablePeriphral()  // Reference to the function for enabling the motor drive port
 * @see MGPIO_voidSetPinMode()      // Reference to the function for setting pin modes
 * @see MGPIO_voidSetOutPutMode()   // Reference to the function for setting output modes
 *
 */
void HDCM_u8Init(void)
{
	//enable MOTOR_DRIVE_PORT
	MRCC_VoidEnablePeriphral(AHB1_BUS,MOTOR_DRIVE_PORT);

	//pins for FORWARD direction M1
	MGPIO_voidSetPinMode(MOTOR_DRIVE_PORT ,FOW_DIR_M1_M2, GPIO_MODE_OUTPUT);
	MGPIO_voidSetOutPutMode(MOTOR_DRIVE_PORT ,FOW_DIR_M1_M2, GPIO_OUTPUT_TYPE_PUSH_PULL);

	//pins for BACKWARD direction M1
	MGPIO_voidSetPinMode(MOTOR_DRIVE_PORT ,BACK_DIR_M1_M2, GPIO_MODE_OUTPUT);
	MGPIO_voidSetOutPutMode(MOTOR_DRIVE_PORT ,BACK_DIR_M1_M2, GPIO_OUTPUT_TYPE_PUSH_PULL);


	//pins for FORWARD direction M2
	MGPIO_voidSetPinMode(MOTOR_DRIVE_PORT ,FOW_DIR_M3_M4, GPIO_MODE_OUTPUT);
	MGPIO_voidSetOutPutMode(MOTOR_DRIVE_PORT ,FOW_DIR_M3_M4, GPIO_OUTPUT_TYPE_PUSH_PULL);

	//pins for BACKWARD direction M2
	MGPIO_voidSetPinMode(MOTOR_DRIVE_PORT ,BACK_DIR_M3_M4, GPIO_MODE_OUTPUT);
	MGPIO_voidSetOutPutMode(MOTOR_DRIVE_PORT ,BACK_DIR_M3_M4, GPIO_OUTPUT_TYPE_PUSH_PULL);
}
/**
 * @brief Start the DC motor control module with PWM output.
 *
 * This function configures Timer 2 for PWM output to control the DC motors.
 * It sets the prescaler, compare values for both channels (CH1, CH2), and the
 * auto-reload value. Additionally, it specifies PWM output mode for both channels
 * and starts Timer 2 to initiate PWM signal generation.
 *
 * @note Ensure that Timer 2 is properly configured and initialized before calling this function.
 *       Use MTMR_voidSetPrescaler, MTMR_voidSetCMPVal, MTMR_voidSetARR, MTMR_voidSetChannelOutput,
 *       and MTMR_voidStart functions for Timer 2 configuration.
 *
 * @see MTMR_voidSetPrescaler()      // Reference to the function for setting the timer prescaler
 * @see MTMR_voidSetCMPVal()         // Reference to the function for setting compare values
 * @see MTMR_voidSetARR()            // Reference to the function for setting the auto-reload value
 * @see MTMR_voidSetChannelOutput()  // Reference to the function for setting channel output mode
 * @see MTMR_voidStart()             // Reference to the function for starting Timer 2
 *
 * @warning Incorrect configuration of Timer 2 or calling this function without proper initialization
 *          may lead to unexpected behavior in the PWM signal generation for DC motors.
 */
void HDCM_voidStart (void)
{
	MTMR_voidSetPrescaler(TMR_2,64);
	MTMR_voidSetCMPVal(TMR_2,CH1,5000);
	MTMR_voidSetCMPVal(TMR_2,CH2,5000);
	MTMR_voidSetARR(TMR_2,10000);
	MTMR_voidSetChannelOutput(TMR_2,PWM_MODE1,CH1);
	MTMR_voidSetChannelOutput(TMR_2,PWM_MODE1,CH2);
	MTMR_voidStart(TMR_2);
}

/**
 * @brief Move the DC motors forward.
 *
 * This function moves the DC motors forward by setting the appropriate PWM compare values
 * and configuring the GPIO pins for forward motion. It checks the current motor state and
 * takes action only if the motors are not already in the FORWARD state.
 *
 * If the motors are already in the FORWARD state, no action is taken, and the motor state is updated.
 *
 * @note Ensure that the DC motor control module is properly initialized before calling this function.
 *       Use HDCM_u8Init and HDCM_voidStart functions for initialization.
 *
 * @note The speed of the forward motion is determined by the global variable G_u32SpeedIndicator.
 *
 * @see HDCM_u8Init()            // Reference to the function for DC motor control module initialization
 * @see HDCM_voidStart()         // Reference to the function for starting the DC motor control module
 * @see G_u32SpeedIndicator      // Reference to the global variable indicating the speed
 *
 * @warning Modifying the G_u32SpeedIndicator variable may affect the speed of forward motion.
 */

void HDCM_voidMoveForward(void)
{
	if (MOTOR_STATE==FORWARD)
	{
		/*do no thing*/
		MOTOR_STATE=FORWARD;
	}
	else
	{
		MTMR_voidSetCMPVal(TMR_2,CH1,G_u32SpeedIndicator);
		MTMR_voidSetCMPVal(TMR_2,CH2,G_u32SpeedIndicator);
		//move forward
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M1_M2, GPIO_HIGH);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M3_M4, GPIO_HIGH);
		//stop backward
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M1_M2, GPIO_LOW);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M3_M4, GPIO_LOW);
		//set state of motor as forward
		MOTOR_STATE=FORWARD;
	}
}
/**
 * @brief Move the DC motors backward.
 *
 * This function moves the DC motors backward by setting the appropriate PWM compare values
 * and configuring the GPIO pins for backward motion. It checks the current motor state and
 * takes action only if the motors are not already in the BACKWARD state.
 *
 * If the motors are already in the BACKWARD state, no action is taken, and the motor state is updated.
 *
 * @note Ensure that the DC motor control module is properly initialized before calling this function.
 *       Use HDCM_u8Init and HDCM_voidStart functions for initialization.
 *
 * @note The speed of the backward motion is determined by the global variable G_u32SpeedIndicator.
 *
 * @see HDCM_u8Init()            // Reference to the function for DC motor control module initialization
 * @see HDCM_voidStart()         // Reference to the function for starting the DC motor control module
 * @see G_u32SpeedIndicator      // Reference to the global variable indicating the speed
 *
 * @warning Modifying the G_u32SpeedIndicator variable may affect the speed of backward motion.
 */
void HDCM_voidMoveBackward(void)
{
	if (MOTOR_STATE==BACKWARD)
	{
		/*do no thing*/
		MOTOR_STATE=BACKWARD;
	}
	else
	{
		MTMR_voidSetCMPVal(TMR_2,CH1,G_u32SpeedIndicator);
		MTMR_voidSetCMPVal(TMR_2,CH2,G_u32SpeedIndicator);
		//stop forward
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M1_M2, GPIO_LOW);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M3_M4, GPIO_LOW);

		//move backward
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M1_M2, GPIO_HIGH);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M3_M4, GPIO_HIGH);

		//set state of motor as forward
		MOTOR_STATE=BACKWARD;
	}
}
/**
 * @brief Stop the DC motors.
 *
 * This function stops the DC motors by configuring the GPIO pins to stop motion.
 * It checks the current motor state and takes action only if the motors are not already in the STOP state.
 *
 * If the motors are already in the STOP state, no action is taken, and the motor state is updated.
 *
 * @note Ensure that the DC motor control module is properly initialized before calling this function.
 *       Use HDCM_u8Init and HDCM_voidStart functions for initialization.
 */
void HDCM_voidStop(void)
{
	if (MOTOR_STATE==STOP)
	{
		/*do no thing*/
		MOTOR_STATE=STOP;
	}
	else {
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M1_M2, GPIO_LOW);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M3_M4, GPIO_LOW);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M3_M4, GPIO_LOW);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M1_M2, GPIO_LOW);
		MOTOR_STATE=STOP;
	}
}
/**
 * @brief Move the DC motors to the right.
 *
 * This function moves the DC motors to the right by setting the appropriate PWM compare values
 * and configuring the GPIO pins for right motion. It checks the current motor state and
 * takes action only if the motors are not already in the RIGHT state.
 *
 * If the motors are already in the RIGHT state, no action is taken, and the motor state is updated.
 *
 * @note Ensure that the DC motor control module is properly initialized before calling this function.
 *       Use HDCM_u8Init and HDCM_voidStart functions for initialization.
 *
 * @note The speed of the right motion is determined by the global variable G_u32SpeedIndicator.
 *
 * @see HDCM_u8Init()            // Reference to the function for DC motor control module initialization
 * @see HDCM_voidStart()         // Reference to the function for starting the DC motor control module
 * @see G_u32SpeedIndicator      // Reference to the global variable indicating the speed
 *
 * @warning Modifying the G_u32SpeedIndicator variable may affect the speed of right motion.
 */
void HDCM_voidMoveRight(void)
{
	if (MOTOR_STATE==RIGHT)
	{
		/*do no thing*/
	}
	else
	{
		MTMR_voidSetCMPVal(TMR_2,CH1,G_u32SpeedIndicator);
		MTMR_voidSetCMPVal(TMR_2,CH2,G_u32SpeedIndicator);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M1_M2, GPIO_HIGH);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M1_M2, GPIO_LOW);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M3_M4, GPIO_LOW);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M3_M4, GPIO_LOW);
		MOTOR_STATE=RIGHT;
	}
}
/**
 * @brief Move the DC motors to the left.
 *
 * This function moves the DC motors to the left by setting the appropriate PWM compare values
 * and configuring the GPIO pins for left motion. It checks the current motor state and
 * takes action only if the motors are not already in the LEFT state.
 *
 * If the motors are already in the LEFT state, no action is taken, and the motor state is updated.
 *
 * @note Ensure that the DC motor control module is properly initialized before calling this function.
 *       Use HDCM_u8Init and HDCM_voidStart functions for initialization.
 *
 * @note The speed of the left motion is determined by the global variable G_u32SpeedIndicator.
 *
 * @see HDCM_u8Init()            // Reference to the function for DC motor control module initialization
 * @see HDCM_voidStart()         // Reference to the function for starting the DC motor control module
 * @see G_u32SpeedIndicator      // Reference to the global variable indicating the speed
 *
 * @warning Modifying the G_u32SpeedIndicator variable may affect the speed of left motion.
 */
void HDCM_voidMoveLeft(void)
{
	if (MOTOR_STATE==LEFT)
	{
		/*do no thing*/
	}
	else
	{
		MTMR_voidSetCMPVal(TMR_2,CH1,G_u32SpeedIndicator);
		MTMR_voidSetCMPVal(TMR_2,CH2,G_u32SpeedIndicator);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M3_M4, GPIO_HIGH);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M3_M4, GPIO_LOW);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M1_M2, GPIO_LOW);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M1_M2, GPIO_LOW);
		MOTOR_STATE=LEFT;
	}
}
/**
 * @brief Move the DC motors forward-left.
 *
 * This function moves the DC motors forward-left by setting the appropriate PWM compare values
 * and configuring the GPIO pins for forward-left motion. It checks the current motor state and
 * takes action only if the motors are not already in the FORWARD_LEFT state.
 *
 * If the motors are already in the FORWARD_LEFT state, no action is taken, and the motor state is updated.
 *
 * @note Ensure that the DC motor control module is properly initialized before calling this function.
 *       Use HDCM_u8Init and HDCM_voidStart functions for initialization.
 *
 * @note The speed of the forward-left motion is determined by the global variable G_u32SpeedIndicator.
 *
 * @see HDCM_u8Init()            // Reference to the function for DC motor control module initialization
 * @see HDCM_voidStart()         // Reference to the function for starting the DC motor control module
 * @see G_u32SpeedIndicator      // Reference to the global variable indicating the speed
 *
 * @warning Modifying the G_u32SpeedIndicator variable may affect the speed of forward-left motion.
 */
void HDCM_voidMoveForwardLeft(void)
{
	if (MOTOR_STATE==FORWARD_LEFT)
	{
		/*do no thing*/
	}
	else
	{
		MTMR_voidSetCMPVal(TMR_2,CH1,(G_u32SpeedIndicator*4)/10);
		MTMR_voidSetCMPVal(TMR_2,CH2,G_u32SpeedIndicator);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M3_M4, GPIO_HIGH);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M3_M4, GPIO_LOW);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M1_M2, GPIO_LOW);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M1_M2, GPIO_HIGH);
		MOTOR_STATE=FORWARD_LEFT;
	}
}
/**
 * @brief Move the DC motors forward-right.
 *
 * This function moves the DC motors forward-right by setting the appropriate PWM compare values
 * and configuring the GPIO pins for forward-right motion. It checks the current motor state and
 * takes action only if the motors are not already in the FORWARD_RIGHT state.
 *
 * If the motors are already in the FORWARD_RIGHT state, no action is taken, and the motor state is updated.
 *
 * @note Ensure that the DC motor control module is properly initialized before calling this function.
 *       Use HDCM_u8Init and HDCM_voidStart functions for initialization.
 *
 * @note The speed of the forward-right motion is determined by the global variable G_u32SpeedIndicator.
 *
 * @see HDCM_u8Init()            // Reference to the function for DC motor control module initialization
 * @see HDCM_voidStart()         // Reference to the function for starting the DC motor control module
 * @see G_u32SpeedIndicator      // Reference to the global variable indicating the speed
 *
 * @warning Modifying the G_u32SpeedIndicator variable may affect the speed of forward-right motion.
 */
void HDCM_voidMoveForwardRight(void)
{
	if (MOTOR_STATE==FORWARD_RIGHT)
	{
		/*do no thing*/
	}
	else
	{
		MTMR_voidSetCMPVal(TMR_2,CH1,G_u32SpeedIndicator);
		MTMR_voidSetCMPVal(TMR_2,CH2,(G_u32SpeedIndicator*4)/10);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M3_M4, GPIO_HIGH);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M3_M4, GPIO_LOW);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M1_M2, GPIO_LOW);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M1_M2, GPIO_HIGH);
		MOTOR_STATE=FORWARD_RIGHT;
	}
}
/**
 * @brief Move the DC motors backward-left.
 *
 * This function moves the DC motors backward-left by setting the appropriate PWM compare values
 * and configuring the GPIO pins for backward-left motion. It checks the current motor state and
 * takes action only if the motors are not already in the BACKWARD_LEFT state.
 *
 * If the motors are already in the BACKWARD_LEFT state, no action is taken, and the motor state is updated.
 *
 * @note Ensure that the DC motor control module is properly initialized before calling this function.
 *       Use HDCM_u8Init and HDCM_voidStart functions for initialization.
 *
 * @note The speed of the backward-left motion is determined by the global variable G_u32SpeedIndicator.
 *
 * @see HDCM_u8Init()            // Reference to the function for DC motor control module initialization
 * @see HDCM_voidStart()         // Reference to the function for starting the DC motor control module
 * @see G_u32SpeedIndicator      // Reference to the global variable indicating the speed
 *
 * @warning Modifying the G_u32SpeedIndicator variable may affect the speed of backward-left motion.
 */
void HDCM_voidMoveBackLeft(void)
{
	if (MOTOR_STATE==BACK_LEFT)
	{
		/*do no thing*/
	}
	else
	{
		MTMR_voidSetCMPVal(TMR_2,CH1,(G_u32SpeedIndicator*3)/10);
		MTMR_voidSetCMPVal(TMR_2,CH2,G_u32SpeedIndicator);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M3_M4, GPIO_LOW);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M3_M4, GPIO_HIGH);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M1_M2, GPIO_HIGH);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M1_M2, GPIO_LOW);
		MOTOR_STATE=BACK_LEFT;
	}
}
/**
 * @brief Move the DC motors backward-right.
 *
 * This function moves the DC motors backward-right by setting the appropriate PWM compare values
 * and configuring the GPIO pins for backward-right motion. It checks the current motor state and
 * takes action only if the motors are not already in the BACKWARD_RIGHT state.
 *
 * If the motors are already in the BACKWARD_RIGHT state, no action is taken, and the motor state is updated.
 *
 * @note Ensure that the DC motor control module is properly initialized before calling this function.
 *       Use HDCM_u8Init and HDCM_voidStart functions for initialization.
 *
 * @note The speed of the backward-right motion is determined by the global variable G_u32SpeedIndicator.
 *
 * @see HDCM_u8Init()            // Reference to the function for DC motor control module initialization
 * @see HDCM_voidStart()         // Reference to the function for starting the DC motor control module
 * @see G_u32SpeedIndicator      // Reference to the global variable indicating the speed
 *
 * @warning Modifying the G_u32SpeedIndicator variable may affect the speed of backward-right motion.
 */
void HDCM_voidMoveBackRight(void)
{
	if (MOTOR_STATE==BACK_RIGHT)
	{
		/*do no thing*/
	}
	else
	{
		MTMR_voidSetCMPVal(TMR_2,CH1,G_u32SpeedIndicator);
		MTMR_voidSetCMPVal(TMR_2,CH2,(G_u32SpeedIndicator*3)/10);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M3_M4, GPIO_LOW);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M3_M4, GPIO_HIGH);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,BACK_DIR_M1_M2, GPIO_HIGH);
		MGPIO_voidSetPinValue(MOTOR_DRIVE_PORT ,FOW_DIR_M1_M2, GPIO_LOW);
		MOTOR_STATE=BACK_RIGHT;
	}
}

/**
 * @brief Set the DC motor control module state based on a received Bluetooth command.
 *
 * This function takes a character representing a Bluetooth command and sets the state
 * of the DC motor control module accordingly. Supported commands include 'F' for forward,
 * 'B' for backward, 'S' for stop, 'R' for right, 'L' for left, 'G' for forward-left, 'I' for forward-right,
 * 'J' for back-right, and 'H' for back-left. Any other character results in an error state.
 *
 * @param Copy_u8CarState The character representing the Bluetooth command.
 * @return Error state, OK if the command is valid, NOK if an invalid command is received.
 *
 * @note Ensure that the DC motor control module is properly initialized before calling this function.
 *       Use HDCM_u8Init and HDCM_voidStart functions for initialization.
 *
 * @see HDCM_u8Init()            // Reference to the function for DC motor control module initialization
 * @see HDCM_voidStart()         // Reference to the function for starting the DC motor control module
 * @see HDCM_voidMoveForward()   // Reference to the function for moving forward
 * @see HDCM_voidMoveBackward()  // Reference to the function for moving backward
 * @see HDCM_voidStop()          // Reference to the function for stopping
 * @see HDCM_voidMoveRight()     // Reference to the function for moving right
 * @see HDCM_voidMoveLeft()      // Reference to the function for moving left
 * @see HDCM_voidMoveForwardLeft()  // Reference to the function for moving forward-left
 * @see HDCM_voidMoveForwardRight() // Reference to the function for moving forward-right
 * @see HDCM_voidMoveBackRight()    // Reference to the function for moving back-right
 * @see HDCM_voidMoveBackLeft()     // Reference to the function for moving back-left
 */

u8 HDCM_u8CarState (u8 Copy_u8CarState)
{
	ERROR_STATE_T Loc_ErrorState=OK;

	if (Copy_u8CarState == 'F')
	{
		HDCM_voidMoveForward();
	}
	else if (Copy_u8CarState == 'B')
	{
		HDCM_voidMoveBackward();
	}
	else if (Copy_u8CarState == 'S')
	{
		HDCM_voidStop();
	}
	else if (Copy_u8CarState == 'R')
	{
		HDCM_voidMoveRight();
	}
	else if (Copy_u8CarState == 'L')
	{
		HDCM_voidMoveLeft();
	}
	else if (Copy_u8CarState == 'G')
	{
		HDCM_voidMoveForwardLeft();
	}
	else if (Copy_u8CarState == 'I')
	{
		HDCM_voidMoveForwardRight();
	}
	else if (Copy_u8CarState == 'J')
	{
		HDCM_voidMoveBackRight();
	}
	else if (Copy_u8CarState == 'H')
	{
		HDCM_voidMoveBackLeft();
	}
	else
	{
		Loc_ErrorState=NOK;
	}
	return Loc_ErrorState;
}

/**
* @brief Change the speed of the DC motors based on a relative speed value.
*
* This function adjusts the speed of the DC motors based on a relative speed value provided
* as an argument. The supported values range from 0 to 9, where '0' corresponds to no speed,
* and '9' corresponds to the maximum speed. Additionally, the character 'q' sets the maximum speed.
*
* @param A_u8RelativeSpeed The relative speed value to set the motors to.
*
* @return Error state, OK if the speed change is successful, OUT_OF_RANGE if the provided
*         relative speed is not within the valid range.
*
* @note Ensure that the DC motor control module is properly initialized before calling this function.
*       Use HDCM_u8Init and HDCM_voidStart functions for initialization.
*
* @see HDCM_u8Init()            // Reference to the function for DC motor control module initialization
* @see HDCM_voidStart()         // Reference to the function for starting the DC motor control module
* @see HDCM_u8CarState()        // Reference to the function for changing the car state based on Bluetooth command
* @see G_u32SpeedIndicator      // Reference to the global variable indicating the speed
*
* @warning Modifying the G_u32SpeedIndicator variable directly may affect the behavior of this function.
*/
u8 HDCM_u8ChangeSpeed (u8 A_u8RelativeSpeed)
{
	ERROR_STATE_T Loc_u8ErrorState=OK;
	switch(A_u8RelativeSpeed)
	{
	case  0 :
	case '0': G_u32SpeedIndicator=0;     		break;
	case  1 :
	case '1': G_u32SpeedIndicator=1000;  		break;
	case  2 :
	case '2': G_u32SpeedIndicator=2000;  		break;
	case  3 :
	case '3': G_u32SpeedIndicator=3000;  		break;
	case  4 :
	case '4': G_u32SpeedIndicator=4000;  		break;
	case  5 :
	case '5': G_u32SpeedIndicator=5000;  		break;
	case  6 :
	case '6': G_u32SpeedIndicator=6000;  		break;
	case  7 :
	case '7': G_u32SpeedIndicator=7000; 		break;
	case  8 :
	case '8': G_u32SpeedIndicator=8000;  		break;
	case  9 :
	case '9': G_u32SpeedIndicator=9000; 		break;
	case 'q': G_u32SpeedIndicator=10000; 		break;
	default : Loc_u8ErrorState=OUT_OF_RANGE;  	break;

	}

	MTMR_voidSetCMPVal(TMR_2,CH1,G_u32SpeedIndicator);
	MTMR_voidSetCMPVal(TMR_2,CH2,G_u32SpeedIndicator);
	return Loc_u8ErrorState;
}

