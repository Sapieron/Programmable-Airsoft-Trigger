/*
 * STM32F030C8T6_rcc.h
 *
 *  Created on: 29.08.2019
 *      Author: Pawel
 */

#ifndef INC_STM32F030C8T6_RCC_H_
#define INC_STM32F030C8T6_RCC_H_

#include <STM32F030C8T6.h>
#include <STM32F030C8T6_gpio.h>
#include <STM32F030C8T6_timer.h>

/******************************************************************************************
 ********************************* Main functions *****************************************
 ******************************************************************************************/

void RCC_GpioClockInit(GPIO_Handle_t *pGPIOHandle);

void RCC_GpioClockDeInit(GPIO_Handle_t *pGPIOHandle);

void RCC_SyscfgClockInit();

void RCC_SetAPBClockPrescaler(uint8_t prescalerAPB);

void RCC_SetAHBClockPrescaler(uint8_t prescalerAHB);

void RCCTimer6_7_ClockInitialize(TIMER6_7_Handler_t *pTIMER6_7_Handler);

void RCCTimer3_ClockInitialize(TIMER3_Handler_t *pTIMER3_Handler);


/******************************************************************************************
 ********************************* RCC macros defines *************************************
 ******************************************************************************************/

#define RCC_CFGR_PPRE			8		//PCLK prescaler (APB clock)
#define RCC_CFGR_HPRE			4		//HCLK prescaler (AHB clock)


#define RCC_AHBENR_IOPAEN		17
#define RCC_AHBENR_IOPBEN		18
#define RCC_AHBENR_IOPCEN		19
#define RCC_AHBENR_IOPDEN		20


#define RCC_AHBENR_IOPFEN		22


#define RCC_APB2ENR_TIMER1		11

#define RCC_APB2RSTR_TIMER1		11


#define RCC_APB1ENR_TIMER3		1
#define RCC_APB1ENR_TIMER6		4
#define RCC_APB1ENR_TIMER7		5


#define RCC_APB1RSTR_TIMER3		1
#define RCC_APB1RSTR_TIMER6		4
#define RCC_APB1RSTR_TIMER7		5


#define RCC_APB2ENR_SYSCFGEN	0


#define RCC_CFGR_PRESCALER_APB_divNONE	0
#define RCC_CFGR_PRESCALER_APB_div2		4
#define RCC_CFGR_PRESCALER_APB_div4		5
#define RCC_CFGR_PRESCALER_APB_div8		6
#define RCC_CFGR_PRESCALER_APB_div16	7


#define RCC_CFGR_PRESCALER_AHB_divNONE	0
#define RCC_CFGR_PRESCALER_AHB_div2		8
#define RCC_CFGR_PRESCALER_AHB_div4		9
#define RCC_CFGR_PRESCALER_AHB_div8		10
#define RCC_CFGR_PRESCALER_AHB_div16	11
#define RCC_CFGR_PRESCALER_AHB_div64	12
#define RCC_CFGR_PRESCALER_AHB_div128	13
#define RCC_CFGR_PRESCALER_AHB_div256	14
#define RCC_CFGR_PRESCALER_AHB_div512	15





#endif /* INC_STM32F030C8T6_RCC_H_ */
