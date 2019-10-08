/*
 * STM32F030C8T6_timer.h
 *
 *  Created on: 01.09.2019
 *      Author: Pawel
 */

#ifndef INC_STM32F030C8T6_TIMER_H_
#define INC_STM32F030C8T6_TIMER_H_

#include <STM32F030C8T6.h>

/******************************************************************************************
 ********************************* TIMER  Structures **************************************
 ******************************************************************************************/

typedef struct
{
	uint32_t enablePWMMode;
	uint32_t PWMMode;
	uint32_t channel;
	uint32_t dutyCycleInPercent;
	uint32_t frequencyInHz;
	uint32_t ActivePolarity;
}TIMER_PwmConfig;

typedef struct
{
	uint32_t counterEnable;
	uint32_t interruptEnable;
	uint32_t counterValue;
	uint32_t prescalerValue;
	uint32_t autoReloadValue;
}TIMER1_Config_t;

typedef struct
{
	uint32_t counterInitialize;
	uint32_t interruptEnable;
	uint32_t counterValue;
	uint32_t prescalerValue;
	uint32_t autoReloadValue;
	TIMER_PwmConfig PWMConfig;
}TIMER3_Config_t;


typedef struct
{
	uint32_t counterInitialize;
	uint32_t interruptEnable;
	uint32_t counterValue;
	uint32_t prescalerValue;
	uint32_t autoReloadValue;
}TIMER6_7_Config_t;



typedef struct
{
	TIMER1_RegDef_t *pTIMER1;
	TIMER1_Config_t	TIMER1Config;
}TIMER1_Handler_t;

typedef struct
{
	TIMER3_RegDef_t *pTIMER3;
	TIMER3_Config_t TIMER3Config;
}TIMER3_Handler_t;

typedef struct
{
	TIMER6_7_RegDef_t *pTIMER6_7;
	TIMER6_7_Config_t TIMER6_7Config;
}TIMER6_7_Handler_t;



/******************************************************************************************
 ********************************* Main functions *****************************************
 ******************************************************************************************/

void TIMER6_7_Init(TIMER6_7_Handler_t *pTIMER6_7_Handler);

void TIMER6_7_CounterHandling(TIMER6_7_Handler_t *pTIMER6_7_Handler);

void TIMER3_Init(TIMER3_Handler_t *pTIMER3_Handler);

void TIMER3_DeInit(TIMER3_Handler_t *pTIMER3_Handler);

void TIMER3CounterHandling(TIMER3_Handler_t *pTIMER3_Handler);


/******************************************************************************************
 ********************************* TIMER Specific defines **********************************
 ******************************************************************************************/

#define TIMER_PWM_CONFIG_MODE_PWM1		 6
#define TIMER_PWM_CONFIG_MODE_PWM2		 7


#define TIMER_PWM_CONFIG_CHANNEL_1		 1
#define TIMER_PWM_CONFIG_CHANNEL_2		 2
#define TIMER_PWM_CONFIG_CHANNEL_3		 3
#define TIMER_PWM_CONFIG_CHANNEL_4		 4


#define TIMER_PWM_CONFIG_ACTIVE_POLARITY_HIGH	 0
#define TIMER_PWM_CONFIG_ACTIVE_POLARITY_LOW	 1


#define TIMER_CR1_CEN		0
#define TIMER_CR1_UDIS		1
#define TIMER_CR1_URS		2
#define TIMER_CR1_OPM		3
#define TIMER_CR1_APRE		7


#define TIMER_DIER_UIE		0
#define TIMER_DIER_UDE		8


#define TIMER_SR_UIF		0


#define TIMER_EGR_UG		0


#define TIMER_CNT_CNT		0


#define TIMER_PSC_PSC		0


#define TIMER_ARR_ARR		0


#define TIMER_CCR1			0
#define TIMER_CCR2			0
#define TIMER_CCR3			0
#define TIMER_CCR4			0


#define TIMER_CCMR1_CC1S	0
#define TIMER_CCMR1_OC1FE	2
#define TIMER_CCMR1_OC1PE	3
#define TIMER_CCMR1_OC1M	4
#define TIMER_CCMR1_OC1CE	7
#define TIMER_CCMR1_CC2S	8
#define TIMER_CCMR1_OC2FE	10
#define TIMER_CCMR1_OC2PE	11
#define TIMER_CCMR1_OC2M	12
#define TIMER_CCMR1_OC2CE	15


#define TIMER_CCMR2_CC3S	0
#define TIMER_CCMR2_OC3FE	2
#define TIMER_CCMR2_OC3PE	3
#define TIMER_CCMR2_OC3M	4
#define TIMER_CCMR2_OC3CE	7
#define TIMER_CCMR2_CC4S	8
#define TIMER_CCMR2_OC4FE	10
#define TIMER_CCMR2_OC4PE	11
#define TIMER_CCMR2_OC4M	12
#define TIMER_CCMR2_OC4CE	15


#define TIMER_CCER_CC1E		0
#define TIMER_CCER_CC1P		1
#define TIMER_CCER_CC1NP	3
#define TIMER_CCER_CC2E		4
#define TIMER_CCER_CC2P		5
#define TIMER_CCER_CC2NP	7
#define TIMER_CCER_CC3E		8
#define TIMER_CCER_CC3P		9
#define TIMER_CCER_CC3NP	11
#define TIMER_CCER_CC4E		12
#define TIMER_CCER_CC4P		13
#define TIMER_CCER_CC4NP	15

#endif /* INC_STM32F030C8T6_TIMER_H_ */
