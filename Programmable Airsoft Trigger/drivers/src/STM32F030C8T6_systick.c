/*
 * STM32F030C8T6_systick.c
 *
 *  Created on: 08.09.2019
 *      Author: Pawel
 */

#include <STM32F030C8T6.h>
#include <STM32F030C8T6_systick.h>
#include <string.h>

/******************************************************************************************
 ********************** Private functions *************************************************
 ******************************************************************************************/

static void	SysTickSetReloadValue(SysTick_Handler_t *pSystickHandler);

static void	SysTickSetCurrentValue(SysTick_Handler_t *pSystickHandler);

static void	SysTickExceptionHandling(SysTick_Handler_t *pSystickHandler);

static void SysTickClockSource(SysTick_Handler_t *pSystickHandler);

/******************************************************************************************
 ********************** Main functions definitions ****************************************
 ******************************************************************************************/

void SysTickInit(SysTick_Handler_t *pSystickHandler){
	SysTickSetReloadValue(pSystickHandler);
	SysTickSetCurrentValue(pSystickHandler);
	SysTickClockSource(pSystickHandler);
	SysTickExceptionHandling(pSystickHandler);
}


void SystickCounterHandling(SysTick_Handler_t *pSystickHandler){
	SYSTICK_p->CSR &= ~(pSystickHandler->config.counterInitialize << SYSTICK_CSR_ENABLE);
	SYSTICK_p->CSR |= (pSystickHandler->config.counterInitialize << SYSTICK_CSR_ENABLE);
}

uint8_t isSystickFlagSet(SysTick_Handler_t *pSystickHandler){
	return (SYSTICK_p->CSR >> SYSTICK_CSR_COUNTFLAG) & 0x1;
}

/******************************************************************************************
 ********************** Private functions *************************************************
 ******************************************************************************************/

static void	SysTickSetReloadValue(SysTick_Handler_t *pSystickHandler){
	pSystickHandler->pSysTick->RVR = (pSystickHandler->config.autoReloadValue << SYSTICK_RVR_RELOAD);
}


static void	SysTickSetCurrentValue(SysTick_Handler_t *pSystickHandler){
	pSystickHandler->pSysTick->CVR = (pSystickHandler->config.counterValue << SYSTICK_CVR_CURRENT);
}


static void	SysTickExceptionHandling(SysTick_Handler_t *pSystickHandler){
	pSystickHandler->pSysTick->CSR &= ~(pSystickHandler->config.exceptionRequestEnable << SYSTICK_CSR_TICKINT);
	pSystickHandler->pSysTick->CSR |= (pSystickHandler->config.exceptionRequestEnable << SYSTICK_CSR_TICKINT);
}


static void SysTickClockSource(SysTick_Handler_t *pSystickHandler){
	pSystickHandler->pSysTick->CSR &= ~(pSystickHandler->config.clockSource << SYSTICK_CSR_CLKSOURCE);
	pSystickHandler->pSysTick->CSR |= (pSystickHandler->config.clockSource << SYSTICK_CSR_CLKSOURCE);
}
