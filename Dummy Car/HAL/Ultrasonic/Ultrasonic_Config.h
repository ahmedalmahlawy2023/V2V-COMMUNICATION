/******************************************************************************
 *
 * @file Ultrasonic_Config.h
 *
 * @brief Configuration file for Ultrasonic module
 *
 * This file contains the configuration parameters for the Ultrasonic module,
 * including GPIO pins for trigger and echo, and related port and pin assignments.
 *
 * @Author: Project Team 
 *
 * @Date: November 11, 2023
 *
 *****************************************************************************/
#ifndef HAL_ULTRASONIC_ULTRASONIC_CONFIG_H_
#define HAL_ULTRASONIC_ULTRASONIC_CONFIG_H_

#include "../../MCAL/GPIOx/GPIO_Interface.h"
/**
 * @defgroup Ultrasonic_Config Ultrasonic Configuration
 * @{
 */

/**
 * @name Forward Ultrasonic Sensor (US1) Configuration
 * @{
 */
#define TRIGGER_PORT1   GPIO_PORTB  /**< GPIO Port for the trigger pin of the forward sensor (US1) */
#define TRIGGER_PIN1    GPIO_PIN0   /**< GPIO Pin for the trigger pin of the forward sensor (US1) */
#define ECHO_PORT1      GPIO_PORTB  /**< GPIO Port for the echo pin of the forward sensor (US1) */
#define ECHO_PIN1       GPIO_PIN1   /**< GPIO Pin for the echo pin of the forward sensor (US1) */
/** @} */


/**
 * @name Left Ultrasonic Sensor (US2) Configuration
 * @{
 */
#define TRIGGER_PORT2   GPIO_PORTB  /**< GPIO Port for the trigger pin of the left sensor (US2) */
#define TRIGGER_PIN2    GPIO_PIN2   /**< GPIO Pin for the trigger pin of the left sensor (US2) */
#define ECHO_PORT2      GPIO_PORTB  /**< GPIO Port for the echo pin of the left sensor (US2) */
#define ECHO_PIN2       GPIO_PIN3   /**< GPIO Pin for the echo pin of the left sensor (US2) */
/** @} */

/**
 * @name Right Ultrasonic Sensor (US3) Configuration
 * @{
 */
#define TRIGGER_PORT3   GPIO_PORTB  /**< GPIO Port for the trigger pin of the right sensor (US3) */
#define TRIGGER_PIN3    GPIO_PIN4   /**< GPIO Pin for the trigger pin of the right sensor (US3) */
#define ECHO_PORT3      GPIO_PORTB  /**< GPIO Port for the echo pin of the right sensor (US3) */
#define ECHO_PIN3       GPIO_PIN5   /**< GPIO Pin for the echo pin of the right sensor (US3) */
/** @} */

/**
 * @name Backward Ultrasonic Sensor (US4) Configuration
 * @{
 */
#define TRIGGER_PORT4   GPIO_PORTB  /**< GPIO Port for the trigger pin of the backward sensor (US4) */
#define TRIGGER_PIN4    GPIO_PIN8   /**< GPIO Pin for the trigger pin of the backward sensor (US4) */
#define ECHO_PORT4      GPIO_PORTB  /**< GPIO Port for the echo pin of the backward sensor (US4) */
#define ECHO_PIN4       GPIO_PIN9   /**< GPIO Pin for the echo pin of the backward sensor (US4) */
/** @} */

/** @} */ // End of Ultrasonic_Config group


#endif /* HAL_ULTRASONIC_ULTRASONIC_CONFIG_H_ */

