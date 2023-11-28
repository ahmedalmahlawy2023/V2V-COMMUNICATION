#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_

/** ****************************************************************************
 *
 * @File RCC_Config.h
 *
 * @brief this file contains confirations related to RCC Module
 *
 * @author Project Team
 *
 * @date 6/11/2023
 *
 ****************************************************************************** */
 
/*
	HSI
	HSE
	PLL
*/
#define CLOCK_TYPE  HSI



/*
 * _2_Prescaler
 * _4_Prescaler
 * _6_Prescaler
 * _8_Prescaler
 */
#define PLLP_VALUE		_2_Prescaler



/* this Configuration must be 192 <= PLLN <=432 */
#define PLLN_VALUE		192



/* this Configuration must be 2 <= PLLM <=63 */
#define PLLM_VALUE    2

/*
 *	HSI
 *	HSE
 */
#define PLL_INPUT_SOURCE	HSI

/*
  	AHP_NO_PRESCALAR
    AHP_2_PRESCALAR
    AHP_4_PRESCALAR
    AHP_8_PRESCALAR
    AHP_16_PRESCALAR
    AHP_64_PRESCALAR
    AHP_128_PRESCALAR
    AHP_256_PRESCALAR
    AHP_512_PRESCALAR

 */

#define AHB_PRESCALER    AHP_NO_PRESCALAR


#endif 
