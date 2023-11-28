/******************************************************************************
 *
 * @file DC_Motor_Interface.h
 *
 * @brief Interface file for the DC motor control module.
 *
 * This file declares the interface functions for the DC motor control module,
 * providing a high-level overview of the available functions for motor control.
 *
 * @Author: Project Team 
 *
 * @Date: November 11, 2023
 *
 *****************************************************************************/

#ifndef HAL_DC_MOTOR_DC_MOTOR_INTERFACE_H_
#define HAL_DC_MOTOR_DC_MOTOR_INTERFACE_H_


/**
 * @brief Initialize the DC motor control module.
 *
 * This function initializes the necessary components for the DC motor control module,
 * such as GPIO pins, timers, and other peripherals.
 *
 * @param none
 * @return none
 */

void HDCM_u8Init(void);

/**
 * @brief Move the DC motors forward.
 *
 * This function moves the DC motors in the forward direction.
 *
 * @param none
 * @return none
 */
void HDCM_voidMoveForward(void);

/**
 * @brief Move the DC motors backward.
 *
 * This function moves the DC motors in the backward direction.
 *
 * @param none
 * @return none
 */
void HDCM_voidMoveBackward(void);

/**
 * @brief Stop the DC motors.
 *
 * This function stops the movement of the DC motors.
 *
 * @param none
 * @return none
 */
void HDCM_voidStop(void);

/**
 * @brief Move the DC motors to the right.
 *
 * This function moves the DC motors to the right.
 *
 * @param none
 * @return none
 */
void HDCM_voidMoveRight(void);

/**
 * @brief Move the DC motors forward-left.
 *
 * This function moves the DC motors in the forward-left direction.
 *
 * @param none
 * @return none
 */
void HDCM_voidMoveForwardLeft(void);

/**
 * @brief Move the DC motors forward-right.
 *
 * This function moves the DC motors in the forward-right direction.
 *
 * @param none
 * @return none
 */
void HDCM_voidMoveForwardRight(void);

/**
 * @brief Move the DC motors back-left.
 *
 * This function moves the DC motors in the back-left direction.
 *
 * @param none
 * @return none
 */
void HDCM_voidMoveBackLeft(void);

/**
 * @brief Move the DC motors back-right.
 *
 * This function moves the DC motors in the back-right direction.
 *
 * @param none
 * @return none
 */
void HDCM_voidMoveBackRight(void);

/**
 * @brief Move the DC motors to the left.
 *
 * This function moves the DC motors to the left.
 *
 * @param none
 * @return none
 */
void HDCM_voidMoveLeft(void);

/**
 * @brief Change the speed of the DC motors.
 *
 * This function adjusts the speed of the DC motors based on a relative speed value.
 *
 * @param A_u8RelativeSpeed The relative speed value to set the motors to.
 * @return Error state, OK if the speed change is successful, OUT_OF_RANGE if the provided
 *         relative speed is not within the valid range.
 */
u8 HDCM_u8ChangeSpeed(u8 A_u8RelativeSpeed);

/**
 * @brief Start the DC motor control module.
 *
 * This function starts the DC motor control module, enabling the timers and other necessary components.
 *
 * @param none
 * @return none
 */
void HDCM_voidStart(void);

/**
 * @brief Change the state of the DC motor control module based on a Bluetooth command.
 *
 * This function takes a character representing a Bluetooth command and sets the state
 * of the DC motor control module accordingly.
 *
 * @param Copy_u8CarState The character representing the Bluetooth command.
 * @return Error state, OK if the command is valid, NOK if an invalid command is received.
 */
u8 HDCM_u8CarState(u8 Copy_u8CarState);

#endif /* HAL_DC_MOTOR_DC_MOTOR_INTERFACE_H_ */
