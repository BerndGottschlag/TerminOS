#include "stm32f429xx.h"
#include <stdbool.h>

void Init_User_Button(void)
{
	/* The user LED is connected to PA0 */
	/* TODO: debouncing? */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; /* Enable GPIO A clock */

	GPIOA->MODER &= ~GPIO_MODER_MODER0; /* Set as input */
	GPIOA->ODR &= ~GPIO_ODR_OD0; /* Set to low */
}

bool Is_User_Button_Pressed(void)
{
	return (bool)(GPIOA->IDR & GPIO_IDR_ID0);
}

void Init_User_LEDs(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN; /* Enable GPIO G clock */

	/* LD3 is the green user LED connected to PG13 */
	GPIOG->MODER |= GPIO_MODER_MODER13_0; /* Set as output */
	GPIOG->OSPEEDR |= GPIO_OSPEEDR_OSPEED13_1; /* Set to high speed */
	GPIOG->ODR &= ~GPIO_ODR_OD13; /* Set to low */


	/* LD4 is the red user LED connected to PG14 */
	GPIOG->MODER |= GPIO_MODER_MODER14_0; /* Set as output */
	GPIOG->OSPEEDR |= GPIO_OSPEEDR_OSPEED14_1; /* Set to high speed */
	GPIOG->ODR &= ~GPIO_ODR_OD14; /* Set to low */
}

void Set_LD3_High(void)
{
	GPIOG->ODR |= GPIO_ODR_OD13;
}

void Set_LD3_Low(void)
{
	GPIOG->ODR &= ~GPIO_ODR_OD13;
}

void Toggle_LD3(void)
{
	GPIOG->ODR ^= GPIO_ODR_OD13;
}


void Set_LD4_High(void)
{
	GPIOG->ODR |= GPIO_ODR_OD14;
}

void Set_LD4_Low(void)
{
	GPIOG->ODR &= ~GPIO_ODR_OD14;
}

void Toggle_LD4(void)
{
	GPIOG->ODR ^= GPIO_ODR_OD14;
}


void Init_Debug_Pins(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN; /* Enable GPIO G clock */

	/* PG5 is used as a debug pin */
	GPIOG->MODER |= GPIO_MODER_MODER5_0; /* Set as output */
	GPIOG->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_1; /* Set to high speed */
	GPIOG->ODR &= ~GPIO_ODR_OD5; /* Set to low */

	/* PG7 is used as a debug pin */
	GPIOG->MODER |= GPIO_MODER_MODER7_0; /* Set as output */
	GPIOG->OSPEEDR |= GPIO_OSPEEDR_OSPEED7_1; /* Set to high speed */
	GPIOG->ODR &= ~GPIO_ODR_OD7; /* Set to low */
}

void Toggle_Debug_Pin_PG5(void)
{
	GPIOG->ODR ^= GPIO_ODR_OD5;
}

void Toggle_Debug_Pin_PG7(void)
{
	GPIOG->ODR ^= GPIO_ODR_OD7;
}

void Set_Debug_Pin_PG7_High(void)
{
	GPIOG->ODR |= GPIO_ODR_OD7;
}

void Set_Debug_Pin_PG7_Low(void)
{
	GPIOG->ODR &= ~GPIO_ODR_OD7;
}
