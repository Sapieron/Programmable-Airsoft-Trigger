/*
 * STM32F030C8T6_irq.h
 *
 *  Created on: 31.08.2019
 *      Author: Pawel
 */

#ifndef INC_STM32F030C8T6_IRQ_H_
#define INC_STM32F030C8T6_IRQ_H_


/******************************************************************************************
 ********************************* Main functions *****************************************
 ******************************************************************************************/

void NVIC_InitVector(uint8_t nvicIRQNumber);

void NVIC_DeInitVector(uint8_t nvicIRQNumber);

void NVIC_PendingRegisterHandling(uint8_t nvicIRQNumber);

void EXTI_InitEvent(uint8_t extiNumber);

void EXTI_DeinitEvent(uint8_t extiNumber);

void EXTI_SWIER_Handling(uint8_t enOrDis, uint8_t extiNumber);

/******************************************************************************************
 ********************************* NVIC and EXTI macros ***********************************
 ******************************************************************************************/

#define GPIO_EXTI_FallingTrigSR			0
#define GPIO_EXTI_RisingTrigSR			1


#define NVIC_IRQNUMBER_EXTI0_1		5
#define NVIC_IRQNUMBER_EXTI2_3		6
#define NVIC_IRQNUMBER_EXTI4_15		7
#define NVIC_IRQNUMBER_TIMER1_CC	14
#define NVIC_IRQNUMBER_TIMER3		16
#define NVIC_IRQNUMBER_TIMER6		17


#endif /* INC_STM32F030C8T6_IRQ_H_ */
