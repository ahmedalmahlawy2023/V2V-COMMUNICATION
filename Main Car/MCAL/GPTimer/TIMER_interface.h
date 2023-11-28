#ifndef TMR_INT_H_
#define TMR_INT_H_

/** ****************************************************************************
 *
 * @File TIMER_Interface.h
 *
 * @brief this file contains prototypes functions for TIMER Module
 *
 * @author Project Team
 *
 * @date 6/11/2023
 ******************************************************************************* */
typedef enum
{
	TMR_2,
	TMR_3,
	TMR_4,
	TMR_5
}TMRN_t;

typedef enum
{
	CH1 = 1,
	CH2,
	CH3,
	CH4
}CHN_t;

typedef enum
{
	FROZEN,
	ACTIVE,
	INACTIVE,
	TOGGLE,
	INACTIVE_FORCE,
	ACTIVE_FORCE,
	PWM_MODE1,
	PWM_MODE2
}CMPFn_t;

typedef enum
{
	OUTPUT,
	IC_T2,
	IC_T1,
	IC_TRC
}CH_MODE_t;

typedef enum
{
	RISIN,
	FALLIN,
	RESERVED,
	BOTH
}EDGE_t;

#define CH1_PIN    0u
#define CH2_PIN    1u
#define CH3_PIN    2u
#define CH4_PIN    3u

void MTMR_voidStart(TMRN_t Copy_uddtTMR_no);
void MTMR_voidStop(TMRN_t Copy_uddtTMR_no);
void MTMR_voidSetPrescaler(TMRN_t Copy_uddtTMR_no, u16 Copy_u16Value);
void MTMR_voidCountRst(TMRN_t Copy_uddtTMR_no);
void MTMR_voidSetChannelOutput(TMRN_t Copy_uddtTMR_no, CMPFn_t Copy_uddtFn, CHN_t Copy_uddtChNo);
void MTMR_voidSetChannelInput(TMRN_t Copy_uddtTMR_no, CHN_t Copy_uddtCH_no);
void MTMR_voidSetARR(TMRN_t Copy_uddtTMR_no, u32 Copy_u32Value);
void MTMR_voidStop(TMRN_t Copy_uddtTMR_no);
void MTMR_voidClearCount(TMRN_t Copy_uddtTMR_no);
void MTMR_voidEnableICUInt(TMRN_t Copy_uddtTMR_no);
void MTMR_voidSetCMPVal(TMRN_t Copy_uddtTMR_no, CHN_t Copy_uddtChNo, u32 cmpValue);
u32  MTMR_voidReadCapture(TMRN_t Copy_uddtTMR_no, CHN_t Copy_uddtChNo);
void MTimer3_voidCapture_Compare_Init(void);


void TIM2TEST (void);

#endif /* TMR_INT_H_ */
