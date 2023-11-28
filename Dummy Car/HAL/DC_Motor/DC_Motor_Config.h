/******************************************************************************
 *
 * @file DC_Motor_Config.h
 *
 * @brief Configuration file for the DC motor control module.
 *
 * This file defines the configuration parameters for the DC motor control module,
 * including the GPIO port and pin configurations for motor control.
 *
 * @Author: Project Team 
 *
 * @Date: November 11, 2023
 *
 *****************************************************************************/
#ifndef HAL_DC_MOTOR_DC_MOTOR_CONFIG_H_
#define HAL_DC_MOTOR_DC_MOTOR_CONFIG_H_



/**
 * @brief GPIO port used for motor control.
 *
 * This macro defines the GPIO port used for controlling the DC motors.
 * Modify this macro to match the GPIO port connected to the motor driver.
 */
#define MOTOR_DRIVE_PORT   GPIO_PORTA

/**
 * @brief GPIO pins for controlling the left side of the car ( two left side motors) (Channel 1).
 *
 * These macros define the GPIO pins used for controlling the left side of the DC motors.
 * FOW_DIR_M1_M2 represents the forward direction, and BACK_DIR_M1_M2 represents the backward direction.
 * Modify these macros based on the actual GPIO pin connections for left-side motor control.
 */
#define FOW_DIR_M1_M2   	    GPIO_PIN5	//in 1
#define BACK_DIR_M1_M2   		GPIO_PIN4	//in 2

/**
 * @brief GPIO pins for controlling the right side of the car (two left right motors) (Channel 2).
 *
 * These macros define the GPIO pins used for controlling the right side of the DC motors.
 * FOW_DIR_M3_M4 represents the forward direction, and BACK_DIR_M3_M4 represents the backward direction.
 * Modify these macros based on the actual GPIO pin connections for right-side motor control.
 */
#define FOW_DIR_M3_M4   	    GPIO_PIN3	//in 3
#define BACK_DIR_M3_M4     		GPIO_PIN2	//in 4


#endif /* HAL_DC_MOTOR_DC_MOTOR_CONFIG_H_ */
