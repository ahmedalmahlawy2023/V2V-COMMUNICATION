#ifndef SYSTICK_PRIVATE_H_
#define SYSTICK_PRIVATE_H_
/** ****************************************************************************
 *
 * @File SYSTICK_Private.h
 *
 * @brief this file contains private addresses and configurations related to SYSTICK Module
 *
 * @author Project Team
 *
 * @date 6/11/2023	
 *
 ****************************************************************************** */
#define SYSTICK_BASE_ADDRESS    0xE000E010

typedef struct 
{
	u32 STK_CTRL;
	
	u32 STK_LOAD;
	
	u32 STK_VAL;
	
	u32 STK_CALIB;

}SYSTICK;

#define MSYSTICK   	    ((volatile SYSTICK *)SYSTICK_BASE_ADDRESS)

#define COUNTFLAG     	16
#define CLKSOURCE 		2
#define TICKINT			1
#define ENABLE			0


#define AHB_OVER_8   						0
#define AHB_PROCCESOR_CLOCK				1


#define MSTK_SINGLE_INTERVAL  	 1
#define MSTK_Periodic_INTERVAL   2

#endif
