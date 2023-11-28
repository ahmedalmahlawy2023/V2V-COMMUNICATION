/**
 * @file USART_Private.h
 *
 * @brief Private header file for USART module.
 *
 * This file defines the private elements of the USART module,
 * including the register map and control bits.
 *
 * @Author: Project Team
 *
 * @Date: November 11, 2023
 */

#ifndef MCAL_USART_USART_PRIVATE_H_
#define MCAL_USART_USART_PRIVATE_H_



/** @addtogroup USART_Private USART Private
 * Private elements of the USART module.
 * @{
 */

/** @defgroup USART_Registers USART Registers
 * Register map for USART modules (USART1, USART2, USART6).
 * @{
 */
#define USART1_BASE_ADDRESS (0x40011000) /**< USART1 Base Address */
#define USART2_BASE_ADDRESS (0x40004400) /**< USART2 Base Address */
#define USART6_BASE_ADDRESS (0x40011400) /**< USART6 Base Address */

typedef struct {
    volatile u32 USART_SR;   /**< Status register */
    volatile u32 USART_DR;   /**< Data register */
    volatile u32 USART_BRR;  /**< Baud rate register */
    volatile u32 USART_CR1;  /**< Control register 1 */
    volatile u32 USART_CR2;  /**< Control register 2 */
    volatile u32 USART_CR3;  /**< Control register 3 */
    volatile u32 USART_GTPR; /**< Guard time and prescaler register */
} USART;

#define USART1 ((volatile USART *)(USART1_BASE_ADDRESS)) /**< USART1 Register Map */
#define USART2 ((volatile USART *)(USART2_BASE_ADDRESS)) /**< USART2 Register Map */
#define USART6 ((volatile USART *)(USART6_BASE_ADDRESS)) /**< USART6 Register Map */

/** @} */

/** @defgroup USART_Config_Bits USART Configuration Bits
 * Definition of control bits for USART configuration.
 * @{
 */
#define OVER_SAMPLING_BY_16 0 /**< Over-sampling mode: 16 bits */
#define OVER_SAMPLING_BY_8  1 /**< Over-sampling mode: 8 bits */

#define ENABLE  1 /**< Enable state */
#define DISABLE 0 /**< Disable state */

#define EVEN_PARITY 0 /**< Even parity */
#define ODD_PARITY  1 /**< Odd parity */

#define _8_DATA_BITS 0 /**< 8 data bits */
#define _9_DATA_BITS 1 /**< 9 data bits */

#define _1_STOP_BIT    0 /**< 1 stop bit */
#define _0_5_STOP_BIT  1 /**< 0.5 stop bit */
#define _2_STOP_BIT    2 /**< 2 stop bits */
#define _1_5_STOP_BIT  3 /**< 1.5 stop bits */

#define _3_BIT_SAMPLE_METHOD 0 /**< 3-bit sample method */
#define _1_BIT_SAMPLE_METHOD 1 /**< 1-bit sample method */

/** @} */

/** @defgroup USART_Control_Bits USART Control Bits
 * Definition of control bits for USART operation.
 * @{
 */
#define OVER8  15 /**< Oversampling mode: 8 bits */
#define UE     13 /**< USART Enable */
#define M      12 /**< Word length: 1 = 9 bits, 0 = 8 bits */
#define PCE    10 /**< Parity control enable */
#define PS     9  /**< Parity selection */
#define PEIE   8  /**< PE interrupt enable */
#define TCIE   6  /**< Transmission complete interrupt enable */
#define RXNEIE 5  /**< RXNE interrupt enable */
#define TE     3  /**< Transmitter enable */
#define RE     2  /**< Receiver enable */
#define STOP   12 /**< STOP bits: 00 = 1, 01 = 0.5, 10 = 2, 11 = 1.5 */
#define ONEBIT 11 /**< One sample bit method enable */
#define TXE    7  /**< Transmit data register empty */
#define TC     6  /**< Transmission complete */
#define RXNE   5  /**< Read data register not empty */

/** @} */

/** @} */ // end of USART_Private

#endif /* MCAL_USART_USART_PRIVATE_H_ */
