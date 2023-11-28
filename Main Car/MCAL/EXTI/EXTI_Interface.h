#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_
/** ****************************************************************************
 *
 * @File EXTI_Interface.h
 *
 * @brief this file contains prototypes functions for EXTI Module
 *
 * @author Project Team
 *
 * @date 6/11/2023
 ******************************************************************************* */
typedef enum 
{
	MEXTI_LINE_0,
	MEXTI_LINE_1,
	MEXTI_LINE_2,
	MEXTI_LINE_3,
	MEXTI_LINE_4,
	MEXTI_LINE_5,
	MEXTI_LINE_6,
	MEXTI_LINE_7,
	MEXTI_LINE_8,
	MEXTI_LINE_9,
	MEXTI_LINE_10,
	MEXTI_LINE_11,
	MEXTI_LINE_12,
	MEXTI_LINE_13,
	MEXTI_LINE_14,
	MEXTI_LINE_15
	
}MEXTI_LINE_t;



// Triggering Mode
typedef enum 
{
	MEXTI_RISING_EDGE,
	MEXTI_FALLING_EDGE,
	MEXTI_ON_CHANGE
	
}MEXTI_TRIGGER_MODE_t;


// EXTI Port
typedef enum 
{
	MEXTI_PORTA,
	MEXTI_PORTB,
	MEXTI_PORTC
	
}MEXTI_PORT_t;





/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
 
void MEXTI_voidEnableEXTI(MEXTI_LINE_t Copy_uddtLineNum); // uddt -> user-defined data type
/*
 * FUNCTION NAME:		  MEXTI_voidEnableEXTI
 * FUNCTION RETURN:		  nothing
 * FUNCTION ARGUMENTS:	  MEXTI_LINE_t (Line Number)
 * FUNCTION DESCRIPTION:  Enable External Interrupt 
 */

void MEXTI_voidDisableEXTI(MEXTI_LINE_t Copy_uddtLineNum); 
/*
 * FUNCTION NAME:		  MEXTI_voidDisableEXTI
 * FUNCTION RETURN:		  nothing
 * FUNCTION ARGUMENTS:	  MEXTI_LINE_t (Line Number)
 * FUNCTION DESCRIPTION:  Disable External Interrupt 
 */
 
void MEXTI_voidSoftwareInterrupt(MEXTI_LINE_t Copy_uddtLineNum); 
/*
 * FUNCTION NAME:		  MEXTI_voidSoftwareInterrupt
 * FUNCTION RETURN:		  nothing
 * FUNCTION ARGUMENTS:	  MEXTI_LINE_t (Line Number)
 * FUNCTION DESCRIPTION:  Enable External Software Interrupt that used for diagnosing and debugging cases
 */
 
void MEXTI_voidSetTriggerSource(MEXTI_LINE_t Copy_uddtLineNum, MEXTI_TRIGGER_MODE_t Copy_uddtTriggerMode); 
/*
 * FUNCTION NAME:		  MEXTI_voidSetTriggerSource
 * FUNCTION RETURN:		  nothing
 * FUNCTION ARGUMENTS:	  MEXTI_LINE_t (Line Number), MEXTI_TRIGGER_MODE_t (Trigger Mode)
 * FUNCTION DESCRIPTION:  Set Triggering Source for External Interrupt
 */
 
void MEXTI_voidSetEXTIConfig(MEXTI_LINE_t Copy_uddtLineNum, MEXTI_PORT_t Copy_uddtGPIOPortNum); //port l2n el pin btt7dd 3la asas el line , we mmkn ast5dm el port mn elenum ele 3mlto leh aw u8
/*
 * FUNCTION NAME:		  MEXTI_voidSetTriggerSource
 * FUNCTION RETURN:		  nothing
 * FUNCTION ARGUMENTS:	  MEXTI_LINE_t (Line Number), MEXTI_PORT_t (GPIO Port Num)
 * FUNCTION DESCRIPTION:  Set External Interrupt Pin in GPIO Ports
 */
 
void MEXTI_voidSetCallBack_EXTI0(void (*ptr) (void)); 
/*
 * FUNCTION NAME:		  MEXTI_voidSetCallBack_EXTI0
 * FUNCTION RETURN:		  nothing
 * FUNCTION ARGUMENTS:	  pointer to function
 * FUNCTION DESCRIPTION:  Call-Back function for External Interrupt 0 
 */

void MEXTI_voidSetCallBack_EXTI1(void (*ptr) (void)); 
/*
 * FUNCTION NAME:		  MEXTI_voidSetCallBack_EXTI1
 * FUNCTION RETURN:		  nothing
 * FUNCTION ARGUMENTS:	  pointer to function
 * FUNCTION DESCRIPTION:  Call-Back function for External Interrupt 1 
*/

void MEXTI_voidSetCallBack_EXTI8(void (*ptr) (void));

#endif
