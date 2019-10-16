/*
 * PASGM_Lib.h
 *
 *  Created on: Oct 6, 2019
 *      Author: pawel
 */

#ifndef PASGM_LIB_H_
#define PASGM_LIB_H_

#include <STM32F030C8T6.h>
#include <STM32F030C8T6_systick.h>
#include <STM32F030C8T6_timer.h>
#include <STM32F030C8T6_gpio.h>
#include <stdint.h>

/******************************************************************************************
 ********************************* Typedef structures *************************************
 ******************************************************************************************/

typedef struct{
	uint16_t beepForTimes;
	uint16_t intervalOfBeepsInMs;
	uint16_t durationOfBeepInMs;
}PASGM_BeepMotorHandler_t;

/******************************************************************************************
 ********************************* Main functions *****************************************
 ******************************************************************************************/

void PASGM_StartUserProgrammingProcedure();

void PASGM_TurnOffMCU();

void PASGM_BeepMotorHandling(PASGM_BeepMotorHandler_t *BeepMotorHandler, SysTick_Handler_t *sysTickHandler, TIMER3_Handler_t *motorBeeping);

#endif /* PASGM_LIB_H_ */
