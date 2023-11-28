/**
 * @file main.c
 *
 * @brief Main source file for the Dummy Car system.
 *
 * This file contains the primary functionality for the Dummy Car. The Dummy Car is designed
 * to move ahead of the main car and provide essential data, including its color, the presence
 * of an object in front of it, and its current speed. The data is sent to the main car upon request.
 *
 * @Author: Project team
 *
 * @Date: November 11, 2023
 */
/*******************************************************************************
 *                          	Standard Types                                 *
 *******************************************************************************/

#include "../../LIB/ITI_STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/*******************************************************************************
 *                          	MCAL Components                                 *
 *******************************************************************************/

#include "MCAL/RCC/RCC_Interface.h"
#include "MCAL/GPIOx/GPIO_Interface.h"
#include "MCAL/SYSTICK/SYSTICK_Interface.h"
#include "MCAL/GPTimer/TIMER_interface.h"
#include "MCAL/NVIC/NVIC_Interface.h"
#include "MCAL/USART/USART_Interface.h"

/*******************************************************************************
 *                          	HAL Components                                 *
 *******************************************************************************/
#include "HAL/DC_Motor/DC_Motor_Interface.h"
#include "HAL/Ultrasonic/Ultrasonic_Interface.h"



/**
 * @brief Macro defining the color red for the Dummy Car.
 */
#define RED 						    1

/**
 * @brief Macro indicating that an object is detected.
 */
#define OBJECT_DETECTED  				1

/**
 * @brief Macro indicating that no object is detected.
 */
#define OBJECT_NOT_DETECTED	 			0

/**
 * @brief Structure representing the Dummy Car's data, including color, speed, and object detection status.
 */
typedef struct
{
	u8 car_u8color; /**< Color of the Dummy Car. */
	u8 car_u8speed; /**< Speed of the Dummy Car. */
	u8 car_u8objectDetected; /**< Object detection status of the Dummy Car. */

}CAR_t;

/**
 * @brief Enumeration representing the direction for overtaking.
 */
typedef enum
{
	RIGHT_OVT, /**< Right-side overtaking direction. */
	LEFT_OVT   /**< Left-side overtaking direction. */

}OVER_TAKE_DIR_t;

/**
 * @brief Global variable for receiving Bluetooth orders from USART6 interrupt.
 */
extern u8 G_u8BluetoothOrder;

/**
 * @brief Global variable indicating the received request from the dummy's Raspberry Pi.
 */
extern u8 G_u8ReceivedRequest;

/**
 * @brief Global variable representing the distance obtained from the ultrasonic sensor.
 */
u32 G_u32USDistance;

/**
 * @brief Global variable representing the speed indicator.
 */
extern u32 G_u32SpeedIndicator;


/**
 * @brief Initialization data for the Dummy Car.
 */
CAR_t DummyCar = {RED, '4', OBJECT_NOT_DETECTED};

/*******************************************************************************
 *                          	Entry Function                                 *
 *******************************************************************************/
void main (void)
{
	/**
	 * @brief Variable to store Raspberry Pi data.
	 */

	u8 L_u8Raspberry_Data= 0;
	// RCC Initialization >> 'INTERNAL CLOCK'
	MRCC_VoidInit();
	MSTK_voidInit();
	 // ENABLE GPIOA + DC MOTOR Initialization
	HDCM_u8Init();

	// ENABLE  GPIOB
	MRCC_VoidEnablePeriphral(AHB1_BUS,GPIO_PORTB);

	// ENABLE TIMER 2
	MRCC_VoidEnablePeriphral(APB1_BUS,RCC_APB1_TIMER2);

	// TIMER2 channel 1  PINS
	MGPIO_voidSetPinMode(GPIO_PORTA,CH1_PIN,GPIO_MODE_ALTF);
	MGPIO_voidSetPinAltFun(GPIO_PORTA,CH1_PIN,GPIO_ALTFN_1);
	// TIMER2 channel 2  PINS
	MGPIO_voidSetPinMode(GPIO_PORTA,CH2_PIN,GPIO_MODE_ALTF);
	MGPIO_voidSetPinAltFun(GPIO_PORTA,CH2_PIN,GPIO_ALTFN_1);

	// DC MOTOR Starting
	HDCM_voidStart();
	// ULTRASONIC INITIALIZATION
	HUS_voidInit();

	//ENABLE USART1
	MRCC_VoidEnablePeriphral(APB2_BUS,RCC_APB2_USART1);
	//ENABLE USART6
	MRCC_VoidEnablePeriphral(APB2_BUS,RCC_APB2_USART6);

	// ENABLE USART1  INTERRUPT
	MNVIC_voidEnableInterrupt(NVIC_USART1);
	// ENABLE USART6  INTERRUPT
	MNVIC_voidEnableInterrupt(NVIC_USART6);

	//USART1  PINS
	MGPIO_voidSetPinMode(MUSART1_PORT,MUSART1_TX_PIN,GPIO_MODE_ALTF); //TX
	MGPIO_voidSetPinAltFun(MUSART1_PORT,MUSART1_TX_PIN,MUSART1_ALF);
	MGPIO_voidSetPinMode(MUSART1_PORT,MUSART1_RX_PIN,GPIO_MODE_ALTF); //RX
	MGPIO_voidSetPinAltFun(MUSART1_PORT,MUSART1_RX_PIN,MUSART1_ALF);

	//USART6  PINS
	MGPIO_voidSetPinMode(MUSART6_PORT,MUSART6_TX_PIN,GPIO_MODE_ALTF); //TX
	MGPIO_voidSetPinAltFun(MUSART6_PORT,MUSART6_TX_PIN,MUSART6_ALF);
	MGPIO_voidSetPinMode(MUSART6_PORT,MUSART6_RX_PIN,GPIO_MODE_ALTF); //RX
	MGPIO_voidSetPinAltFun(MUSART6_PORT,MUSART6_RX_PIN,MUSART6_ALF);

	// USART1 Initialization  >> for Raspberry
	MUSART1_voidInit();
	// USART6 Initialization  >> for Bluetooth
	MUSART6_voidInit();


	while (1)
	{

		//CONTROL THE SPEED AND DIRECTION OF THE Dummy CAR

		if ((G_u8BluetoothOrder >='0' && G_u8BluetoothOrder<='9')||(G_u8BluetoothOrder=='q'))
		{
			HDCM_u8ChangeSpeed(G_u8BluetoothOrder);
		}
		else
		{
			HDCM_u8CarState(G_u8BluetoothOrder);
		}

		if (G_u8BluetoothOrder=='S')
		{
			DummyCar.car_u8speed=0;
		}

		else
		{
			switch(G_u32SpeedIndicator)
			{
			case 0     : DummyCar.car_u8speed=0; 		break;
			case 1000  : DummyCar.car_u8speed=1; 		break;
			case 2000  : DummyCar.car_u8speed=2;     	break;
			case 3000  : DummyCar.car_u8speed=3; 		break;
			case 4000  : DummyCar.car_u8speed=4;     	break;
			case 5000  : DummyCar.car_u8speed=5; 		break;
			case 6000  : DummyCar.car_u8speed=6;     	break;
			case 7000  : DummyCar.car_u8speed=7; 		break;
			case 8000  : DummyCar.car_u8speed=8;     	break;
			case 9000  : DummyCar.car_u8speed=9; 		break;
			case 10000 : DummyCar.car_u8speed=9; 		break;
			default   :                                 break;
			}
		}
		if (G_u8BluetoothOrder=='F')
		{
			G_u32USDistance = HUS_f32CalcDistance(FORWARD_US);
			if(G_u32USDistance < 20)
			{
				// Stop dummy car
				G_u8BluetoothOrder = 'S';
			}
		}

		if(G_u8ReceivedRequest== 'R')
		{
			G_u32USDistance = HUS_f32CalcDistance(FORWARD_US);
			if(G_u32USDistance < 20)
			{
				DummyCar.car_u8objectDetected=OBJECT_DETECTED;
				// Stop dummy car
				G_u8BluetoothOrder = 'S';
			}
			// check ,in front of dummy car
			else if(G_u32USDistance < 200)
			{
				// My Camera will detect if there is an object or a car
				DummyCar.car_u8objectDetected=OBJECT_DETECTED;
			}

			else
			{
				// There is no thing in front of the car within mentioned range
				DummyCar.car_u8objectDetected=OBJECT_NOT_DETECTED;
			}

			// To send dummy data in one message
			L_u8Raspberry_Data=L_u8Raspberry_Data*10+DummyCar.car_u8color;
			L_u8Raspberry_Data=L_u8Raspberry_Data*10+DummyCar.car_u8objectDetected;
			L_u8Raspberry_Data=L_u8Raspberry_Data*10+(DummyCar.car_u8speed);

			//Send Dummy car data to its Raspberry
			MUSART1_voidTransmitData(L_u8Raspberry_Data);
			//TO prevent sending data without a request
			G_u8ReceivedRequest=0;
		}
		//To prevent data corruption
		L_u8Raspberry_Data=0;
	}
}

