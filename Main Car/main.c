/** ****************************************************************************
 * @mainpage V2V Communication Project (Main Car)
 *
 * @File main.c
 *
 * @brief this file is application file 
 *
 * @author Project Team 
 *
 * @date 6/11/2023
 *
 ****************************************************************************** */
 /*******************************************************************************
 *                          	Standard Types                                 *
 *******************************************************************************/
#include "LIB/BIT_MATH.h"
#include "LIB/ITI_STD_TYPES.h"
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
/*******************************************************************************
 *                          	Global Defenations                             *
 *******************************************************************************/

#define RED 						   		    1
#define OBJECT_DETECTED  				       	1
#define OBJECT_NOT_DETECTED	 					0

#define REQ_FOR_RASPBERRY_FOR_DUMMY				'R'
#define REQ_FOR_RASPBERRY_FOR_CAMERA			'C'

#define VEHICLE_DETECTED 						'V'
#define VEHICLE_NOT_DETECTED 					'O'

typedef struct
{
	u8 car_u8color;
	u8 car_u8speed;
	u8 car_u8objectDetected;

}CAR_t;

CAR_t Dummy_Car_Data;

typedef enum
{
	RIGHT_OVT,
	LEFT_OVT

}OVER_TAKE_DIR_t;

extern u8 G_u8BluetoothOrder;   
extern u32 G_u32SpeedIndicator;	
extern u8 G_u8CameraDetection ;
u8 G_u8PassedCarFlag=1;
u8 G_u8FlagRightInvalid=0;
u8 G_u8EntranceFlag = 0;
u32 G_u32USDistance=100;
u8 G_u8HandShake=0; 
u8 G_u8RasspDummyData=0;

/**
 * @brief Decoding the data received from rasspberry pi.
 *
 * This function takes value as data and divide it to required data .
 * 
 * @param Copy_u8RasspData The data which required to be decoded.
 * @param *P_Dummy_Car_Data The address where the required new data will be saved.
 *
 */
void APP_voidDecodeRasspData(u8 Copy_u8RasspData , CAR_t * P_Dummy_Car_Data)
{
	P_Dummy_Car_Data->car_u8speed=Copy_u8RasspData%10;
	Copy_u8RasspData/=10;
	P_Dummy_Car_Data->car_u8objectDetected=Copy_u8RasspData%10;
	Copy_u8RasspData/=10;
	P_Dummy_Car_Data->car_u8color=Copy_u8RasspData%10;
	Copy_u8RasspData/=10;
}
/**
 * @brief this function responsible for ovartaken sequence.
 *
 * This function takes direction of overtake sequence.
 * 
 * @param A_OverTakeDir The direction of overtaken sequence .
 *
 */
void APP_voidOverTakeSeq(OVER_TAKE_DIR_t A_OverTakeDir)
{
	u8 L_u8checkflag = 1;
	u32 L_u32LocalSpeed = 0;
	
	switch (A_OverTakeDir)
	{
	case RIGHT_OVT:
	
		L_u32LocalSpeed = G_u32SpeedIndicator;
		G_u32SpeedIndicator =5000;
		HDCM_voidMoveRight();
		MSTK_voidSetBusyWait(1000000);
		HDCM_voidMoveForward();
		MSTK_voidSetBusyWait(1800000);
		HDCM_voidMoveLeft();
		MSTK_voidSetBusyWait(1400000); 
		HDCM_u8ChangeSpeed(Dummy_Car_Data.car_u8speed+4);
		HDCM_voidMoveForward();

		while(G_u8PassedCarFlag == 1)
		{
			G_u32USDistance = HUS_f32CalcDistance(LEFT_US);
			while(G_u32USDistance <= 50) 
			{
				G_u32USDistance = HUS_f32CalcDistance(LEFT_US);
				G_u8PassedCarFlag=0;
				if((G_u32USDistance>50) && (L_u8checkflag==1))
				{
					L_u8checkflag=2;
					MSTK_voidSetBusyWait(4000000);
					G_u32USDistance=0;
				}
				else if(G_u32USDistance<50)
				{
					L_u8checkflag=1;
				}
			}
		}
		L_u8checkflag=1;

		if	(G_u8PassedCarFlag==0)
		{
			G_u32SpeedIndicator = 5000;
			HDCM_voidMoveLeft();
			MSTK_voidSetBusyWait(1000000);   
			HDCM_voidMoveForward();
			MSTK_voidSetBusyWait(2000000);
			HDCM_voidMoveRight();
			MSTK_voidSetBusyWait(800000); 
			G_u32SpeedIndicator = L_u32LocalSpeed;
			HDCM_voidMoveForward();
			G_u8PassedCarFlag = 1;
		}
		break;

	case LEFT_OVT:
		
		L_u32LocalSpeed = G_u32SpeedIndicator;
		G_u32SpeedIndicator =5000;
		HDCM_voidMoveLeft();
		MSTK_voidSetBusyWait(1000000);
		HDCM_voidMoveForward();
		MSTK_voidSetBusyWait(1800000);
		HDCM_voidMoveRight();
		MSTK_voidSetBusyWait(1400000); 
		HDCM_u8ChangeSpeed(Dummy_Car_Data.car_u8speed+4);
		HDCM_voidMoveForward();

		while(G_u8PassedCarFlag == 1)
		{
			G_u32USDistance = HUS_f32CalcDistance(LEFT_US);
			while(G_u32USDistance <= 50) 
			{
				G_u32USDistance = HUS_f32CalcDistance(LEFT_US);
				G_u8PassedCarFlag=0; 
				if((G_u32USDistance > 50) && (L_u8checkflag == 1))
				{
					L_u8checkflag = 2;
					MSTK_voidSetBusyWait(4000000);
					G_u32USDistance=0;
				}
				else if(G_u32USDistance<50)
				{
					L_u8checkflag=1;
				}
			}
		}
		L_u8checkflag=1;
		
		if (G_u8PassedCarFlag==0)
		{
			G_u32SpeedIndicator = 5000;
			HDCM_voidMoveRight();
			MSTK_voidSetBusyWait(1000000);   
			HDCM_voidMoveForward();
			MSTK_voidSetBusyWait(2000000);
			HDCM_voidMoveLeft();
			MSTK_voidSetBusyWait(800000); 
			G_u32SpeedIndicator = L_u32LocalSpeed;
			HDCM_voidMoveForward();
			G_u8PassedCarFlag = 1;
		}
		break ;
		
	default : break;
	}
}
/*******************************************************************************
 *                          	Entry Function                                 *
 *******************************************************************************/
void main (void)
{
	u8 L_u8responseAck= 0;
	s8 L_s8counterStop=-2;
	u8 L_u8blindSpotDistance=0;
	u8 L_u8leftLEDFlag = 0;
	u8 L_u8RightLEDFlag = 0;
	u8 L_u8RightLEDCounter = 0;
	u8 L_u8RightLEDCounter = 0;
	
	// RCC Initialization
	MRCC_VoidInit(); 
	MSTK_voidInit();
	// ENABLE GPIOA + DC MOTOR Initialization
	HDCM_u8Init();   

	//ENABLE GPIOB
	MRCC_VoidEnablePeriphral(AHB1_BUS,GPIO_PORTB);

	//ENABLE TIMER2
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

	// USART1 Initialization   >> for Raspberry
	MUSART1_voidInit();
	// USART6 Initialization   >> for Bluetooth
	MUSART6_voidInit();


	// pins for LEDS (used for blindspot detection)
	MGPIO_voidSetPinMode(GPIO_PORTB,GPIO_PIN8,GPIO_MODE_OUTPUT);    // used for right side
	MGPIO_voidSetOutputSpeed(GPIO_PORTB,GPIO_PIN8,GPIO_OUTPUT_SPEED_LOW);
	MGPIO_voidSetOutPutMode(GPIO_PORTB,GPIO_PIN8,GPIO_OUTPUT_TYPE_PUSH_PULL);

	MGPIO_voidSetPinMode(GPIO_PORTB,GPIO_PIN9,GPIO_MODE_OUTPUT);	// used for left side
	MGPIO_voidSetOutputSpeed(GPIO_PORTB,GPIO_PIN9,GPIO_OUTPUT_SPEED_LOW);
	MGPIO_voidSetOutPutMode(GPIO_PORTB,GPIO_PIN9,GPIO_OUTPUT_TYPE_PUSH_PULL);


	G_u8BluetoothOrder='S';
	u32 L_u32counter = 250000;
	
	while (1)
	{
		// CONTROL THE SPEED AND DIRECTION OF THE Main CAR
		if ((G_u8BluetoothOrder >='0' && G_u8BluetoothOrder<='9')||(G_u8BluetoothOrder=='q'))
		{
			HDCM_u8ChangeSpeed(G_u8BluetoothOrder);

		}	
		
		else if (G_u8BluetoothOrder == 'R')
		{
			L_u8blindSpotDistance = HUS_f32CalcDistance(RIGHT_US);
			if(L_u8blindSpotDistance < 20)
			{
				MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN8,GPIO_HIGH);
				HDCM_u8CarState('F');
				L_u8RightLEDFlag = 1;	
			}
			else
			{
				MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN8,GPIO_LOW);
				HDCM_u8CarState('R');
				L_u8RightLEDFlag = 0;	
			}
		}
		
		else if (G_u8BluetoothOrder == 'L')
		{
			L_u8blindSpotDistance = HUS_f32CalcDistance(LEFT_US);
			if(L_u8blindSpotDistance < 20)
			{
				MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN9,GPIO_HIGH);
				HDCM_u8CarState('F');
				L_u8LeftLEDFlag = 1;
			}
			else
			{
				MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN9,GPIO_LOW);
				HDCM_u8CarState('L');
				L_u8LeftLEDFlag = 0;	
			}
		}
		
		else if(G_u8BluetoothOrder == 'F')
		{
			HDCM_u8CarState('F');
		}
		
		else
		{
			MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN8,GPIO_LOW);
			MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN9,GPIO_LOW);
			L_u8LeftLEDFlag = 0;
			L_u8RightLEDFlag = 0;
			HDCM_u8CarState(G_u8BluetoothOrder);
		}
		
		
		if (G_u8BluetoothOrder == 'F' || (L_u8RightLEDFlag==1) || (L_u8LeftLEDFlag==1))
		{	
			if(L_u32counter>=250000)
			{
				L_u32counter=0;
				G_u32USDistance = HUS_f32CalcDistance(FORWARD_US);

				if((G_u32USDistance < 70))
				{
			
					G_u8HandShake=MUSART1_u8ReciveData();
					if(G_u8HandShake == 'D')
					{
						MUSART1_voidTransmitData('A');
					}
					else
					{
						MUSART1_voidTransmitData('H');
						G_u8HandShake = 0;
						continue;
					}
					G_u8HandShake = 0;

					MUSART1_voidTransmitData(REQ_FOR_RASPBERRY_FOR_CAMERA);
					L_u8responseAck=MUSART1_u8ReciveData();
					if(L_u8responseAck != 'S')
					{
						MUSART1_voidTransmitData('<');
						L_u8responseAck = 0;
						continue;
					}
					else
					{
						MUSART1_voidTransmitData('S');
					}
					L_u8responseAck = 0;

					G_u8CameraDetection=MUSART1_u8ReciveData();
					
					//Receive data from raspberry that contains the result of the camera
					if((G_u8CameraDetection == 'V')||(G_u8CameraDetection == 'O'))
					{
						MUSART1_voidTransmitData('F');
					}
					else
					{
						MUSART1_voidTransmitData('G');
						G_u8CameraDetection = 0;
						continue;
					}

					if(G_u8CameraDetection == VEHICLE_DETECTED) // vehicle detected
					{
						L_s8counterStop=0;
						G_u8CameraDetection=0;
						
						// Send request for my raspberry to get data from dummy car
						G_u8HandShake=MUSART1_u8ReciveData();
						if(G_u8HandShake == 'D')
						{
							MUSART1_voidTransmitData('A');
						}
						else
						{
							MUSART1_voidTransmitData('H');
							G_u8HandShake = 0;
							continue;
						}
						G_u8HandShake = 0;

						MUSART1_voidTransmitData(REQ_FOR_RASPBERRY_FOR_DUMMY);
						L_u8responseAck=MUSART1_u8ReciveData();
						if(L_u8responseAck != 'S')
						{
							MUSART1_voidTransmitData(')');
							L_u8responseAck = 0;
							continue;
						}
						else
						{
							MUSART1_voidTransmitData('S');
						}
						L_u8responseAck = 0;

						// Receiving dummy car data from raspberry:
						G_u8RasspDummyData=MUSART1_u8ReciveData();

						if((G_u8RasspDummyData >= 100) && (G_u8RasspDummyData <= 119))
						{
							MUSART1_voidTransmitData('K');
						}
						else
						{
							G_u8RasspDummyData = 0;
							MUSART1_voidTransmitData('L');
							continue;
						}

						// Decoding data coming from raspberry
						APP_voidDecodeRasspData(G_u8RasspDummyData,&Dummy_Car_Data);

						G_u8RasspDummyData=0;

						if (Dummy_Car_Data.car_u8color==RED) 
						{
							// there is no car in front of dummy car
							if(Dummy_Car_Data.car_u8objectDetected==OBJECT_NOT_DETECTED)
							{
								G_u32USDistance = HUS_f32CalcDistance(RIGHT_US); // RIGHT_US

								if(G_u32USDistance > 20)
								{
									MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN8,GPIO_LOW);
									APP_voidOverTakeSeq(RIGHT_OVT);
								}
								else
								{   // if there is an object in range of 20 cm
									// now we have to check on our left
									G_u8FlagRightInvalid=1;
									MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN8,GPIO_HIGH);						
								}
								if(G_u8FlagRightInvalid==1)
								{
									G_u32USDistance = HUS_f32CalcDistance(LEFT_US); // LEFT_US
									if(G_u32USDistance > 20)
									{
										MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN9,GPIO_LOW);
										APP_voidOverTakeSeq(LEFT_OVT);
									}
									else
									{
										// if there is an object in RIGHT ANN LEFT
										// go as the dummy car
										HDCM_u8ChangeSpeed(Dummy_Car_Data.car_u8speed+2);
										MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN9,GPIO_HIGH);
									}

									G_u8FlagRightInvalid=0; // to not enter it again without checking right is not ok
								}
				
							}//end of No object front of the dummy car
							else
							{
								//there is an object in front of the dummy car
								HDCM_u8ChangeSpeed(Dummy_Car_Data.car_u8speed + 2);
							}
						}//end of the car is red

					}//end of  A car is detected
					else
					{
						// OBJECT DETECTED  so the car have to stop immediately
						if(L_s8counterStop==0)
						{
							G_u8BluetoothOrder='S'; 
						}
						else
						{
							L_s8counterStop++;
						}
					}

					G_u8CameraDetection=0; // to start the while (camera) again
					MSTK_voidSetBusyWait(1000);

				} // end of something is in front of the main car
				else
				{
					//there is no thing in front of the main car within mentioned range
				}

			}

		}//end of bluetooth order = 'F'
		else
		{
			//bluetooth order is not 'F'
			//do nothing
		}

		L_u32counter++;

	}// end of while

}//end of main

