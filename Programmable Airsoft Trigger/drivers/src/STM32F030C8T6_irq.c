/*
 * STM32F030C8T6_irq.c
 *
 *  Created on: 31.08.2019
 *      Author: Pawel
 */

#include <STM32F030C8T6.h>
#include <STM32F030C8T6_irq.h>

/******************************************************************************************
 ********************** Private functions *************************************************
 ******************************************************************************************/

static void SetIRQVector(uint8_t nvicIRQNumber);

static void ResetIRQVector(uint8_t nvicIRQNumber);

/******************************************************************************************
 ********************** Main functions definitions ****************************************
 ******************************************************************************************/

/*
Any of the external lines can be configured as software interrupt/event lines. The following is
the procedure to generate a software interrupt.
Configure the corresponding mask bit (EXTI_IMR, EXTI_EMR)
Set the required bit of the software interrupt register (EXTI_SWIER)*/


void EXTI_InitEvent(uint8_t extiNumber){
	EXTI_p->EMR |= (ENABLE << extiNumber);		//TODO: refactor ,,event mask register"
}

void EXTI_DeinitEvent(uint8_t extiNumber){
	EXTI_p->EMR &= ~(ENABLE << extiNumber);		//TODO: refactor ,,event mask register"
}

void EXTI_SWIER_Handling(uint8_t enOrDis, uint8_t extiNumber){
	EXTI_p->SWIER |= (enOrDis << extiNumber);
}

void NVIC_InitVector(uint8_t nvicIRQNumber){
	ResetIRQVector(nvicIRQNumber);
	SetIRQVector(nvicIRQNumber);
}

void NVIC_DeInitVector(uint8_t nvicIRQNumber){
	ResetIRQVector(nvicIRQNumber);
}

void NVIC_PendingRegisterHandling(uint8_t nvicIRQNumber){
	NVIC_p->ICPR |= (ENABLE << nvicIRQNumber);
}

/******************************************************************************************
 ********************** Private functions *************************************************
 ******************************************************************************************/

static void SetIRQVector(uint8_t nvicIRQNumber){
	NVIC_p->ICER &= ~(ENABLE << nvicIRQNumber);
	NVIC_p->ISER |= (ENABLE << nvicIRQNumber);
}

static void ResetIRQVector(uint8_t nvicIRQNumber){
	NVIC_p->ISER &= ~(ENABLE << nvicIRQNumber);
	NVIC_p->ICER |= (ENABLE << nvicIRQNumber);
}
