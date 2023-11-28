/** ****************************************************************************
 *
 * @File GPIO_Interface.h
 *
 * @brief this file contains prototypes functions for GPIO Module
 *
 * @author Project Team
 *
 * @date 6/11/2023
 ******************************************************************************* */
 
/***************************File Guard **************************************** */
#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_




/***************************************Port Macros*********************************/
#define GPIO_PORTA      0u
#define GPIO_PORTB      1u
#define GPIO_PORTC      2u
#define GPIO_PORTD      3u
#define GPIO_PORTE      4u
#define GPIO_PORTH      5u


/***************************************Pin Macros*********************************/
#define GPIO_PIN0      0u
#define GPIO_PIN1      1u
#define GPIO_PIN2      2u
#define GPIO_PIN3      3u
#define GPIO_PIN4      4u
#define GPIO_PIN5      5u
#define GPIO_PIN6      6u
#define GPIO_PIN7      7u
#define GPIO_PIN8      8u
#define GPIO_PIN9      9u
#define GPIO_PIN10     10u
#define GPIO_PIN11     11u
#define GPIO_PIN12     12u
#define GPIO_PIN13     13u
#define GPIO_PIN14     14u
#define GPIO_PIN15     15u

/***************************************Modes Macros*********************************/
#define GPIO_MODE_INPUT         0u
#define GPIO_MODE_OUTPUT		1u
#define GPIO_MODE_ALTF			2u
#define GPIO_MODE_ANALOG		3u

/***************************************O/PTypes Macros*******************************/
#define GPIO_OUTPUT_TYPE_PUSH_PULL        (0u)
#define GPIO_OUTPUT_TYPE_OPEN_DRAIN       (1u)

/***************************************Speed Macros*********************************/
#define GPIO_OUTPUT_SPEED_LOW       	(0u)
#define GPIO_OUTPUT_SPEED_MEDIUM      	(1u)
#define GPIO_OUTPUT_SPEED_HIGH 			(2u)
#define GPIO_OUTPUT_SPEED_VERY_HIGH 	(3u)

/***************************************Pull State Macros*********************************/
#define GPIO_PULL_FLOATING      	(0u)
#define GPIO_PULL_PULL_UP      		(1u)
#define GPIO_PULL_PULL_DOWN 		(2u)

/***************************************Write Data Macros*********************************/
#define GPIO_LOW     		(0u)
#define GPIO_HIGH      		(1u)

/***************************************Alternative Func Macros*********************************/
#define GPIO_ALTFN_0            (0b0000)         
#define GPIO_ALTFN_1            (0b0001)
#define GPIO_ALTFN_2            (0b0010)
#define GPIO_ALTFN_3            (0b0011)
#define GPIO_ALTFN_4            (0b0100)
#define GPIO_ALTFN_5            (0b0101)
#define GPIO_ALTFN_6            (0b0110)
#define GPIO_ALTFN_7            (0b0111)
#define GPIO_ALTFN_8            (0b1000)
#define GPIO_ALTFN_9            (0b1001)
#define GPIO_ALTFN_10           (0b1010)
#define GPIO_ALTFN_11           (0b1011)
#define GPIO_ALTFN_12           (0b1100)
#define GPIO_ALTFN_13           (0b1101)
#define GPIO_ALTFN_14           (0b1110)
#define GPIO_ALTFN_15           (0b1111)


/*********************************Functions Prototypes**********************************/

/*
**************************************************************************************************************************
***************************************** 01 - MGPIO_voidSetPinMode  *****************************************************

	1-  function Description ->  function Set the mode of the Pin 
	2-  Options : (A) MGPIO_MODE_INPUT
				  (B) MGPIO_MODE_OUTPUT
				  (C) MGPIO_MODE_ALTFUN
				  (D) MGPIO_MODE_ANALOG
				  
	3- Function Arguments : (A)  Copy_u8PortName  : The port Number (ex : MGPIOA_PORT , MGPIOB_PORT)
							(B)	 Copy_u8PinNum    : The Pin Number (ex : GPIO_PIN0 , GPIO_PIN1)
							(C)  Copy_u8Mode      : The Mode (ex : MGPIO_MODE_INPUT)
	
	4- Function Return   ->  void
	
**************************************************************************************************************************
**************************************************************************************************************************/	
void MGPIO_voidSetPinMode(u8 Copy_u8PortName,u8 Copy_u8PinNum,u8 Copy_u8Mode);


void MGPIO_voidSetPortMode(u8 Copy_u8PortName,u8 Copy_u8Mode); //assignment


/*******************************************************************************************************/
/*                                      02- MGPIO_voidSetOutputMode                                    */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set The output mode Of Pin  Take Bits                           */
/*                                                                                                     */
/*      1- PUSH_PULL                                                                                   */
/*      2- OPEN_DRAIN                                                                                  */
/*                                                                                                     */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum ,   Copy_u8OutputMode                  */                   
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidSetOutPutMode(u8 Copy_u8PortName,u8 Copy_u8PinNum,u8 Copy_u8OutPutMode);

/*******************************************************************************************************/
/*                                      03- MGPIO_voidSetOutputSpeed                                   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set The output speed  Of Pin Mode Take 2Bits                    */
/*                                                                                                     */
/*      1- LOW_SPEED   		  8 MHZ                                                                    */
/*      2- MEDUIM_SPEED 	  50 MHZ                                                                   */
/*      3- HIGH_SPEED    	  80 MHZ                                                                   */
/*      4- VERY_HIGH_SPEED	  180 MHZ                                                                  */
/*																								       */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum ,   Copy_u8OutputSpeed                 */                   
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidSetOutputSpeed(u8 Copy_u8PortName,u8 Copy_u8PinNum,u8 Copy_u8OutPutSpeed);

/*******************************************************************************************************/
/*                                      04- MGPIO_voidSetPullState                                     */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set The Resistor connection state of pin Take 2Bits             */
/*                                                                                                     */
/*      1- PULL_FLOAT                                                                                  */
/*      2- PULL_UP                                                                                     */
/*      3- PULL_DOWN                                                                                   */
/*      4- RESERVED                                                                                    */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum ,   Copy_u8PullState                   */                   
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidSetPullState(u8 Copy_u8PortName,u8 Copy_u8PinNum,u8 Copy_u8PullState); //lazm azbt el S.F bta3y eno lw 3aml o/p mode we push-pull mynf34 a48l el pull state 

/*******************************************************************************************************/
/*                                      05- MGPIO_u8GetPinVal                                          */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Read Data from IDR Register                                     */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum                                        */                   
/* 3- Function Return      -> u8 PinValue                                                              */
/*******************************************************************************************************/
u8 MGPIO_u8GetPinValue(u8 Copy_u8PortName,u8 Copy_u8PinNum);

/*******************************************************************************************************/
/*                                      06- MGPIO_voidSetPinVal                                        */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set Pin Value At  ODR Register                                  */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum  , Copy_u8Pinval                       */                   
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidSetPinValue(u8 Copy_u8PortName,u8 Copy_u8PinNum,u8 Copy_u8PinVal);

/*******************************************************************************************************/
/*                                      07- MGPIO_voidDirectSetReset                                   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set and Reset Direct for crossponding Pin Value At  BSRR Register*/
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum  , Copy_u8SetResetState                */                   
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidDirectSetReset(u8 Copy_u8PortName,u8 Copy_u8PinNum,u8 Copy_u8SetResetState); //hna hst5dm b2a BSRR

/*******************************************************************************************************/
/*                                      08- MGPIO_voidSetPortVal                                       */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set Port Value At  ODR Register                                 */
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName  , Copy_u8Pinval                                         */                   
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidSetPortValue(u8 Copy_u8PortName,u16 Copy_u16PortValue);

/*******************************************************************************************************/
/*                                      09- MGPIO_voidPinLock                                          */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Lock At pin :                                                   */
/*                               1 - Set PIN                                                           */
/*                               2 - Set PIN 16                                                        */
/*                               3 - Clr PIN 16                                                        */
/*                               4 - Set PIN 16                                                        */
/*                               5 - wait bit 16 = High                                                */ 
/*                                                                                                     */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum                                        */                   
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidPinLock(u8 Copy_u8PortName,u8 Copy_u8PinNum);

/*******************************************************************************************************/
/*                                      10- MGPIO_voidSetPinAltFun                                     */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set pin Alternative :                                           */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum  , Copy_u8AltFun                       */                   
/* 3- Function Return      -> void                                                                     */
/*******************************************************************************************************/
void MGPIO_voidSetPinAltFun(u8 Copy_u8PortName,u8 Copy_u8PinNum,u8 Copy_u8AltFun);//b7dd el pin dy ht4t8l tb3 anhy periphral we bro7 ll periphral da b2a a7ddlo anhy pin adthalo

void MGPIO_voidTogglePin(u8 Copy_u8PortName ,u8 Copy_u8PinNumber );


#endif
