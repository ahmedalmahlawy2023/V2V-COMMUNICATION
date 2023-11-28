/*
 * @file USART_Interface.h
 *
 * @brief Interface file for USART module.
 *
 * This file declares the interface functions and pin configurations for USART modules (USART1, USART2, USART6).
 *
 * @Author: Project Team
 *
 * @Date: November 11, 2023
 */

#ifndef MCAL_USART_USART_INTERFACE_H_
#define MCAL_USART_USART_INTERFACE_H_

/** @defgroup USART_Pins USART Pins
 * Pin configurations for USART modules.
 * @{
 */
#define MUSART1_TX_PIN GPIO_PIN6 /**< USART1 Transmit Pin */
#define MUSART1_RX_PIN GPIO_PIN7 /**< USART1 Receive Pin */

#define MUSART2_TX_PIN GPIO_PIN2 /**< USART2 Transmit Pin */
#define MUSART2_RX_PIN GPIO_PIN3 /**< USART2 Receive Pin */

#define MUSART6_TX_PIN GPIO_PIN11 /**< USART6 Transmit Pin */
#define MUSART6_RX_PIN GPIO_PIN12 /**< USART6 Receive Pin */

#define MUSART6_PORT GPIO_PORTA /**< USART6 GPIO Port */
#define MUSART2_PORT GPIO_PORTA /**< USART2 GPIO Port */
#define MUSART1_PORT GPIO_PORTB /**< USART1 GPIO Port */

#define MUSART1_ALF GPIO_ALTFN_7 /**< USART1 Alternate Function */
#define MUSART2_ALF GPIO_ALTFN_7 /**< USART2 Alternate Function */
#define MUSART6_ALF GPIO_ALTFN_8 /**< USART6 Alternate Function */
/** @} */

/**
 * @brief Initialize USART1.
 */
void MUSART1_voidInit(void);

/**
 * @brief Transmit a byte via USART1.
 * @param Copy_u8Data: The byte to be transmitted.
 */
void MUSART1_voidTransmitData(u8 Copy_u8Data);

/**
 * @brief Receive a byte via USART1.
 * @return The received byte.
 */
u8 MUSART1_u8ReciveData(void);

/**
 * @brief Receive a string via USART1.
 * @param PC_String: Pointer to the received string.
 */
void MUSART1_voidReciveString(u8* PC_String);

/**
 * @brief Send a string via USART1.
 * @param PC_String: Pointer to the string to be sent.
 */
void MUSART1_voidSendString(u8* PC_String);

/**
 * @brief Initialize USART2.
 */
void MUSART2_voidInit(void);

/**
 * @brief Transmit a byte via USART2.
 * @param Copy_u8Data: The byte to be transmitted.
 */
void MUSART2_voidTransmitData(u8 Copy_u8Data);

/**
 * @brief Receive a byte via USART2.
 * @return The received byte.
 */
u8 MUSART2_u8ReciveData(void);

/**
 * @brief Receive a string via USART2.
 * @param PC_String: Pointer to the received string.
 */
void MUSART2_voidReciveString(u8* PC_String);

/**
 * @brief Send a string via USART2.
 * @param PC_String: Pointer to the string to be sent.
 */
void MUSART2_voidSendString(u8* PC_String);

/**
 * @brief Initialize USART6.
 */
void MUSART6_voidInit(void);

/**
 * @brief Transmit a byte via USART6.
 * @param Copy_u8Data: The byte to be transmitted.
 */
void MUSART6_voidTransmitData(u8 Copy_u8Data);

/**
 * @brief Receive a byte via USART6.
 * @return The received byte.
 */
u8 MUSART6_u8ReciveData(void);

/**
 * @brief Receive a string via USART6.
 * @param PC_String: Pointer to the received string.
 */
void MUSART6_voidReciveString(u8* PC_String);

/**
 * @brief Send a string via USART6.
 * @param PC_String: Pointer to the string to be sent.
 */
void MUSART6_voidSendString(u8* PC_String);

#endif /* MCAL_USART_USART_INTERFACE_H_ */
