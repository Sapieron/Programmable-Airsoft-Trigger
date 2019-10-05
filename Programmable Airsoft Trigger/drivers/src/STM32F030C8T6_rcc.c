/*
 * STM32F030C8T6_rcc.c
 *
 *  Created on: 29.08.2019
 *      Author: Pawel
 */

#include <STM32F030C8T6_rcc.h>
#include <STM32F030C8T6.h>
#include <stdint.h>
#include <STM32F030C8T6_gpio.h>

/******************************************************************************************
 ********************** Private functions *************************************************
 ******************************************************************************************/

static void ClearAPBPrescaler();

static void SetAPBPrescaler(uint8_t prescalerAPB);

static void ClearAHBPrescaler();

static void SetAHBPrescaler(uint8_t prescalerAHB);


/******************************************************************************************
 ********************** Main functions definitions ****************************************
 ******************************************************************************************/

void RCCGpioClockInit(GPIO_Handle_t *pGPIOHandle){
	if (pGPIOHandle->pGPIOx == GPIOA_p)
		RCC_p->AHBENR |= (ENABLE << RCC_AHBENR_IOPAEN);
	else if (pGPIOHandle->pGPIOx == GPIOB_p)
		RCC_p->AHBENR |= (ENABLE << RCC_AHBENR_IOPBEN);
	else if (pGPIOHandle->pGPIOx == GPIOC_p)
		RCC_p->AHBENR |= (ENABLE << RCC_AHBENR_IOPCEN);
	else if (pGPIOHandle->pGPIOx == GPIOD_p)
		RCC_p->AHBENR |= (ENABLE << RCC_AHBENR_IOPDEN);
	else if (pGPIOHandle->pGPIOx == GPIOF_p)
		RCC_p->AHBENR |= (ENABLE << RCC_AHBENR_IOPFEN);
}

void RCCSyscfgClockInit(){
	RCC_p->APB2ENR |= (ENABLE << RCC_APB2ENR_SYSCFGEN);
}

void RCCGpioClockDeInit(GPIO_Handle_t *pGPIOHandle){
	RCC_p->APB2ENR &= ~(ENABLE << RCC_APB2ENR_SYSCFGEN);
	RCC_p->APB2RSTR |= (ENABLE << RCC_APB2ENR_SYSCFGEN);
}

void RCCSetAPBClockPrescaler(uint8_t prescalerAPB){
	ClearAPBPrescaler();
	SetAPBPrescaler(prescalerAPB);
}

void RCCSetAHBClockPrescaler(uint8_t prescalerAHB){
	ClearAHBPrescaler();
	SetAHBPrescaler(prescalerAHB);
}

void RCCTimer6_7_ClockInitialize(TIMER6_7_Handler_t *pTIMER6_7_Handler){
	if(pTIMER6_7_Handler->pTIMER6_7 == TIMER6_p)
	{
		RCC_p->APB1RSTR |= (ENABLE << RCC_APB1ENR_TIMER6);
		RCC_p->APB1RSTR &= ~(ENABLE << RCC_APB1ENR_TIMER6);
		RCC_p->APB1ENR |= (ENABLE << RCC_APB1ENR_TIMER6);
	}
	else if(pTIMER6_7_Handler->pTIMER6_7 == TIMER7_p)
	{
		RCC_p->APB1RSTR |= (ENABLE << RCC_APB1ENR_TIMER7);
		RCC_p->APB1RSTR &= ~(ENABLE << RCC_APB1ENR_TIMER7);
		RCC_p->APB1ENR |= (ENABLE << RCC_APB1ENR_TIMER7);
	}
}


void RCCTimer3_ClockInitialize(TIMER3_Handler_t *pTIMER3_Handler){
		RCC_p->APB1RSTR |= (ENABLE << RCC_APB1ENR_TIMER3);
		RCC_p->APB1RSTR &= ~(ENABLE << RCC_APB1ENR_TIMER3);
		RCC_p->APB1ENR |= (ENABLE << RCC_APB1ENR_TIMER3);
		while( !( (RCC_p->APB1ENR |= (ENABLE << RCC_APB1ENR_TIMER3) ) >> RCC_APB1ENR_TIMER3) )
				;
}

/******************************************************************************************
 ********************** Private functions *************************************************
 ******************************************************************************************/

static void ClearAPBPrescaler(){
	RCC_p->CFGR &= ~(0x7 << RCC_CFGR_PPRE);
}

static void SetAPBPrescaler(uint8_t prescalerAPB){
	RCC_p->CFGR |= (prescalerAPB << RCC_CFGR_PPRE);
}

static void ClearAHBPrescaler(){
	RCC_p->CFGR &= ~(0x7 << RCC_CFGR_HPRE);
}

static void SetAHBPrescaler(uint8_t prescalerAHB){
	RCC_p->CFGR |= (prescalerAHB << RCC_CFGR_HPRE);
}
