/******************************************************************************
 *
 * @file Ultrasonic_Interface.h
 *
 * @brief Interface file for Ultrasonic module
 *
 * This file contains function prototypes and enumerations for the Ultrasonic module.
 *
 * @Author: Project Team 
 *
 * @Date: November 11, 2023
 *
 *****************************************************************************/
#ifndef HAL_ULTRASONIC_ULTRASONIC_INTERFACE_H_
#define HAL_ULTRASONIC_ULTRASONIC_INTERFACE_H_

/**
 * @defgroup Ultrasonic_Interface Ultrasonic Interface
 * @{
 */

/**
 * @brief Enumeration for Ultrasonic sensors.
 */
typedef enum
{
    FORWARD_US = 1, /**< Forward Ultrasonic Sensor */
    LEFT_US,        /**< Left Ultrasonic Sensor */
    RIGHT_US,       /**< Right Ultrasonic Sensor */
    BACKWARD_US     /**< Backward Ultrasonic Sensor */
} USNUM_t;
/**
 * @brief Initialize the Ultrasonic module.
 *
 * This function initializes the Ultrasonic module by configuring GPIO pins.
 */
void HUS_voidInit(void);

/**
 * @brief Calculate the distance measured by the Ultrasonic sensor.
 *
 * @param[in] A_USNUM_t_Ultrasonic_Num The Ultrasonic sensor to calculate the distance for.
 * @return Distance measured by the Ultrasonic sensor in centimeters.
 */
f32 HUS_f32CalcDistance(USNUM_t A_USNUM_t_Ultrasonic_Num);

/** @} */ // End of Ultrasonic_Interface group



#endif /* HAL_ULTRASONIC_INTERFACE_H_ */
