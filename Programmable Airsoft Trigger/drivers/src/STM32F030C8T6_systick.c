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

void SysTick_Init(SysTick_Handler_t *pSystickHandler){
	SysTickSetReloadValue(pSystickHandler);
	SysTickSetCurrentValue(pSystickHandler);
	SysTickClockSource(pSystickHandler);
	SysTickExceptionHandling(pSystickHandler);
}


void SysTick_CounterHandling(SysTick_Handler_t *pSystickHandler){
	SYSTICK_p->CSR &= ~(ENABLE << SYSTICK_CSR_ENABLE);
	SYSTICK_p->CSR |= (pSystickHandler->config.counterInitialize << SYSTICK_CSR_ENABLE);
}

uint8_t SysTick_isFlagSet(SysTick_Handler_t *pSystickHandler){
	return (SYSTICK_p->CSR >> SYSTICK_CSR_COUNTFLAG) & 0x1;
}

void Systick_EnableTimerForSetTimeInMs(SysTick_Handler_t *sysTickHandler, uint32_t delayTime, uint8_t exceptionRequestEnOrDis){
	sysTickHandler->config.counterValue = 0;
	sysTickHandler->config.autoReloadValue = TIME_BASE_OF_ONE_MS_FOR_SYSTICK * delayTime;
	sysTickHandler->config.counterInitialize = ENABLE;
	sysTickHandler->config.exceptionRequestEnable = exceptionRequestEnOrDis;
	SysTick_CounterHandling(sysTickHandler);
}

uint32_t SysTick_ReadCurrentCounterValue(SysTick_Handler_t *pSystickHandler){
	return pSystickHandler->pSysTick->CVR;
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
