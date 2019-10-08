/*
 * STM32F030C8T6_systick.h
 *
 *  Created on: 08.09.2019
 *      Author: Pawel
 */

#ifndef INC_STM32F030C8T6_SYSTICK_H_
#define INC_STM32F030C8T6_SYSTICK_H_

#include <stdint.h>

/******************************************************************************************
 ********************************* Main functions *****************************************
 ******************************************************************************************/


typedef struct{
	uint32_t autoReloadValue;
	uint32_t counterValue;
	uint32_t counterInitialize;
	uint32_t exceptionRequestEnable;
	uint32_t clockSource;
}SysTick_Config_t;


typedef struct{
	SYSTICK_RegDef_t *pSysTick;
	SysTick_Config_t config;
}SysTick_Handler_t;

void SysTickInit(SysTick_Handler_t *pSystickHandler);

void SysTickCounterHandling(SysTick_Handler_t *pSystickHandler);

uint8_t isSysTickFlagSet(SysTick_Handler_t *pSystickHandler);

void Systick_EnableTimerForSetTimeInMs(SysTick_Handler_t *sysTickHandler, uint32_t delayTime, uint8_t interruptEnOrDis);

uint32_t SysTickReadCurrentCounterValue(SysTick_Handler_t *pSystickHandler);

/******************************************************************************************
 ********************************* Systick macros and defines *****************************
 ******************************************************************************************/

#define SYSTICK_CSR_CLKSOURCE_EXTERNAL		0
#define SYSTICK_CSR_CLKSOURCE_PROC_CLK		1


#define SYSTICK_CSR_ENABLE		0
#define SYSTICK_CSR_TICKINT		1
#define SYSTICK_CSR_CLKSOURCE	2
#define SYSTICK_CSR_COUNTFLAG	16


#define SYSTICK_RVR_RELOAD		0


#define SYSTICK_CVR_CURRENT		0


#define SYSTICK_CALIB_TENMS		0
#define SYSTICK_CALIB_SKEW		30
#define SYSTICK_CALIB_NOREF		31


#endif /* INC_STM32F030C8T6_SYSTICK_H_ */
