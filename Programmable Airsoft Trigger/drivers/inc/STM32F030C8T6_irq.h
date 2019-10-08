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

void NVICInitVector(uint8_t nvicIRQNumber);

void NVICDeInitVector(uint8_t nvicIRQNumber);

void NVICPendingRegisterHandling(uint8_t nvicIRQNumber);

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
