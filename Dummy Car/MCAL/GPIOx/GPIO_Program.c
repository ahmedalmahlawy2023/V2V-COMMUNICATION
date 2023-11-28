/** *****************************************************************************
 *
 * @File GPIO_Program.c
 *
 * @brief this file contains functions related to GPIO Module
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
#include "GPIO_private.h"
#include "GPIO_Config.h"
#include "GPIO_interface.h"

/*******************************************************************************
 *                          	APIs Implementation                            *
 *******************************************************************************/

/**
 * @brief Set the mode of a specific GPIO pin on a selected port.
 *
 * This function configures the mode of a GPIO pin on a specified GPIO port.
 *
 * @param Copy_u8PortName The name of the GPIO port (e.g., GPIO_PORTA, GPIO_PORTB).
 * @param Copy_u8PinNumber The number of the GPIO pin to configure.
 * @param Copy_u8PinMode The mode to set for the GPIO pin (e.g., GPIO_MODE_INPUT, GPIO_MODE_OUTPUT).
 *
 * @note The function uses the Copy_u8PortName and Copy_u8PinNumber parameters to determine
 * the specific GPIO pin to configure. It sets the pin mode based on the provided mode.
 */

void MGPIO_voidSetPinMode(u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8PinMode)
{
	if( Copy_u8PinNumber < 16)
	{
		switch(Copy_u8PortName)
		{
		// every PIN configured with 2 bits
		case GPIO_PORTA : MGPIOA->MODER |= (u32)(Copy_u8PinMode << (2U * Copy_u8PinNumber));   break;
		case GPIO_PORTB : MGPIOB->MODER |= (u32)(Copy_u8PinMode << (2U * Copy_u8PinNumber));   break;
#if STMmodel==STM32F401cc
		case GPIO_PORTC :
			if(Copy_u8PinNumber > 12 ) 
			{
				MGPIOC->MODER |= (u32)(Copy_u8PinMode << (2U * Copy_u8PinNumber));
			}
			else 
			{
				// report an error : port c pin number is out of boundary
			}
			break;
#elif STMmodel == 2
		case GPIO_PORTC : MGPIOC->MODER |= (u32)(Copy_u8PinMode << (2U * Copy_u8PinNumber));   break;
		case GPIO_PORTD : MGPIOD->MODER |= (u32)(Copy_u8PinMode << (2U * Copy_u8PinNumber));   break;
		case GPIO_PORTE : MGPIOE->MODER |= (u32)(Copy_u8PinMode << (2U * Copy_u8PinNumber));   break;
		case GPIO_PORTH : MGPIOH->MODER |= (u32)(Copy_u8PinMode << (2U * Copy_u8PinNumber));   break;
#endif
		default    :  /* report an error : port name fault*/ break;

		}
	}
	else
	{
		// report an error : pin number is out of boundary
	}
}
/**
 * @brief Set the mode of an entire GPIO port.
 *
 * This function configures the mode of all pins in a GPIO port.
 *
 * @param Copy_u8PortName The name of the GPIO port (e.g., GPIO_PORTA, GPIO_PORTB).
 * @param Copy_u8PortMode The mode to set for the GPIO port (e.g., GPIO_MODE_INPUT, GPIO_MODE_OUTPUT).
 *
 * @note The function sets the mode of all pins in the specified port to the provided mode.
 */
void MGPIO_voidSetPortMode(u8 Copy_u8PortName, u8 Copy_u8PortMode)
{
	if (Copy_u8PortMode== GPIO_MODE_INPUT)
	{
		switch (Copy_u8PortName)
		{
		case GPIO_PORTA: MGPIOA->MODER=Copy_u8PortMode;  	break;

		case GPIO_PORTB: MGPIOB->MODER=Copy_u8PortMode;		break;

		default: /* error state wrong port name*/ 			 break;
		}
	}
	else if (Copy_u8PortMode== GPIO_MODE_OUTPUT)
	{
		switch (Copy_u8PortName)
		{
		case GPIO_PORTA: MGPIOA->MODER=(MGPIOA->MODER &0) | 0x55555555;  		break;

		case GPIO_PORTB: MGPIOB->MODER=(MGPIOA->MODER &0) | 0x55555555;			break;


		default: /* error state wrong port name*/ 			break;
		}
	}
	else if (Copy_u8PortMode== GPIO_MODE_ALTF)
	{
		switch (Copy_u8PortName)
		{
		case GPIO_PORTA: MGPIOA->MODER=(MGPIOA->MODER &0) | 0xAAAAAAAA;  		break;

		case GPIO_PORTB: MGPIOB->MODER=(MGPIOA->MODER &0) | 0xAAAAAAAA;			break;

		default: /* error state wrong port name*/ 			break;
		}
	}
	else if (Copy_u8PortMode== GPIO_MODE_ANALOG)
	{
		switch (Copy_u8PortName)
		{
		case GPIO_PORTA: MGPIOA->MODER=(MGPIOA->MODER &0) | 0xFFFFFFFF;  		break;

		case GPIO_PORTB: MGPIOB->MODER=(MGPIOA->MODER &0) | 0xFFFFFFFF;			break;

		default: /* error state wrong port name*/ 			break;
		}
	}
	else 
	{
		// error state wrong PortMode
	}
}
/**
 * @brief Set the output mode for a specific GPIO pin on a selected port.
 *
 * This function configures the output mode for a specific GPIO pin on a specified GPIO port.
 *
 * @param Copy_u8PortName The name of the GPIO port (e.g., GPIO_PORTA, GPIO_PORTB).
 * @param Copy_u8PinNumber The number of the GPIO pin to configure (0-15).
 * @param Copy_u8OutMode The output mode to set for the GPIO pin (e.g., GPIO_OUT_PP, GPIO_OUT_OD).
 *
 * @note The function uses the Copy_u8PortName and Copy_u8PinNumber parameters to determine
 * the specific GPIO pin to configure. It sets the output mode based on the provided mode.
 */
void MGPIO_voidSetOutPutMode(u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8OutMode)
{
	if(Copy_u8PinNumber < 16)
	{
		switch(Copy_u8PortName)
		{
		case GPIO_PORTA : MGPIOA->OTYPER |= (u16)(Copy_u8OutMode <<  Copy_u8PinNumber);   break; //as2l mahran kda el u16 elmfrood mlha4 lzam s7 wla la
		case GPIO_PORTB : MGPIOB->OTYPER |= (u16)(Copy_u8OutMode <<  Copy_u8PinNumber);   break;
		case GPIO_PORTC :
			if(Copy_u8PinNumber > 12 ) 
			{
				MGPIOC->OTYPER |= (u16)(Copy_u8OutMode << Copy_u8PinNumber);
			}
			else 
			{
				// report an error : port c pin number is out of boundary
			}
			break;
		default:/* report an error : port name fault*/ break;
		}
	}
	else
	{
		// report an error : pin number is out of boundary
	}
}
/**
 * @brief Set the output speed for a specific GPIO pin on a selected port.
 *
 * This function configures the output speed for a specific GPIO pin on a specified GPIO port.
 *
 * @param Copy_u8PortName The name of the GPIO port (e.g., GPIO_PORTA, GPIO_PORTB).
 * @param Copy_u8PinNumber The number of the GPIO pin to configure (0-15).
 * @param Copy_u8OutSpeed The output speed to set for the GPIO pin (e.g., GPIO_SPEED_LOW, GPIO_SPEED_HIGH).
 *
 * @note The function uses the Copy_u8PortName and Copy_u8PinNumber parameters to determine
 * the specific GPIO pin to configure. It sets the output speed based on the provided speed.
 */
void MGPIO_voidSetOutputSpeed(u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8OutSpeed)
{
	if( Copy_u8PinNumber < 16)
	{
		switch(Copy_u8PortName)
		{
		// every PIN configured with 2 bits
		case GPIO_PORTA : MGPIOA->OSPEEDR |= (u32)(Copy_u8OutSpeed << (2U * Copy_u8PinNumber));   break;
		case GPIO_PORTB : MGPIOB->OSPEEDR |= (u32)(Copy_u8OutSpeed << (2U * Copy_u8PinNumber));   break;
		case GPIO_PORTC :
			if(Copy_u8PinNumber > 12) 
			{
				MGPIOC->OSPEEDR |= (u32)(Copy_u8OutSpeed << (2U * Copy_u8PinNumber));
			}
			else 
			{
				// report an error : port c pin number is out of boundary
			}
			break;
		default:/* report an error : port name fault*/ break;

		}
	}
	else
	{
		// report an error : pin number is out of boundary
	}
}
/**
 * @brief Set the pull-up/pull-down state for a specific GPIO pin on a selected port.
 *
 * This function configures the pull-up or pull-down state for a specific GPIO pin on a specified GPIO port.
 *
 * @param Copy_u8PortName The name of the GPIO port (e.g., GPIO_PORTA, GPIO_PORTB).
 * @param Copy_u8PinNumber The number of the GPIO pin to configure (0-15).
 * @param Copy_u8PullState The pull-up/pull-down state to set for the GPIO pin (e.g., GPIO_PULL_UP, GPIO_PULL_DOWN).
 *
 * @note The function uses the Copy_u8PortName and Copy_u8PinNumber parameters to determine
 * the specific GPIO pin to configure. It sets the pull-up/pull-down state based on the provided state.
 */
void MGPIO_voidSetPullState(u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8PullState)
{
	if( Copy_u8PinNumber < 16)
	{
		switch(Copy_u8PortName)
		{
		// every PIN configured with 2 bits
		case GPIO_PORTA : MGPIOA->PUPDR |= (u32)(Copy_u8PullState << (2U * Copy_u8PinNumber));   break;
		case GPIO_PORTB : MGPIOB->PUPDR |= (u32)(Copy_u8PullState << (2U * Copy_u8PinNumber));   break;
		case GPIO_PORTC :
			if(Copy_u8PinNumber > 12) 
			{
				MGPIOC->PUPDR |= (u32)(Copy_u8PullState << (2U * Copy_u8PinNumber));
			}
			else 
			{
				// report an error : port c pin number is out of boundary
			}
			break;
		default  /* report an error : port name fault*/  : break;
		}
	}
	else
	{
		// report an error : pin number is out of boundary
	}
}
/**
 * @brief Get the value of a specific GPIO pin on a selected port.
 *
 * This function reads and returns the value of a specific GPIO pin on a specified GPIO port.
 *
 * @param Copy_u8PortName The name of the GPIO port (e.g., GPIO_PORTA, GPIO_PORTB).
 * @param Copy_u8PinNumber The number of the GPIO pin to read (0-15).
 *
 * @return The value of the GPIO pin (GPIO_HIGH or GPIO_LOW).
 *
 * @note The function uses the Copy_u8PortName and Copy_u8PinNumber parameters to determine
 * the specific GPIO pin to read and returns its value.
 */
u8 MGPIO_u8GetPinValue(u8 Copy_u8PortName, u8 Copy_u8PinNumber)
{
	u8 L_u8PinValue;

	if(Copy_u8PinNumber < 16)
	{
		switch(Copy_u8PortName)
		{
		case GPIO_PORTA : L_u8PinValue = GET_BIT(MGPIOA->IDR, Copy_u8PinNumber);   break;
		case GPIO_PORTB : L_u8PinValue = GET_BIT(MGPIOB->IDR, Copy_u8PinNumber);   break;
		case GPIO_PORTC :
			if(Copy_u8PinNumber > 12) 
			{
				L_u8PinValue = GET_BIT(MGPIOC->IDR, Copy_u8PinNumber);
			}
			else 
			{
				// report an error : port c pin number is out of boundary
			}
			break;
		default :  /* report an error : port name fault*/   break;
		}
	}
	else
	{
		// report an error : pin number is out of boundary
	}

	return L_u8PinValue;
}
/**
 * @brief Set the value of a specific GPIO pin on a selected port.
 *
 * This function sets a specific GPIO pin on a specified GPIO port.
 *
 * @param Copy_u8PortName The name of the GPIO port (e.g., GPIO_PORTA, GPIO_PORTB).
 * @param Copy_u8PinNumber The number of the GPIO pin to read (0-15).
 * @param Copy_u8PinValue The value to set for the GPIO pin.
 *
 * @return The value of the GPIO pin (GPIO_HIGH or GPIO_LOW).
 *
 * @note The function uses the Copy_u8PortName and Copy_u8PinNumber parameters to determine
 * the specific GPIO pin to read and returns its value.
 */
void MGPIO_voidSetPinValue(u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8PinValue)
{
	if( Copy_u8PinNumber < 16)
	{
		if(Copy_u8PinValue == GPIO_HIGH)
		{
			switch(Copy_u8PortName)
			{
			case GPIO_PORTA : SET_BIT(MGPIOA->ODR, Copy_u8PinNumber);  break;
			case GPIO_PORTB : SET_BIT(MGPIOB->ODR, Copy_u8PinNumber);  break;
			case GPIO_PORTC :
				if(Copy_u8PinNumber > 12 ) 
				{
					SET_BIT(MGPIOC->ODR, Copy_u8PinNumber);
				}
				else 
				{
					// report an error : port c pin number is out of boundary
				}
				break;
			default :  /* report an error : port name fault*/   break;
			}
		}
		else if(Copy_u8PinValue == GPIO_LOW)
		{
			switch(Copy_u8PortName)
			{
			// every PIN configured with 2 bits
			case GPIO_PORTA : CLR_BIT(MGPIOA->ODR, Copy_u8PinNumber);  break;
			case GPIO_PORTB : CLR_BIT(MGPIOB->ODR, Copy_u8PinNumber);  break;
			case GPIO_PORTC : if(Copy_u8PinNumber > 12)
			{
				CLR_BIT(MGPIOC->ODR, Copy_u8PinNumber);
			}
			else 
			{
				// report an error : port c pin number is out of boundary
			}
			break;
			default:  /* report an error : port name fault*/    break;
			}
		}
		else
		{
			// // report an error : pin Value is wrong
		}

	}
	else {
		// report an error : pin number is out of boundary
	}
}
/**
 * @brief Directly set or reset a specific GPIO pin on a selected port.
 *
 * This function allows you to directly set or reset a specific GPIO pin on a specified GPIO port.
 *
 * @param Copy_u8PortName The name of the GPIO port (e.g., GPIO_PORTA, GPIO_PORTB).
 * @param Copy_u8PinNumber The number of the GPIO pin to set or reset.
 * @param Copy_u8SetResetState The state to set or reset the GPIO pin (e.g., GPIO_HIGH, GPIO_LOW).
 *
 * @note The function uses the Copy_u8PortName and Copy_u8PinNumber parameters to determine
 * the specific GPIO pin to set or reset. It sets the pin according to the provided state.
 */
void MGPIO_voidDirectSetReset(u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8SetResetState)
{
	if( Copy_u8PinNumber < 16)
	{
		if(Copy_u8SetResetState == GPIO_HIGH)
		{
			switch(Copy_u8PortName)
			{
			// write 1 to set the pin
			case GPIO_PORTA : MGPIOA->BSRR = (u32)(1U << Copy_u8PinNumber);   break;
			case GPIO_PORTB : MGPIOB->BSRR = (u32)(1U << Copy_u8PinNumber);   break;
			case GPIO_PORTC :
				if(Copy_u8PinNumber > 12 ) 
				{
					MGPIOC->BSRR = (u32)(1U << Copy_u8PinNumber);
				}
				else 
				{
					// report an error : port c pin number is out of boundary
				}
				break;
			default    : /* report an error : port name fault*/ break;

			}
		}
		else if(Copy_u8SetResetState == GPIO_LOW)
		{
			Copy_u8PinNumber+= 16; // to access higher 16 bits in the register
			switch(Copy_u8PortName)
			{
			// write 1 to reset the pin
			case GPIO_PORTA : MGPIOA->BSRR = (u32)(1U << Copy_u8PinNumber);   break;
			case GPIO_PORTB : MGPIOB->BSRR = (u32)(1U << Copy_u8PinNumber);   break;
			case GPIO_PORTC :
				if(Copy_u8PinNumber > 12 ) 
				{
					MGPIOC->BSRR = (u32)(1U << Copy_u8PinNumber);
				}
				else {
					// report an error : port c pin number is out of boundary
				}
				break;
			default    :/* report an error : port name fault*/  break;
			}
		}
	}
	else
	{
		// report an error : pin number is out of boundary
	}
}
/**
 * @brief Set the value of an entire GPIO port.
 *
 * This function sets the value of all pins in a GPIO port to a specific value.
 *
 * @param Copy_u8PortName The name of the GPIO port (e.g., GPIO_PORTA, GPIO_PORTB).
 * @param Copy_u16PortValue The value to set for the entire GPIO port.
 *
 * @note The function sets the value of all pins in the specified port to the provided value.
 */
void MGPIO_voidSetPortValue(u8 Copy_u8PortName, u16 Copy_u16PortValue)
{
	switch(Copy_u8PortName)
	{
	case GPIO_PORTA : MGPIOA->ODR = 0xFFFFFFFF; break;
	case GPIO_PORTB : MGPIOB->ODR = 0xFFFFFFFF; break;
	//case GPIO_PORTC : MGPIOC->ODR = (u16)Copy_u16PortValue; break;
	default :/* report an error : port name fault*/  break;
	}
}
/**
 * @brief Set the alternate function of a specific GPIO pin on a selected port.
 *
 * This function configures the alternate function of a specific GPIO pin on a specified GPIO port.
 *
 * @param Copy_u8PortName The name of the GPIO port (e.g., GPIO_PORTA, GPIO_PORTB).
 * @param Copy_u8PinNum The number of the GPIO pin to configure.
 * @param copy_u8AltFun The alternate function to set for the GPIO pin.
 *
 * @note The function uses the Copy_u8PortName and Copy_u8PinNum parameters to determine
 * the specific GPIO pin to configure. It sets the alternate function based on the provided function code.
 */
void MGPIO_voidSetPinAltFun(u8 Copy_u8PortName, u8 Copy_u8PinNum, u8 copy_u8AltFun)
{
	if(Copy_u8PinNum <= 7U)
	{
		switch(Copy_u8PortName)
		{
		case GPIO_PORTA:
			MGPIOA->AFRL &= ~((0b1111)<<(Copy_u8PinNum*4U));
			MGPIOA->AFRL |=(copy_u8AltFun<<(Copy_u8PinNum*4U));
			break;
		case GPIO_PORTB: MGPIOB->AFRL= (u32)((MGPIOB->AFRL&(~(0b1111<<(Copy_u8PinNum*4U))))|(copy_u8AltFun<<(Copy_u8PinNum*4U))); break;
#if (STM_MODEL  ==  STM32F401CC)
		case GPIO_PORTC:
			if(Copy_u8PinNum >= 13)
			{
				MGPIOC->AFRL=(u32) ((MGPIOC->AFRL&(~(0b1111<<(Copy_u8PinNum*4U))))|(copy_u8AltFun<<(Copy_u8PinNum*4U))); break;
			}
			else
			{
				//ERROR PINS<13
			}
			break;

#elif (STM_MODEL  !=  STM32F401CC)
		case MGPIOC_PORT: MGPIOC->AFRL= (u32)((MGPIOC->AFRL&(~(0b1111<<(Copy_u8PinNum*4U))))|(copy_u8AltFun<<(Copy_u8PinNum*4U))); break;
		case MGPIOD_PORT: MGPIOD->AFRL= (u32)((MGPIOD->AFRL&(~(0b1111<<(Copy_u8PinNum*4U))))|(copy_u8AltFun<<(Copy_u8PinNum*4U))); break;
		case MGPIOE_PORT: MGPIOE->AFRL= (u32)((MGPIOE->AFRL&(~(0b1111<<(Copy_u8PinNum*4U))))|(copy_u8AltFun<<(Copy_u8PinNum*4U))); break;
		case MGPIOH_PORT: MGPIOH->AFRL= (u32)((MGPIOH->AFRL&(~(0b1111<<(Copy_u8PinNum*4U))))|(copy_u8AltFun<<(Copy_u8PinNum*4U))); break;
#endif
		default:
			//error WRONG PORT
			break;
		}

	}
	else if(Copy_u8PinNum <=15U)
	{
		Copy_u8PinNum -=8 ;
		switch(Copy_u8PortName)
		{
		case GPIO_PORTA:
			//	MGPIOA->AFRH= (u32)((MGPIOA->AFRH&(~(0b1111<<(Copy_u8PinNum*4U))))|(copy_u8AltFun<<(Copy_u8PinNum*4U))); break;
			MGPIOA->AFRH &= ~((0b1111)<<(Copy_u8PinNum*4U));
			MGPIOA->AFRH |=(copy_u8AltFun<<(Copy_u8PinNum*4U));
			break;
		case GPIO_PORTB: MGPIOB->AFRH= (u32)((MGPIOB->AFRH&(~(0b1111<<(Copy_u8PinNum*4U))))|(copy_u8AltFun<<(Copy_u8PinNum*4U))); break;
#if 	(STM_MODEL  ==  STM32F401CC)

		case GPIO_PORTC:
			if(Copy_u8PinNum >= 13)
			{
				MGPIOC->AFRH= (u32)((MGPIOC->AFRH&(~(0b1111<<(Copy_u8PinNum*4U))))|(copy_u8AltFun<<(Copy_u8PinNum*4U))); break;
			}
			else
			{
				//ERROR PIN C <13
			}
			break;

#elif (STM_MODEL  !=  STM32F401CC)
		case MGPIOC_PORT: MGPIOC->AFRH= (u32)((MGPIOC->AFRH&(~(0b1111<<(Copy_u8PinNum*4U))))|(copy_u8AltFun<<(Copy_u8PinNum*4U))); break;
		case MGPIOD_PORT: MGPIOD->AFRH= (u32)((MGPIOD->AFRH&(~(0b1111<<(Copy_u8PinNum*4U))))|(copy_u8AltFun<<(Copy_u8PinNum*4U))); break;
		case MGPIOE_PORT: MGPIOE->AFRH= (u32)((MGPIOE->AFRH&(~(0b1111<<(Copy_u8PinNum*4U))))|(copy_u8AltFun<<(Copy_u8PinNum*4U))); break;
		case MGPIOH_PORT: MGPIOH->AFRH= (u32)((MGPIOH->AFRH&(~(0b1111<<(Copy_u8PinNum*4U))))|(copy_u8AltFun<<(Copy_u8PinNum*4U))); break;
#endif
		default:
			//error WRONG PORT
			break;
		}
	}
	else
	{
		//error PIN >15
	}
}
/**
 * @brief Toggle the state of a specific GPIO pin on a selected port.
 *
 * This function toggles the state of a specific GPIO pin on a specified GPIO port.
 *
 * @param Copy_u8PortName The name of the GPIO port (e.g., GPIO_PORTA, GPIO_PORTB).
 * @param Copy_u8PinNumber The number of the GPIO pin to toggle.
 *
 * @note The function uses the Copy_u8PortName and Copy_u8PinNumber parameters to determine
 * the specific GPIO pin to toggle. It toggles the pin's state.
 */
void MGPIO_voidTogglePin(u8 Copy_u8PortName ,u8 Copy_u8PinNumber )
{
  switch (Copy_u8PortName) {
    case GPIO_PORTA:
      TOG_BIT(MGPIOA->ODR, Copy_u8PinNumber);
      break;
    case GPIO_PORTB:
      TOG_BIT(MGPIOB->ODR, Copy_u8PinNumber);
      break;
    case GPIO_PORTC:
      TOG_BIT(MGPIOC->ODR, Copy_u8PinNumber);
      break;
    default: /* Invalid PORT */
      break;
  }
}
