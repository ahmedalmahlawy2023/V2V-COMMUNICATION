/** ****************************************************************************
 *
 * @File RCC_Program.c
 *
 * @brief this file contains functions related to RCC Module
 *
 * @author Project Team
 *
 * @date 6/11/2023
 *
 ****************************************************************************** */
/*******************************************************************************
 *                          	Standard Types                                 *
 *******************************************************************************/
#include "../../LIB/ITI_STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
/*******************************************************************************
 *                          	MCAL Components                                 *
 *******************************************************************************/
#include "RCC_Interface.h"
#include "RCC_Private.h"
#include "RCC_Config.h"
/*******************************************************************************
 *                          	APIs Implementation                            *
 *******************************************************************************/
 /**
 * @brief Initialize the RCC (Reset and Clock Control) module.
 *
 * This function configures the RCC module based on the selected clock source.
 * The clock source can be HSI, HSE, or PLL, and the AHB prescaler is also configured.
 *
 * @note This function should be called at the beginning of the program.
 */
void MRCC_VoidInit(void)
{
#if 	CLOCK_TYPE == HSI

	//Enable HSI Clock (y3ny b2lo feh el source da m3aya mn dmn eloptions ele mmkn a5tar mnha dmn el system clock)
	SET_BIT(MRCC->RCC_CR,HSION);
	// wait until HSI ready flag is on
	//	while(GET_BIT(MRCC->RCC_CR,1) == 0);
	//Choosing HSI as Clock Source(kda b5tar fe el mux eltany)
	CLR_BIT(MRCC->RCC_CFGR,SW0);
	CLR_BIT(MRCC->RCC_CFGR,SW1);



#elif 	CLOCK_TYPE == HSE
	//Enable HSE Clock (y3ny b2lo feh el source da m3aya mn dmn eloptions ele mmkn a5tar mnha dmn el system clock)
	SET_BIT(MRCC->RCC_CR,HSEON);
	//Choosing HSI as Clock Source(kda b5tar fe el mux eltany)
	SET_BIT(MRCC->RCC_CFGR,SW0);
	CLR_BIT(MRCC->RCC_CFGR,SW1);

#elif	CLOCK_TYPE ==  PLL
	/*
	 f(VCO clock)=f(PLL clock input)*(PLLN/PLLM)    VCO hya elclock source ele 25trto ele hwa HSE OR HSI
	 f(PLL general clock o/p)=f(VCO clock)/PLLP
	 f(USB OTG FS, SDIO, RNG clock o/p)=f(VCO clock)/PLLQ
	 */
	//lazm elregister da at4t8l 3leh klo we ana 2afl enable el PLL

	//Selecting which clock will be operated on in PLL ct
	MRCC->RCC_PLLCFGR|= (PLL_INPUT_SOURCE << PLLSRC) ;

	//Setting PLLP (Prescaler Value that performed on the clock that out from PLL ct  going to SYS Clock MUX as PLL clock)
	MRCC->RCC_PLLCFGR|= PLLP_VALUE << PLLP0 ; // the value of clock freq out of this prescaler must no exceeded 84MHZ

	//Setting PLLN (Multiplication Value for VCO that performed on the clock that will be operated on PLL ct this clock is either HSE or HSI)
#if ((PLLN_VALUE >=192)&&(PLLN_VALUE <=432))

	MRCC->RCC_PLLCFGR|= PLLN_VALUE << PLLN0 ;
#else
#error "Wrong Configuration For PLLN_VALUE"
#endif
	//Setting PLLM (Division Factor for VCO(main PLL input Clock) that performed on the clock that will be operated on PLL ct this clock is either HSE or HSI)
#if ((PLLM_VALUE >=2)&&(PLLM_VALUE <=63))

	MRCC->RCC_PLLCFGR|= PLLM_VALUE << PLLM0 ;
#else
#error "Wrong Configuration For PLLM_VALUE"
#endif

	//Enable PLL Ct (y3ny b2lo feh el source da m3aya mn dmn eloptions ele mmkn a5tar mnha dmn el system clock)
	SET_BIT(MRCC->RCC_CR,PLLON);
	//Choosing PLLclock as Clock Source (kda b5tar fe el mux eltany)
	SET_BIT(MRCC->RCC_CFGR,SW0);
	SET_BIT(MRCC->RCC_CFGR,SW1);

#endif /* For Choosing Clock Type*/
	//DETERMINING AHB PRESCALER
	MRCC -> RCC_CFGR &= AHB_PRESCALAR_MASK;
	MRCC -> RCC_CFGR |= (AHB_PRESCALER << 4); /*AHB clock = SYSTEM CLOCK / AHP_PRESCALAR*/

}
/**
 * @brief Enable a specific peripheral on a particular bus.
 *
 * This function enables a specific peripheral on the selected bus.
 *
 * @param Copy_U8PeriphralBus The bus to which the peripheral is connected (AHB1, AHB2, APB1, or APB2).
 * @param Copy_U8PeriphralNumber The peripheral number to enable.
 */
void MRCC_VoidEnablePeriphral(u8 Copy_U8PeriphralBus,u8 Copy_U8PeriphralNumber)
{
	// First Switch on the bus to Filter the periphrals which will be operated on 
	switch (Copy_U8PeriphralBus)
	{
		// after choosing the bus then going to choose the periphral number corresponding to bits of this periphral on this bus (to know which periphrals are on this bus go to memory map then go to RCC registers which enable them by knowing the bus first)
		case AHB1_BUS: SET_BIT(MRCC->RCC_AHB1ENR,Copy_U8PeriphralNumber);   break;
		case AHB2_BUS: SET_BIT(MRCC->RCC_AHB2ENR,Copy_U8PeriphralNumber);	break;
		case APB1_BUS: SET_BIT(MRCC->RCC_APB1ENR,Copy_U8PeriphralNumber);	break;
		case APB2_BUS: SET_BIT(MRCC->RCC_APB2ENR,Copy_U8PeriphralNumber);	break;
	}
}
/**
 * @brief Disable a specific peripheral on a particular bus.
 *
 * This function disables a specific peripheral on the selected bus.
 *
 * @param Copy_U8PeriphralBus The bus to which the peripheral is connected (AHB1, AHB2, APB1, or APB2).
 * @param Copy_U8PeriphralNumber The peripheral number to disable.
 */
void MRCC_VoidDisablePeriphral(u8 Copy_U8PeriphralBus,u8 Copy_U8PeriphralNumber)
{
	// First Switch on the bus to Filter the periphrals which will be operated on 
	switch (Copy_U8PeriphralBus)
	{
		// after choosing the bus then going to choose the periphral number corresponding to bits of this periphral on this bus (to know which periphrals are on this bus go to memory map then go to RCC registers which enable them by knowing the bus first)
		case AHB1_BUS: CLR_BIT(MRCC->RCC_AHB1ENR,Copy_U8PeriphralNumber);   break;
		case AHB2_BUS: CLR_BIT(MRCC->RCC_AHB2ENR,Copy_U8PeriphralNumber);	break;
		case APB1_BUS: CLR_BIT(MRCC->RCC_APB1ENR,Copy_U8PeriphralNumber);	break;
		case APB2_BUS: CLR_BIT(MRCC->RCC_APB2ENR,Copy_U8PeriphralNumber);	break;
	}
}
