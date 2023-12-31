/*
 * Tiemr0.c
 *
 *  Created on: Nov 19, 2023
 *      Author: medoa
 */


#include "Timer0.h"

void TIMER0_Init(void)
{
	#if (TIMER_OPERATION_MODE == TIMER0_MODE_INTERVAL)
		TIMER0_TCCR0_REG|= TIMER0_INTERVAL_MODE;
	#elif (TIMER_OPERATION_MODE == TIMER0_MODE_CTC)
		TIMER0_TCCR0_REG|= TIMER0_CTC_MODE;
	#elif (TIMER_OPERATION_MODE == TIMER0_MODE_FAST_PWM)
		TIMER0_TCCR0_REG|= TIMER0_PWM_FAST;
	#elif (TIMER_OPERATION_MODE == TIMER0_MODE_PWM_PHASE_CORRECT)
		TIMER0_TCCR0_REG|= TIMER0_PWM_PHASE_CORRECT;
	#else
	#endif
}

#if ((TIMER_OPERATION_MODE == TIMER0_MODE_INTERVAL) || (TIMER_OPERATION_MODE == TIMER0_MODE_CTC))
void TIMER0_Start(u8 prescaler)
{
	TIMER0_TCCR0_REG |=prescaler;
}

void TIMER0_Stop(void)
{
	TIMER0_TCCR0_REG &=0xFC;
}

void TIMER0_SetPreload(u8 preLoadValue)
{
	TIMER0_TCNT0_REG = preLoadValue;
}

u8 TIMER0_GetPreload()
{
	return TIMER0_TCNT0_REG;
}

void TIMER0_EnableInterrupt(void)
{
#if (TIMER_OPERATION_MODE == TIMER0_MODE_INTERVAL)
	SET_BIT(TIMER0_TIMSK_REG,TIMER0_INTERVAL_INT_ENABLE_BIT_NO);
#elif (TIMER_OPERATION_MODE == TIMER0_MODE_CTC)
	SET_BIT(TIMER0_TIMSK_REG,TIMER0_CTC_INT_ENABLE_BIT_NO);
#endif
}

void TIMER0_DisableInterrupt(void)
{
#if (TIMER_OPERATION_MODE == TIMER0_MODE_INTERVAL)
	CLR_BIT(TIMER0_TIMSK_REG,TIMER0_INTERVAL_INT_ENABLE_BIT_NO);
#elif (TIMER_OPERATION_MODE == TIMER0_MODE_CTC)
	CLR_BIT(TIMER0_TIMSK_REG,TIMER0_CTC_INT_ENABLE_BIT_NO);
#endif
}
void TIMER0_SetCompareValue(u8 compareValue)
{
	TIMER0_OCR0_REG = compareValue;
}
#endif

#if ((TIMER_OPERATION_MODE == TIMER0_MODE_FAST_PWM) || (TIMER_OPERATION_MODE == TIMER0_MODE_PWM_PHASE_CORRECT))
void TIMER0_PWM(u8 freq, u8 dutyCycle)
{
	u16 result =0 ;
	result = (dutyCycle * TIMER0_TOP)/100;
	TIMER0_OCR0_REG = result;

}
#endif
