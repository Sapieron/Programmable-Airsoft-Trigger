/*
 * PASGM_Lib.c
 *
 *  Created on: Oct 6, 2019
 *      Author: pawel
 */

#include <PASGM_Lib.h>

/******************************************************************************************
 ********************** Private functions *************************************************
 ******************************************************************************************/



/******************************************************************************************
 ********************** Main functions definitions ****************************************
 ******************************************************************************************/

void PASGM_StartUserProgrammingProcedure(){
	//TODO Write this procedure
	//TODO use flash memory to store last remembered configuration
}

void PASGM_BeepMotorHandling(PASGM_BeepMotorHandler_t *BeepMotorHandler, SysTick_Handler_t *sysTickHandler, TIMER3_Handler_t *motorBeeping){
	sysTickHandler->config.counterInitialize = DISABLE;
	SysTick_CounterHandling(sysTickHandler);

	sysTickHandler->config.autoReloadValue = TIME_BASE_OF_ONE_MS_FOR_SYSTICK * (BeepMotorHandler->durationOfBeepInMs + BeepMotorHandler->durationOfBeepInMs);
	sysTickHandler->config.counterValue = 0;
	SysTick_Init(sysTickHandler);

	sysTickHandler->config.counterInitialize = ENABLE;
	SysTick_CounterHandling(sysTickHandler);

	for(uint16_t i = 0; i < BeepMotorHandler->beepForTimes ; ++i){
		motorBeeping->TIMER3Config.counterInitialize = ENABLE;
		TIMER3_CounterHandling(motorBeeping);

		while( (sysTickHandler->config.autoReloadValue - (TIME_BASE_OF_ONE_MS_FOR_SYSTICK * BeepMotorHandler->durationOfBeepInMs) ) <= SysTick_ReadCurrentCounterValue(sysTickHandler) );

		motorBeeping->TIMER3Config.counterInitialize = DISABLE;
		TIMER3_CounterHandling(motorBeeping);

		while( ! SysTick_isFlagSet(sysTickHandler) );
	}
	sysTickHandler->config.counterInitialize = DISABLE;
	SysTick_CounterHandling(sysTickHandler);
}

/******************************************************************************************
 ********************** Private functions *************************************************
 ******************************************************************************************/


