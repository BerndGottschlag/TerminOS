#include "stm32f429xx.h"

void Init_Clock(void)
{
	/* The STM32F4 discovery boards is fitted with an 8 MHz crystal connected to HSE */
	RCC->CR |= RCC_CR_HSEON; /* Enable the HSE */
	while (!(RCC->CR & RCC_CR_HSERDY)); /* Wait until the HSE oscillator is stable */

	/* Configure the PLL for 180 MHz */
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC; /* Select HSE as PLL input */
	/* PLL parameter calculation:
	 * F_VCO_in = F_HSE/PLLM; 1 MHz <= F_VCO_in <= 2 MHz; recommendation: F_VCO_in = 2 MHz
	 * F_VCO_out = F_VCO_in * PLLN; 100 MHz <= F_VCO_out <= 432 MHz; 50 <= PLLN <= 432
	 * F_PLL_out = F_VCO_out/PLLP; F_PLL_out <= 180 MHz; PLLP in [2,4,6,8]
	 * F_PLL_out_USBOTG_etc = F_VCO_out/PLLQ; F_PLL_out_USBOTG_etc <= 48 MHz if USBOTG is not used; 2 <= PLLQ <= 15
	 *
	 * Chosen Values:
	 * F_VCO_in = 2 MHz and F_HSE = 8 MHz -> PLLM = 4
	 * PLLN = 180 -> F_VCP_out = 360 Mhz
	 * PLLP = 2 -> F_PLL_out = 180 MHz
	 * PLLQ = 8 -> F_PLL_out_USBOTG_etc = 45 MHz
	 */
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_Msk;
	RCC->PLLCFGR |= (4 << RCC_PLLCFGR_PLLM_Pos);
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_Msk;
	RCC->PLLCFGR |= (180 << RCC_PLLCFGR_PLLN_Pos);
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP_Msk; /* A value of 0 corresponds to PLLP = 2 */
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLQ_Msk;
	RCC->PLLCFGR |= (8 << RCC_PLLCFGR_PLLQ_Pos);

	RCC->CR |= RCC_CR_PLLON; /* Enable the PLL */
	while (!(RCC->CR & RCC_CR_PLLRDY)); /* Wait until the PLL is locked */

	/* Set the APB prescaler */
	RCC->CFGR &= ~RCC_CFGR_PPRE2_Msk;
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2; /* Div by 2 results in the maximum of 90 MHz */
	RCC->CFGR &= ~RCC_CFGR_PPRE1_Msk;
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4; /* Div by 4 results in the maximum of 45 MHz */

	FLASH->ACR |= FLASH_ACR_LATENCY_5WS; /* Set 5 flash wait states for 180 MHz at 3.3 V (see RM p. 81) */
	FLASH->ACR |=FLASH_ACR_PRFTEN; /* Enable prefetch */

	/* Select the PLL as system clock source */
	RCC->CFGR |= RCC_CFGR_SW_1;
	while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLL); /* Wait until the main clock source is set to the PLL */
}
