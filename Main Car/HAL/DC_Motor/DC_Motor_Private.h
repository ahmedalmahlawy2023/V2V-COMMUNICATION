/******************************************************************************
 *
 * @file DC_Motor_Private.h
 *
 * @brief Private header file for the DC motor control module.
 *
 * This file defines the private elements of the DC motor control module, including the enumeration for motor states.
 *
 * @Author: Project Team 
 *
 * @Date: November 11, 2023
 *
 *****************************************************************************/

#ifndef HAL_DC_MOTOR_DC_MOTOR_PRIVATE_H_
#define HAL_DC_MOTOR_DC_MOTOR_PRIVATE_H_


/**
 * @brief Enumeration representing different states of the DC motor.
 *
 * The enumeration includes states such as STOP, FORWARD, BACKWARD, RIGHT, LEFT, FORWARD_LEFT,
 * FORWARD_RIGHT, BACK_LEFT, and BACK_RIGHT.
 */


enum MOTOR_STATE_T
{
    STOP,           /**< Motor is in the STOP state. */
    FORWARD,        /**< Motor is moving in the FORWARD direction. */
    BACKWARD,       /**< Motor is moving in the BACKWARD direction. */
    RIGHT,          /**< Motor is moving to the RIGHT. */
    LEFT,           /**< Motor is moving to the LEFT. */
    FORWARD_LEFT,   /**< Motor is moving in the FORWARD-LEFT direction. */
    FORWARD_RIGHT,  /**< Motor is moving in the FORWARD-RIGHT direction. */
    BACK_LEFT,      /**< Motor is moving in the BACKWARD-LEFT direction. */
    BACK_RIGHT      /**< Motor is moving in the BACKWARD-RIGHT direction. */
} MOTOR_STATE = STOP; /**< Global variable representing the current motor state, initialized to STOP. */

#endif /* HAL_DC_MOTOR_DC_MOTOR_PRIVATE_H_ */
