/**
 * @file USART_program.c
 *
 * @brief Implementation file for USART module.
 *
 * This file contains the implementation of USART initialization,
 * transmission, and reception functions for USART1, USART2, and USART6.
 *
 * @Author: Project Team
 *
 * @Date: November 11, 2023
 *
 */

/*******************************************************************************
 *                           Standard Types                                  *
 *******************************************************************************/
#include "../../LIB/ITI_STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
/*******************************************************************************
 *                          	MCAL Components                                 *
 *******************************************************************************/
#include "USART_Interface.h"
#include "USART_Private.h"
#include "USART_Config.h"

#define FREQ_CK  16000000UL

/**
 * @brief Global variable for receiving Bluetooth orders from USART6 Interrupt.
 *        Default value is 'S', indicating the stop state.
 */
u8 G_u8BluetoothOrder = 'S';

/**
 * @brief Global variable representing the speed of Car 2 (Dummy Car).
 *        Default value is 3000.
 */
u32 G_u32Car2_speed = 3000;

/**
 * @brief Global variable indicating camera detection status.
 *        Default value is 0, indicating that the camera initially detects a person.
 */
u8 G_u8CameraDetection = 0;

/**
 * @brief Global variable indicating the status of Car 2 (Dummy Car).
 *        Default value is 0, indicating that initially, there is no car in front of the Dummy Car.
 */
u8 G_u8Car2_status = 0;


/**
 * @brief Initializes USART1 with the configured settings.
 *
 * This function initializes USART1 with the configured settings such as
 * baud rate, word length, stop bits, etc.
 */
void MUSART1_voidInit(void)
{
	/*
	//calculating BAUDRATE
	f32 USARTDIV= (FREQ_CK)/((8.0*(2.0-OVER_SAMPLING_MODE)*USART1_BAUD_RATE)) ;

	u16 DIV_Mantissa= (u16)USARTDIV;

	f32 DIV_Fraction= (USARTDIV - DIV_Mantissa)*16.0 ;
	//putting DIV_Mantissa in register
	USART1->USART_BRR &=(0xFFFF000F)|(DIV_Mantissa<<4);
	//putting DIV_Fraction in register
	USART1->USART_BRR &=(0xFFFFFFF0)|((u16)(DIV_Fraction));
*/

	//Choosing OverSampling Mode
#if USART1_OVER_SAMPLING_MODE ==OVER_SAMPLING_BY_8
	SET_BIT(USART1->USART_CR1,OVER8);
#elif USART1_OVER_SAMPLING_MODE ==OVER_SAMPLING_BY_16
	CLR_BIT(USART1->USART_CR1,OVER8);
#endif

	//Choosing Word Length
#if USART1_WORD_LENGTH ==_8_DATA_BITS
	CLR_BIT(USART1->USART_CR1,M);
#elif USART1_WORD_LENGTH ==_9_DATA_BITS
	SET_BIT(USART1->USART_CR1,M);
#endif

	/*//Choosing Parity Enable
#if USART1_PARITY_ENABLE_STATE ==DISABLE
	CLR_BIT(USART1->USART_CR1,PCE);
#elif USART1_PARITY_ENABLE_STATE ==ENABLE
	SET_BIT(USART1->USART_CR1,PCE);
#endif
*/

/*	//Choosing Parity Selection
#if USART1_PARITY_SELECTION ==EVEN_PARITY
	CLR_BIT(USART1->USART_CR1,PS);
#elif USART1_PARITY_SELECTION ==ODD_PARITY
	SET_BIT(USART1->USART_CR1,PS);
#endif
*/
	/*//Transmition Complete Interrupt Enable
#if USART1_TRANSMISSION_COMPLETE_INT ==DISABLE
	CLR_BIT(USART1->USART_CR1,TCIE);

#elif USART1_TRANSMISSION_COMPLETE_INT ==ENABLE
	SET_BIT(USART1->USART_CR1,TCIE);
#endif
*/

	//8- RECEIVING NOT EMPTY INTERRUPT ENABLE  >> receiving complete
#if USART1_RECEIVING_COMPLETE_INT ==DISABLE
	CLR_BIT(USART1->USART_CR1,RXNEIE);

#elif USART1_RECEIVING_COMPLETE_INT ==ENABLE
	SET_BIT(USART1->USART_CR1,RXNEIE);
#endif

	//Choosing Stop BITS
#if USART1_STOP_BITS ==_1_STOP_BIT
	CLR_BIT(USART1->USART_CR2,STOP);
	CLR_BIT(USART1->USART_CR2,13);
#elif USART1_STOP_BITS ==_2_STOP_BIT
	CLR_BIT(USART1->USART_CR2,STOP);
	SET_BIT(USART1->USART_CR2,13);
#endif

	//Choosing SAMPLE BIT METHOD
#if USART1_SAMPLE_METHOD ==_3_BIT_SAMPLE_METHOD
	CLR_BIT(USART1->USART_CR3,ONEBIT);
#elif USART1_SAMPLE_METHOD ==_1_BIT_SAMPLE_METHOD
	SET_BIT(USART1->USART_CR3,ONEBIT);
#endif

	//Transmitter Enable
#if USART1_TRANSMITTER_ENABLE ==DISABLE
	CLR_BIT(USART1->USART_CR1,TE);
#elif USART1_TRANSMITTER_ENABLE ==ENABLE
	SET_BIT(USART1->USART_CR1,TE);
#endif

	//receiver Enable
#if USART1_RECIVER_ENABLE ==DISABLE
	CLR_BIT(USART1->USART_CR1,RE);
#elif USART1_RECIVER_ENABLE ==ENABLE
	SET_BIT(USART1->USART_CR1,RE);
#endif

	//BAUD_RATE
#if (USART1_BAUD_RATE == 9600)
	USART1->USART_BRR |= 0xD06;
#elif (USART1_BAUD_RATE == 115200)
	USART1->USART_BRR |= 0x116;
#elif (USART1_BAUD_RATE == 38400)
	USART1->USART_BRR |= 0x342;

#endif
	//SEt Enable For USART
#if USART1_STATE ==ENABLE
	SET_BIT(USART1->USART_CR1,UE);
//#elif USART1_STATE ==DISABLE
	//CLR_BIT(USART1->USART_CR1,UE);
#endif

}
/**
 * @brief Initializes USART2 with the configured settings.
 *
 * This function initializes USART2 with the configured settings such as
 * baud rate, word length, stop bits, etc.
 */
void MUSART2_voidInit(void)
{
	/*
	//calculating BAUDRATE
	f32 USARTDIV= (FREQ_CK)/((8.0*(2.0-OVER_SAMPLING_MODE)*USART1_BAUD_RATE)) ;

	u16 DIV_Mantissa= (u16)USARTDIV;

	f32 DIV_Fraction= (USARTDIV - DIV_Mantissa)*16.0 ;
	//putting DIV_Mantissa in register
	USART2->USART_BRR &=(0xFFFF000F)|(DIV_Mantissa<<4);
	//putting DIV_Fraction in register
	USART2->USART_BRR &=(0xFFFFFFF0)|((u16)(DIV_Fraction));
*/

	//Choosing OverSampling Mode
#if USART2_OVER_SAMPLING_MODE ==OVER_SAMPLING_BY_8
	SET_BIT(USART2->USART_CR1,OVER8);
#elif USART2_OVER_SAMPLING_MODE ==OVER_SAMPLING_BY_16
	CLR_BIT(USART2->USART_CR1,OVER8);
#endif

	//Choosing Word Length
#if USART2_WORD_LENGTH ==_8_DATA_BITS
	CLR_BIT(USART2->USART_CR1,M);
#elif USART2_WORD_LENGTH ==_9_DATA_BITS
	SET_BIT(USART2->USART_CR1,M);
#endif

	/*//Choosing Parity Enable
#if USART2_PARITY_ENABLE_STATE ==DISABLE
	CLR_BIT(USART2->USART_CR1,PCE);
#elif USART2_PARITY_ENABLE_STATE ==ENABLE
	SET_BIT(USART2->USART_CR1,PCE);
#endif
*/

/*	//Choosing Parity Selection
#if USART2_PARITY_SELECTION ==EVEN_PARITY
	CLR_BIT(USART2->USART_CR1,PS);
#elif USART2_PARITY_SELECTION ==ODD_PARITY
	SET_BIT(USART2>USART_CR1,PS);
#endif
*/
	/*//Transmition Complete Interrupt Enable
#if USART2_TRANSMISSION_COMPLETE_INT ==DISABLE
	CLR_BIT(USART2->USART_CR1,TCIE);

#elif USART2_TRANSMISSION_COMPLETE_INT ==ENABLE
	SET_BIT(USART2->USART_CR1,TCIE);
#endif
*/

	//8- RECEIVING NOT EMPTY INTERRUPT ENABLE  >> receiving complete
#if USART2_RECEIVING_COMPLETE_INT ==DISABLE
	CLR_BIT(USART2->USART_CR1,RXNEIE);

#elif USART2_RECEIVING_COMPLETE_INT ==ENABLE
	SET_BIT(USART2->USART_CR1,RXNEIE);
#endif

	//Choosing Stop BITS
#if USART2_STOP_BITS ==_1_STOP_BIT
	CLR_BIT(USART2->USART_CR2,STOP);
	CLR_BIT(USART2->USART_CR2,13);
#elif USART2_STOP_BITS ==_2_STOP_BIT
	CLR_BIT(USART2->USART_CR2,STOP);
	SET_BIT(USART2->USART_CR2,13);
#endif

	//Choosing SAMPLE BIT METHOD
#if USART2_SAMPLE_METHOD ==_3_BIT_SAMPLE_METHOD
	CLR_BIT(USART2->USART_CR3,ONEBIT);
#elif USART2_SAMPLE_METHOD ==_1_BIT_SAMPLE_METHOD
	SET_BIT(USART2->USART_CR3,ONEBIT);
#endif

	//Transmitter Enable
#if USART2_TRANSMITTER_ENABLE ==DISABLE
	CLR_BIT(USART2->USART_CR1,TE);
#elif USART2_TRANSMITTER_ENABLE ==ENABLE
	SET_BIT(USART2->USART_CR1,TE);
#endif

	//receiver Enable
#if USART2_RECIVER_ENABLE ==DISABLE
	CLR_BIT(USART2->USART_CR1,RE);
#elif USART2_RECIVER_ENABLE ==ENABLE
	SET_BIT(USART2->USART_CR1,RE);
#endif

	//BAUD_RATE
#if (USART2_BAUD_RATE == 9600)
	USART2->USART_BRR |= 0xD06;
#elif (USART2_BAUD_RATE == 115200)
	USART2->USART_BRR |= 0x116;
#elif (USART2_BAUD_RATE == 38400)
	USART2->USART_BRR |= 0x342;

#endif
	//SEt Enable For USART
#if USART2_STATE ==ENABLE
	SET_BIT(USART2->USART_CR1,UE);
//#elif USART2_STATE ==DISABLE
	//CLR_BIT(USART2->USART_CR1,UE);
#endif

}
/**
 * @brief Initializes USART6 with the configured settings.
 *
 * This function initializes USART6 with the configured settings such as
 * baud rate, word length, stop bits, etc.
 */
void MUSART6_voidInit(void)
{

	//Choosing OverSampling Mode
#if USART6_OVER_SAMPLING_MODE ==OVER_SAMPLING_BY_8
	SET_BIT(USART6->USART_CR1,OVER8);
#elif USART6_OVER_SAMPLING_MODE ==OVER_SAMPLING_BY_16
	CLR_BIT(USART6->USART_CR1,OVER8);
#endif

	//Choosing Word Length
#if USART6_WORD_LENGTH ==_8_DATA_BITS
	CLR_BIT(USART6->USART_CR1,M);
#elif USART6_WORD_LENGTH ==_9_DATA_BITS
	SET_BIT(USART6->USART_CR1,M);
#endif

	/*//Choosing Parity Enable
#if USART6_PARITY_ENABLE_STATE ==DISABLE
	CLR_BIT(USART6->USART_CR1,PCE);
#elif USART6_PARITY_ENABLE_STATE ==ENABLE
	SET_BIT(USART6->USART_CR1,PCE);
#endif
*/
/*
	//Choosing Parity Selection
#if USART6_PARITY_SELECTION ==EVEN_PARITY
	CLR_BIT(USART6->USART_CR1,PS);
#elif USART6_PARITY_SELECTION ==ODD_PARITY
	SET_BIT(USART6>USART_CR1,PS);
#endif
*/

	//Transmition Complete Interrupt Enable
#if USART6_TRANSMISSION_COMPLETE_INT ==DISABLE
	CLR_BIT(USART6->USART_CR1,TCIE);

#elif USART6_TRANSMISSION_COMPLETE_INT ==ENABLE
	SET_BIT(USART6->USART_CR1,TCIE);
#endif


	//8- RECEIVING NOT EMPTY INTERRUPT ENABLE  >> receiving complete
#if USART6_RECEIVING_COMPLETE_INT ==DISABLE
	CLR_BIT(USART6->USART_CR1,RXNEIE);

#elif USART6_RECEIVING_COMPLETE_INT ==ENABLE
	SET_BIT(USART6->USART_CR1,RXNEIE);
#endif

	//Choosing Stop BITS
#if USART6_STOP_BITS ==_1_STOP_BIT
	CLR_BIT(USART6->USART_CR2,STOP);
	CLR_BIT(USART6->USART_CR2,13);
#elif USART6_STOP_BITS ==_2_STOP_BIT
	CLR_BIT(USART6->USART_CR2,STOP);
	SET_BIT(USART6->USART_CR2,13);
#endif

	//Choosing SAMPLE BIT METHOD
#if USART6_SAMPLE_METHOD ==_3_BIT_SAMPLE_METHOD
	CLR_BIT(USART6->USART_CR3,ONEBIT);
#elif USART6_SAMPLE_METHOD ==_1_BIT_SAMPLE_METHOD
	SET_BIT(USART6->USART_CR3,ONEBIT);
#endif

	//Transmitter Enable
#if USART6_TRANSMITTER_ENABLE ==DISABLE
	CLR_BIT(USART6->USART_CR1,TE);
#elif USART6_TRANSMITTER_ENABLE ==ENABLE
	SET_BIT(USART6->USART_CR1,TE);
#endif

	//receiver Enable
#if USART6_RECIVER_ENABLE ==DISABLE
	CLR_BIT(USART6->USART_CR1,RE);
#elif USART6_RECIVER_ENABLE ==ENABLE
	SET_BIT(USART6->USART_CR1,RE);
#endif

	//BAUD_RATE
#if (USART6_BAUD_RATE == 9600)
	USART6->USART_BRR |= 0xD06;
#elif (USART6_BAUD_RATE == 115200)
	USART6->USART_BRR |= 0x116;
#elif (USART6_BAUD_RATE == 38400)
	USART6->USART_BRR |= 0x342;

#endif
	//SEt Enable For USART
#if USART6_STATE ==ENABLE
	SET_BIT(USART6->USART_CR1,UE);
//#elif USART6_STATE ==DISABLE
	//CLR_BIT(USART6->USART_CR1,UE);
#endif

}
/**
 * @brief Transmits a byte of data through USART1.
 *
 * This function transmits a byte of data through USART1.
 *
 * @param Copy_u8Data: The data byte to be transmitted.
 */
void MUSART1_voidTransmitData(u8 Copy_u8Data)
{
	// Check if data reg is empty
	while (GET_BIT(USART1->USART_SR,TXE)==0);
	//Clearing Flag
	//CLR_BIT(USART1->USART_SR,TXE);
	//sending data to data reg
	USART1->USART_DR=Copy_u8Data;
	//Check if Transmission Completed
	while (GET_BIT(USART1->USART_SR,TC)==0);
	//Clearing Flag
	CLR_BIT(USART1->USART_SR,TC);
}
/**
 * @brief Transmits a byte of data through USART2.
 *
 * This function transmits a byte of data through USART2.
 *
 * @param Copy_u8Data: The data byte to be transmitted.
 */
void MUSART2_voidTransmitData(u8 Copy_u8Data)
{
	// Check if data reg is empty
	while (GET_BIT(USART2->USART_SR,TXE)==0);
	//Clearing Flag
	//CLR_BIT(USART2->USART_SR,TXE);
	//sending data to data reg
	USART2->USART_DR=Copy_u8Data;
	//Check if Transmission Completed
	while (GET_BIT(USART2->USART_SR,TC)==0);
	//Clearing Flag
	CLR_BIT(USART2->USART_SR,TC);
}
/**
 * @brief Transmits a byte of data through USART6.
 *
 * This function transmits a byte of data through USART6.
 *
 * @param Copy_u8Data: The data byte to be transmitted.
 */
void MUSART6_voidTransmitData(u8 Copy_u8Data)
{
	// Check if data reg is empty
	while (GET_BIT(USART6->USART_SR,TXE)==0);
	//Clearing Flag
	//CLR_BIT(USART6->USART_SR,TXE);
	//sending data to data reg
	USART6->USART_DR=Copy_u8Data;
	//Check if Transmission Completed
	while (GET_BIT(USART6->USART_SR,TC)==0);
	//Clearing Flag
	CLR_BIT(USART6->USART_SR,TC);
}
/**
 * @brief Receives a byte of data through USART1.
 *
 * This function receives a byte of data through USART1.
 *
 * @return The received data byte.
 */
u8 MUSART1_u8ReciveData(void)
{
	// Check if data reg isn't empty

	while (GET_BIT(USART1->USART_SR,RXNE)==0);
	//Clearing Flag
	CLR_BIT(USART1->USART_SR,RXNE);

	return (u8)USART1->USART_DR;
}
/**
 * @brief Receives a byte of data through USART2.
 *
 * This function receives a byte of data through USART2.
 *
 * @return The received data byte.
 */
u8 MUSART2_u8ReciveData(void)
{
	// Check if data reg isn't empty
	while (GET_BIT(USART2->USART_SR,RXNE)==0);
	//Clearing Flag
	CLR_BIT(USART2->USART_SR,RXNE);

	return (u8)USART2->USART_DR;
}
/**
 * @brief Receives a byte of data through USART6.
 *
 * This function receives a byte of data through USART6.
 *
 * @return The received data byte.
 */
u8 MUSART6_u8ReciveData(void)
{
	// Check if data reg isn't empty

	while (GET_BIT(USART6->USART_SR,RXNE)==0);
	//Clearing Flag
	CLR_BIT(USART6->USART_SR,RXNE);

	return (u8)USART6->USART_DR;
}
/**
 * @brief Sends a string through USART1.
 *
 * This function sends a null-terminated string through USART1.
 *
 * @param PC_String: Pointer to the string to be transmitted.
 */
void MUSART1_voidSendString(u8* PC_String)
{
	u8 Loc_u8Iterator;
	for (Loc_u8Iterator=0 ; PC_String[Loc_u8Iterator] != '\0'; Loc_u8Iterator++)
	{
		MUSART1_voidTransmitData(PC_String[Loc_u8Iterator]);
	}
	MUSART1_voidTransmitData('\0');

}
/**
 * @brief Sends a string through USART2.
 *
 * This function sends a null-terminated string through USART2.
 *
 * @param PC_String: Pointer to the string to be transmitted.
 */
void MUSART2_voidSendString(u8* PC_String)
{
	u8 Loc_u8Iterator;
	for (Loc_u8Iterator=0 ; PC_String[Loc_u8Iterator] != '\0'; Loc_u8Iterator++)
	{
		MUSART2_voidTransmitData(PC_String[Loc_u8Iterator]);
	}
	MUSART2_voidTransmitData('\0');
}
/**
 * @brief Sends a string through USART6.
 *
 * This function sends a null-terminated string through USART6.
 *
 * @param PC_String: Pointer to the string to be transmitted.
 */
void MUSART6_voidSendString(u8* PC_String)
{
	u8 Loc_u8Iterator;
	for (Loc_u8Iterator=0 ; PC_String[Loc_u8Iterator] != '\0'; Loc_u8Iterator++)
	{
		MUSART6_voidTransmitData(PC_String[Loc_u8Iterator]);
	}
	MUSART6_voidTransmitData('\0');
}
/**
 * @brief Receives a string through USART1.
 *
 * This function receives a null-terminated string through USART1.
 *
 * @param PC_String: Pointer to the buffer where the received string will be stored.
 */
void MUSART1_voidReciveString(u8* PC_String)
{
	u8 Loc_u8Iterator;
	u8 Loc_RecivedData = MUSART1_u8ReciveData();
	for (Loc_u8Iterator=0 ; Loc_RecivedData!='\0' ; Loc_u8Iterator++ )
	{
		PC_String[Loc_u8Iterator]=MUSART1_u8ReciveData();
		Loc_RecivedData = MUSART1_u8ReciveData();
	}
}
/**
 * @brief Receives a string through USART2.
 *
 * This function receives a null-terminated string through USART2.
 *
 * @param PC_String: Pointer to the buffer where the received string will be stored.
 */
void MUSART2_voidReciveString(u8* PC_String)
{
	u8 Loc_u8Iterator;
	u8 Loc_RecivedData = MUSART2_u8ReciveData();
	for (Loc_u8Iterator=0 ; Loc_RecivedData!='\0' ; Loc_u8Iterator++ )
	{
		PC_String[Loc_u8Iterator]=MUSART2_u8ReciveData();
		Loc_RecivedData = MUSART2_u8ReciveData();
	}
}
/**
 * @brief Receives a string through USART6.
 *
 * This function receives a null-terminated string through USART6.
 *
 * @param PC_String: Pointer to the buffer where the received string will be stored.
 */
void MUSART6_voidReciveString(u8* PC_String)
{
	u8 Loc_u8Iterator;
	u8 Loc_RecivedData = MUSART6_u8ReciveData();
	for (Loc_u8Iterator=0 ; Loc_RecivedData!='\0' ; Loc_u8Iterator++ )
	{
		PC_String[Loc_u8Iterator]=MUSART6_u8ReciveData();
		Loc_RecivedData = MUSART6_u8ReciveData();
	}
}

/**
 * @brief USART1 interrupt handler.
 *
 * This function is the interrupt handler for USART1. It is currently empty
 * and can be expanded with specific functionality if needed.
 */
void USART1_IRQHandler(void)
{

}
/**
 * @brief USART2 interrupt handler.
 *
 * This function is the interrupt handler for USART2. It is currently empty
 * and can be expanded with specific functionality if needed.
 */

void USART2_IRQHandler(void)
{


}

/**
 * @brief USART6 interrupt handler.
 *
 * This function is the interrupt handler for USART6. It currently reads a
 * byte from USART6 and assigns it to the global variable G_u8BluetoothOrder.
 */
void USART6_IRQHandler(void)
{
	G_u8BluetoothOrder = MUSART6_u8ReciveData();
}




