#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_
/** ****************************************************************************
 *
 * @File SYSTICK_Interface.h
 *
 * @brief this file contains prototypes functions for SYSTICK Module
 *
 * @author Project Team
 *
 * @date 6/11/2023
 ******************************************************************************* */

void MSTK_voidInit(void);
void MSTK_voidSetBusyWait(u32 Copy_u32Ticks);
void MSTK_voidSetIntervalSingle  (u32 Copy_u32Ticks , void (*Copy_ptr)(void) );
void MSTK_voidSetIntervalPeriodic(u32 Copy_u32Ticks , void (*Copy_ptr)(void) );
void MSTK_voidStopInterval(void );
u32  MSTK_u32GetElapsedTime(void) ;
u32  MSTK_u32GetRemainingTime(void);


#endif
