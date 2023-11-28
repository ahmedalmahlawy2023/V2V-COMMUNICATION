
/**
 * @file USART_Config.h
 *
 * @brief Configuration file for USART module.
 *
 * This file defines the configuration parameters for USART modules (USART1, USART2, USART6).
 *
 * @Author: Project Team
 *
 * @Date: November 11, 2023
 */

#ifndef MCAL_USART_USART_CONFIG_H_
#define MCAL_USART_USART_CONFIG_H_



/** @defgroup USART_Config USART Configuration
 * Configuration parameters for USART modules (USART1, USART2, USART6).
 * @{
 */

/** @defgroup USART1_Config USART1 Configuration
 * Configuration parameters for USART1.
 * @{
 */
#define USART1_OVER_SAMPLING_MODE           OVER_SAMPLING_BY_8 /**< Set USART1 oversampling mode. Options: OVER_SAMPLING_BY_16, OVER_SAMPLING_BY_8 */
#define USART1_STATE                        ENABLE            /**< Enable or disable USART1. Options: ENABLE, DISABLE */
#define USART1_WORD_LENGTH                  _8_DATA_BITS      /**< Set USART1 word length. Options: _9_DATA_BITS, _8_DATA_BITS */
#define USART1_PARITY_ENABLE_STATE          DISABLE           /**< Enable or disable USART1 parity. Options: ENABLE, DISABLE */
#define USART1_PARITY_SELECTION             EVEN_PARITY       /**< Set USART1 parity selection. Options: EVEN_PARITY, ODD_PARITY */
#define USART1_TRANSMISSION_COMPLETE_INT    DISABLE           /**< Enable or disable USART1 transmission complete interrupt. Options: ENABLE, DISABLE */
#define USART1_RECEIVING_COMPLETE_INT       DISABLE           /**< Enable or disable USART1 receiving complete interrupt. Options: ENABLE, DISABLE */
#define USART1_TRANSMITTER_ENABLE           ENABLE            /**< Enable or disable USART1 transmitter. Options: ENABLE, DISABLE */
#define USART1_RECIVER_ENABLE               ENABLE            /**< Enable or disable USART1 receiver. Options: ENABLE, DISABLE */
#define USART1_STOP_BITS                    _1_STOP_BIT       /**< Set USART1 stop bits. Options: _1_STOP_BIT, _0.5_STOP_BIT, _2_STOP_BIT, _1.5_STOP_BIT */
#define USART1_SAMPLE_METHOD                _1_BIT_SAMPLE_METHOD /**< Set USART1 sample method. Options: _3_BIT_SAMPLE_METHOD, _1_BIT_SAMPLE_METHOD */
#define USART1_BAUD_RATE                    9600              /**< Set USART1 baud rate. */
/** @} */

/** @defgroup USART2_Config USART2 Configuration
 * Configuration parameters for USART2.
 * @{
 */
#define USART2_OVER_SAMPLING_MODE           OVER_SAMPLING_BY_8 /**< Set USART2 oversampling mode. Options: OVER_SAMPLING_BY_16, OVER_SAMPLING_BY_8 */
#define USART2_STATE                        ENABLE            /**< Enable or disable USART2. Options: ENABLE, DISABLE */
#define USART2_WORD_LENGTH                  _8_DATA_BITS      /**< Set USART2 word length. Options: _9_DATA_BITS, _8_DATA_BITS */
#define USART2_PARITY_ENABLE_STATE          DISABLE           /**< Enable or disable USART2 parity. Options: ENABLE, DISABLE */
#define USART2_PARITY_SELECTION             EVEN_PARITY       /**< Set USART2 parity selection. Options: EVEN_PARITY, ODD_PARITY */
#define USART2_TRANSMISSION_COMPLETE_INT    DISABLE           /**< Enable or disable USART2 transmission complete interrupt. Options: ENABLE, DISABLE */
#define USART2_RECEIVING_COMPLETE_INT       DISABLE           /**< Enable or disable USART2 receiving complete interrupt. Options: ENABLE, DISABLE */
#define USART2_TRANSMITTER_ENABLE           ENABLE            /**< Enable or disable USART2 transmitter. Options: ENABLE, DISABLE */
#define USART2_RECIVER_ENABLE               ENABLE            /**< Enable or disable USART2 receiver. Options: ENABLE, DISABLE */
#define USART2_STOP_BITS                    _1_STOP_BIT       /**< Set USART2 stop bits. Options: _1_STOP_BIT, _0.5_STOP_BIT, _2_STOP_BIT, _1.5_STOP_BIT */
#define USART2_SAMPLE_METHOD                _1_BIT_SAMPLE_METHOD /**< Set USART2 sample method. Options: _3_BIT_SAMPLE_METHOD, _1_BIT_SAMPLE_METHOD */
#define USART2_BAUD_RATE                    9600              /**< Set USART2 baud rate. */
/** @} */

/** @defgroup USART6_Config USART6 Configuration
 * Configuration parameters for USART6.
 * @{
 */
#define USART6_OVER_SAMPLING_MODE           OVER_SAMPLING_BY_8 /**< Set USART6 oversampling mode. Options: OVER_SAMPLING_BY_16, OVER_SAMPLING_BY_8 */
#define USART6_STATE                        ENABLE            /**< Enable or disable USART6. Options: ENABLE, DISABLE */
#define USART6_WORD_LENGTH                  _8_DATA_BITS      /**< Set USART6 word length. Options: _9_DATA_BITS, _8_DATA_BITS */
#define USART6_PARITY_ENABLE_STATE          DISABLE           /**< Enable or disable USART6 parity. Options: ENABLE, DISABLE */
#define USART6_PARITY_SELECTION             EVEN_PARITY       /**< Set USART6 parity selection. Options: EVEN_PARITY, ODD_PARITY */
#define USART6_TRANSMISSION_COMPLETE_INT    DISABLE           /**< Enable or disable USART6 transmission complete interrupt. Options: ENABLE, DISABLE */
#define USART6_RECEIVING_COMPLETE_INT       ENABLE            /**< Enable or disable USART6 receiving complete interrupt. Options: ENABLE, DISABLE */
#define USART6_TRANSMITTER_ENABLE           ENABLE            /**< Enable or disable USART6 transmitter. Options: ENABLE, DISABLE */
#define USART6_RECIVER_ENABLE               ENABLE            /**< Enable or disable USART6 receiver. Options: ENABLE, DISABLE */
#define USART6_STOP_BITS                    _1_STOP_BIT       /**< Set USART6 stop bits. Options:**/
#endif /* MCAL_USART_USART_CONFIG_H_ */
