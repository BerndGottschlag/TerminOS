#include "stm32f429xx.h"

/* TIM2 is used as the time base counter as it is a 32-bit counter.
 * It it supplied with a clock of 90 MHz.
 */

#define TIM2_FREQUENCY 90 /* MHz */
#define TICKS_PER_MICRO_SECOND 10

void Init_System_Timer(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	TIM2->PSC = TIM2_FREQUENCY/10 - 1; /* TIM2 ticks with 1 MHz -> smallest resolution: 0.1 us, overflow every 7,15 minutes*/

	DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_TIM2_STOP_Msk; /* Disable the timer in debug mode */
}

void Start_System_Timer(void)
{
	TIM2->EGR |= TIM_EGR_UG;
	TIM2->CR1 |= TIM_CR1_CEN;
}

void Reset_System_Timer(void)
{
	TIM2->CNT = 0;
}

uint32_t Get_Time_In_Micro_Seconds(void)
{
	return TIM2->CNT / TICKS_PER_MICRO_SECOND;
}

void Delay_For_Micro_Seconds(uint32_t delayValue)
{
	/* TODO: make robust against timer overflows */
	uint32_t endTime = TIM2->CNT + delayValue * TICKS_PER_MICRO_SECOND;
	while (endTime > TIM2->CNT);
}

void Delay_Until_Micro_Seconds(uint32_t endTimeInMicroSeconds)
{
	/* TODO: make robust against timer overflows */
	uint32_t endTime = endTimeInMicroSeconds * TICKS_PER_MICRO_SECOND;
	while (endTime > TIM2->CNT);
}
