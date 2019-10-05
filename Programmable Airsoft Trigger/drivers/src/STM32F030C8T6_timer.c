/*
 * STM32F030C8T6_timer.c
 *
 *  Created on: 01.09.2019
 *      Author: Pawel
 */

#include <STM32F030C8T6.h>
#include <STM32F030C8T6_timer.h>
#include <STM32F030C8T6_rcc.h>
#include <string.h>
#include <stdint.h>

/******************************************************************************************
 ********************** Private functions *************************************************
 ******************************************************************************************/
static void TIMER6_7_SetPrescalerValue(TIMER6_7_Handler_t *pTIMER6_7_Handler);

static void TIMER6_7_SetAutoReloadValue(TIMER6_7_Handler_t *pTIMER6_7_Handler);

static void TIMER6_7_SetInterruptValue(TIMER6_7_Handler_t *pTIMER6_7_Handler);

static void TIMER6_7_UpdateRegisters(TIMER6_7_Handler_t *pTIMER6_7_Handler);


static void TIMER3_SetPrescalerValue(TIMER3_Handler_t *pTIMER3_Handler);

static void TIMER3_SetAutoReloadValue(TIMER3_Handler_t *pTIMER3_Handler);

static void TIMER3_SetInterruptValue(TIMER3_Handler_t *pTIMER3_Handler);

static void TIMER3_UpdateRegisters(TIMER3_Handler_t *pTIMER3_Handler);


static uint16_t CheckAPBPrescaler();

static uint16_t CheckAHBPrescaler();

static void TimerSetDutyCycle(TIMER3_Handler_t *pTIMER3_Handler);

static void TimerSetFrequency(TIMER3_Handler_t *pTIMER3_Handler);

static void TimerARRisBufferedHandling(TIMER3_Handler_t *pTIMER3_Handler);

static uint8_t isPWMModeSelected(TIMER3_Handler_t *pTIMER3_Handler);

static void TimerCaptureCompareHandling(TIMER3_Handler_t *pTIMER3_Handler);

static void TIMER3_PWMModeHandling(TIMER3_Handler_t *pTIMER3_Handler);


/******************************************************************************************
 ********************** Main functions definitions ****************************************
 ******************************************************************************************/

void TIMER6_7_Init(TIMER6_7_Handler_t *pTIMER6_7_Handler){
	//TODO albo usunac albo poprawic
	RCCTimer6_7_ClockInitialize(pTIMER6_7_Handler);
	TIMER6_7_SetPrescalerValue(pTIMER6_7_Handler);
	TIMER6_7_SetAutoReloadValue(pTIMER6_7_Handler);
	TIMER6_7_SetInterruptValue(pTIMER6_7_Handler);

	TIMER6_7_UpdateRegisters(pTIMER6_7_Handler);

	TIMER6_7_CounterHandling(pTIMER6_7_Handler);
}

void TIMER3_Init(TIMER3_Handler_t *pTIMER3_Handler){
	RCCTimer3_ClockInitialize(pTIMER3_Handler);

	TIMER3_SetPrescalerValue(pTIMER3_Handler);
	TIMER3_SetAutoReloadValue(pTIMER3_Handler);
	TIMER3_UpdateRegisters(pTIMER3_Handler);
	TIMER3_SetInterruptValue(pTIMER3_Handler);
	TIMER3_PWMModeHandling(pTIMER3_Handler);
	TIMER3CounterHandling(pTIMER3_Handler);
}

void TIMER3_DeInit(TIMER3_Handler_t *pTIMER3_Handler){
	RCC_p->APB1RSTR |= (ENABLE << RCC_APB1ENR_TIMER3);
	RCC_p->APB1RSTR &= ~(ENABLE << RCC_APB1ENR_TIMER3);

	memset(&pTIMER3_Handler,CLEAR,sizeof(pTIMER3_Handler));
}

void TIMER6_7_CounterHandling(TIMER6_7_Handler_t *pTIMER6_7_Handler){
	pTIMER6_7_Handler->pTIMER6_7->CR1 &= ~(ENABLE << TIMER_CR1_CEN);
	pTIMER6_7_Handler->pTIMER6_7->CR1 |= (((uint16_t)pTIMER6_7_Handler->TIMER6_7Config.counterInitialize) << TIMER_CR1_CEN);
}

void TIMER3CounterHandling(TIMER3_Handler_t *pTIMER3_Handler){
	pTIMER3_Handler->pTIMER3->CR1 &= ~(ENABLE << TIMER_CR1_CEN);
	pTIMER3_Handler->pTIMER3->CR1 |= (((uint16_t)pTIMER3_Handler->TIMER3Config.counterInitialize) << TIMER_CR1_CEN);
	if(pTIMER3_Handler->TIMER3Config.PWMConfig.enablePWMMode){
		if(pTIMER3_Handler->TIMER3Config.PWMConfig.channel == TIMER_PWM_CONFIG_CHANNEL_1){
			pTIMER3_Handler->pTIMER3->CCER &= ~(ENABLE << TIMER_CCER_CC1E);
			pTIMER3_Handler->pTIMER3->CCER |=  (pTIMER3_Handler->TIMER3Config.counterInitialize << TIMER_CCER_CC1E);
		}
		else if(pTIMER3_Handler->TIMER3Config.PWMConfig.channel == TIMER_PWM_CONFIG_CHANNEL_2){

			pTIMER3_Handler->pTIMER3->CCER &= ~(ENABLE << TIMER_CCER_CC2E);
			pTIMER3_Handler->pTIMER3->CCER |=  (pTIMER3_Handler->TIMER3Config.counterInitialize << TIMER_CCER_CC2E);
		}

		else if(pTIMER3_Handler->TIMER3Config.PWMConfig.channel == TIMER_PWM_CONFIG_CHANNEL_3){
			pTIMER3_Handler->pTIMER3->CCER &= ~(ENABLE << TIMER_CCER_CC3E);
			pTIMER3_Handler->pTIMER3->CCER |=  (pTIMER3_Handler->TIMER3Config.counterInitialize << TIMER_CCER_CC3E);
		}

		else if(pTIMER3_Handler->TIMER3Config.PWMConfig.channel == TIMER_PWM_CONFIG_CHANNEL_4){
			pTIMER3_Handler->pTIMER3->CCER &= ~(ENABLE << TIMER_CCER_CC4E);
			pTIMER3_Handler->pTIMER3->CCER |=  (pTIMER3_Handler->TIMER3Config.counterInitialize << TIMER_CCER_CC4E);
		}
	}
}


/******************************************************************************************
 ********************** Private functions *************************************************
 ******************************************************************************************/

static void TIMER6_7_SetPrescalerValue(TIMER6_7_Handler_t *pTIMER6_7_Handler){
	*(volatile uint16_t*)&pTIMER6_7_Handler->pTIMER6_7->PSC = (((uint16_t)pTIMER6_7_Handler->TIMER6_7Config.prescalerValue) << TIMER_PSC_PSC);
}

static void TIMER6_7_SetAutoReloadValue(TIMER6_7_Handler_t *pTIMER6_7_Handler){
	*(volatile uint16_t*)&pTIMER6_7_Handler->pTIMER6_7->ARR = (((uint16_t)pTIMER6_7_Handler->TIMER6_7Config.autoReloadValue) << TIMER_ARR_ARR);
}

static void TIMER6_7_SetInterruptValue(TIMER6_7_Handler_t *pTIMER6_7_Handler){
	*(volatile uint16_t*)&pTIMER6_7_Handler->pTIMER6_7->DIER &= ~(ENABLE << TIMER_DIER_UIE);
	*(volatile uint16_t*)&pTIMER6_7_Handler->pTIMER6_7->DIER |= (((uint16_t)pTIMER6_7_Handler->TIMER6_7Config.interruptEnable) << TIMER_DIER_UIE);
}

static void TIMER6_7_UpdateRegisters(TIMER6_7_Handler_t *pTIMER6_7_Handler){
	*(volatile uint16_t*)&pTIMER6_7_Handler->pTIMER6_7->EGR |= (ENABLE << TIMER_EGR_UG);
}



static void TIMER3_SetPrescalerValue(TIMER3_Handler_t *pTIMER3_Handler){
	pTIMER3_Handler->pTIMER3->PSC = (pTIMER3_Handler->TIMER3Config.prescalerValue << TIMER_PSC_PSC);
}

static void TIMER3_SetAutoReloadValue(TIMER3_Handler_t *pTIMER3_Handler){
	*(volatile uint16_t*)&pTIMER3_Handler->pTIMER3->ARR = (((uint16_t)pTIMER3_Handler->TIMER3Config.autoReloadValue) << TIMER_ARR_ARR);
}

static void TIMER3_SetInterruptValue(TIMER3_Handler_t *pTIMER3_Handler){
	*(volatile uint16_t*)&pTIMER3_Handler->pTIMER3->DIER &= ~(ENABLE << TIMER_DIER_UIE);
	*(volatile uint16_t*)&pTIMER3_Handler->pTIMER3->DIER |= (((uint16_t)pTIMER3_Handler->TIMER3Config.interruptEnable) << TIMER_DIER_UIE);
}

static void TIMER3_UpdateRegisters(TIMER3_Handler_t *pTIMER3_Handler){
	*(volatile uint16_t*)&pTIMER3_Handler->pTIMER3->EGR |= (ENABLE << TIMER_EGR_UG);
}

static void TimerSetDutyCycle(TIMER3_Handler_t *pTIMER3_Handler){
	uint16_t resultToARRregister, resultToCCRRegister;
	uint32_t timeBase;

	timeBase = F_CPU / CheckAPBPrescaler() / CheckAHBPrescaler();

	resultToARRregister = timeBase / (pTIMER3_Handler->TIMER3Config.PWMConfig.frequencyInHz - 1);

	resultToCCRRegister = resultToARRregister  * pTIMER3_Handler->TIMER3Config.PWMConfig.dutyCycleInPercent / 100 ;

	if(pTIMER3_Handler->TIMER3Config.PWMConfig.channel == TIMER_PWM_CONFIG_CHANNEL_1)
		pTIMER3_Handler->pTIMER3->CCR1 = (resultToCCRRegister << TIMER_CCR1);
	else if(pTIMER3_Handler->TIMER3Config.PWMConfig.channel == TIMER_PWM_CONFIG_CHANNEL_2)
		pTIMER3_Handler->pTIMER3->CCR2 = (resultToCCRRegister << TIMER_CCR2);
	else if(pTIMER3_Handler->TIMER3Config.PWMConfig.channel == TIMER_PWM_CONFIG_CHANNEL_3)
		pTIMER3_Handler->pTIMER3->CCR3 = (resultToCCRRegister << TIMER_CCR3);
	else if(pTIMER3_Handler->TIMER3Config.PWMConfig.channel == TIMER_PWM_CONFIG_CHANNEL_4)
		pTIMER3_Handler->pTIMER3->CCR4 = (resultToCCRRegister << TIMER_CCR4);
}

static void TimerSetFrequency(TIMER3_Handler_t *pTIMER3_Handler){
	uint16_t resultToARRregister;
	uint32_t timeBase;

	timeBase = F_CPU / CheckAPBPrescaler() / CheckAHBPrescaler();

	resultToARRregister = timeBase / (pTIMER3_Handler->TIMER3Config.PWMConfig.frequencyInHz - 1);

	pTIMER3_Handler->pTIMER3->ARR = (resultToARRregister << TIMER_ARR_ARR);
}

static void TimerARRisBufferedHandling(TIMER3_Handler_t *pTIMER3_Handler){
	pTIMER3_Handler->pTIMER3->CR1 &= ~(ENABLE << TIMER_CR1_APRE);
	pTIMER3_Handler->pTIMER3->CR1 |= (ENABLE << TIMER_CR1_APRE);
}

static uint8_t isPWMModeSelected(TIMER3_Handler_t *pTIMER3_Handler){
	return pTIMER3_Handler->TIMER3Config.PWMConfig.enablePWMMode;
}

static uint16_t CheckAPBPrescaler(){
	if( ((RCC_p->CFGR >> RCC_CFGR_PPRE) & 0x7) == RCC_CFGR_PRESCALER_APB_div2)
			return 2;
	else if(((RCC_p->CFGR >> RCC_CFGR_PPRE) & 0x7) == RCC_CFGR_PRESCALER_APB_div4)
			return 4;
	else if(((RCC_p->CFGR >> RCC_CFGR_PPRE) & 0x7) == RCC_CFGR_PRESCALER_APB_div8)
			return 8;
	else if(((RCC_p->CFGR >> RCC_CFGR_PPRE) & 0x7) == RCC_CFGR_PRESCALER_APB_div16)
			return 16;
	return 1;
}

static uint16_t CheckAHBPrescaler(){
	if( ((RCC_p->CFGR >> RCC_CFGR_HPRE) & 0xF) == RCC_CFGR_PRESCALER_AHB_div2)
		return 2;
	else if(((RCC_p->CFGR >> RCC_CFGR_HPRE) & 0xF) == RCC_CFGR_PRESCALER_AHB_div4)
		return 4;
	else if(((RCC_p->CFGR >> RCC_CFGR_HPRE) & 0xF) == RCC_CFGR_PRESCALER_AHB_div8)
		return 8;
	else if(((RCC_p->CFGR >> RCC_CFGR_HPRE) & 0xF) == RCC_CFGR_PRESCALER_AHB_div16)
		return 16;
	else if(((RCC_p->CFGR >> RCC_CFGR_HPRE) & 0xF) == RCC_CFGR_PRESCALER_AHB_div64)
		return 64;
	else if(((RCC_p->CFGR >> RCC_CFGR_HPRE) & 0xF) == RCC_CFGR_PRESCALER_AHB_div128)
		return 128;
	else if(((RCC_p->CFGR >> RCC_CFGR_HPRE) & 0xF) == RCC_CFGR_PRESCALER_AHB_div256)
		return 256;
	else if(((RCC_p->CFGR >> RCC_CFGR_HPRE) & 0xF) == RCC_CFGR_PRESCALER_AHB_div512)
		return 512;
	return 1;
}



static void TimerCaptureCompareHandling(TIMER3_Handler_t *pTIMER3_Handler){
	if(pTIMER3_Handler->TIMER3Config.PWMConfig.channel == TIMER_PWM_CONFIG_CHANNEL_1){
			pTIMER3_Handler->pTIMER3->CCMR1 |= (pTIMER3_Handler->TIMER3Config.PWMConfig.PWMMode << TIMER_CCMR1_OC1M);
			pTIMER3_Handler->pTIMER3->CCMR1 |= (ENABLE << TIMER_CCMR1_OC1PE);
		}

		else if(pTIMER3_Handler->TIMER3Config.PWMConfig.channel == TIMER_PWM_CONFIG_CHANNEL_2){
			pTIMER3_Handler->pTIMER3->CCMR1 |= (pTIMER3_Handler->TIMER3Config.PWMConfig.PWMMode << TIMER_CCMR1_OC2M);
			pTIMER3_Handler->pTIMER3->CCMR1 |= (ENABLE << TIMER_CCMR1_OC2PE);

			pTIMER3_Handler->pTIMER3->CCER &= ~(ENABLE << TIMER_CCER_CC2E);
			pTIMER3_Handler->pTIMER3->CCER |=  (pTIMER3_Handler->TIMER3Config.counterInitialize << TIMER_CCER_CC2E);
		}

		else if(pTIMER3_Handler->TIMER3Config.PWMConfig.channel == TIMER_PWM_CONFIG_CHANNEL_3){
			pTIMER3_Handler->pTIMER3->CCMR2 |= (pTIMER3_Handler->TIMER3Config.PWMConfig.PWMMode << TIMER_CCMR2_OC3M);
			pTIMER3_Handler->pTIMER3->CCMR2 |= (ENABLE << TIMER_CCMR2_OC3PE);

			pTIMER3_Handler->pTIMER3->CCER &= ~(ENABLE << TIMER_CCER_CC3E);
			pTIMER3_Handler->pTIMER3->CCER |=  (pTIMER3_Handler->TIMER3Config.counterInitialize << TIMER_CCER_CC3E);
		}

		else if(pTIMER3_Handler->TIMER3Config.PWMConfig.channel == TIMER_PWM_CONFIG_CHANNEL_4){
			pTIMER3_Handler->pTIMER3->CCMR2 |= (pTIMER3_Handler->TIMER3Config.PWMConfig.PWMMode << TIMER_CCMR2_OC4M);
			pTIMER3_Handler->pTIMER3->CCMR2 |= (ENABLE << TIMER_CCMR2_OC4PE);

			pTIMER3_Handler->pTIMER3->CCER &= ~(ENABLE << TIMER_CCER_CC4E);
			pTIMER3_Handler->pTIMER3->CCER |=  (pTIMER3_Handler->TIMER3Config.counterInitialize << TIMER_CCER_CC4E);
		}
}


static void TIMER3_PWMModeHandling(TIMER3_Handler_t *pTIMER3_Handler){
	if(isPWMModeSelected(pTIMER3_Handler) ) {
		TimerSetFrequency(pTIMER3_Handler);
		TimerARRisBufferedHandling(pTIMER3_Handler);
		TimerSetDutyCycle(pTIMER3_Handler);
		TimerCaptureCompareHandling(pTIMER3_Handler);
	}
}
