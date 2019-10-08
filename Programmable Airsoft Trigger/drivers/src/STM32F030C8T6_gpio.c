/*
 * STM32F030C8T6_driver.c
 *
 *  Created on: 21.08.2019
 *      Author: Pawel
 */

#include <STM32F030C8T6.h>
#include <STM32F030C8T6_gpio.h>
#include <STM32F030C8T6_rcc.h>
#include <STM32F030C8T6_irq.h>
#include <stdint.h>
#include <string.h>

/******************************************************************************************
 ********************** Private functions *************************************************
 ******************************************************************************************/

static void EnableNVICInterrupt(GPIO_Handle_t *pGPIOHandle);

static void SetInterruptTriggerType(GPIO_Handle_t *pGPIOHandle,uint8_t EXTItriggerType);

static void EnableInterruptMaskRegister(GPIO_Handle_t *pGPIOHandle);

static uint8_t GPIOtoPortCode(GPIO_Handle_t * pGPIOHandle);

static void ConfigureSYSCFGinterruptRegisters(GPIO_Handle_t * pGPIOHandle);

static void GPIOSetPin(GPIO_Handle_t *pGPIOHandle);

static void GPIOResetPin(GPIO_Handle_t *pGPIOHandle);

static uint8_t isOutputSet(GPIO_Handle_t *pGPIOHandle);

static uint8_t isPendingRegisterSet(GPIO_Handle_t *pGPIOHandle);

static void resetPendingRegister(GPIO_Handle_t *pGPIOHandle);

static void GPIOSetPUPDR(GPIO_Handle_t *pGPIOHandle);

static void GPIOResetPUPDR(GPIO_Handle_t *pGPIOHandle);

static void GPIOSetMODER(GPIO_Handle_t *pGPIOHandle);

static void GPIOResetMODER(GPIO_Handle_t *pGPIOHandle);

static void GPIOSetAFRegister(GPIO_Handle_t *pGPIOHandle);

/******************************************************************************************
 ********************** Main functions definitions ****************************************
 ******************************************************************************************/

void GPIOInit(GPIO_Handle_t *pGPIOHandle){
	RCCGpioClockInit(pGPIOHandle);
	GPIOSetMODER(pGPIOHandle);
	GPIOSetPUPDR(pGPIOHandle);
	GPIOSetAFRegister(pGPIOHandle);
}

void GPIODeInit(GPIO_Handle_t *pGPIOHandle){
	RCCGpioClockDeInit(pGPIOHandle);
	GPIOResetMODER(pGPIOHandle);
	GPIOResetPUPDR(pGPIOHandle);
}

void GPIOWriteToOutputPin(GPIO_Handle_t *pGPIOHandle, uint8_t EnableOrDisable){
	if(EnableOrDisable == ENABLE)
		GPIOSetPin(pGPIOHandle);
	else
		GPIOResetPin(pGPIOHandle);
}

uint8_t GPIOReadFromInputPin(GPIO_Handle_t *pGPIOHandle){
	return ( (pGPIOHandle->pGPIOx->IDR & ( 1 << pGPIOHandle->PinConfig.PinNumber) ) >> pGPIOHandle->PinConfig.PinNumber);
}

void GPIOToggleOutputPin(GPIO_Handle_t *pGPIOHandle){
	if(isOutputSet(pGPIOHandle))
		GPIOResetPin(pGPIOHandle);
	else
		GPIOSetPin(pGPIOHandle);
}

void GPIOPendingRegisterHandling(GPIO_Handle_t *pGPIOHandle){
	if(isPendingRegisterSet(pGPIOHandle))
		resetPendingRegister(pGPIOHandle);
}

void GPIOIrqExtiInit(uint8_t EXTItriggerType, GPIO_Handle_t *pGPIOHandle){
	RCCSyscfgClockInit();
	EnableInterruptMaskRegister(pGPIOHandle);
	SetInterruptTriggerType(pGPIOHandle,EXTItriggerType);
	if ( pGPIOHandle->PinConfig.PinMode == GPIO_MODE_AF )
		EnableNVICInterrupt(pGPIOHandle);
	ConfigureSYSCFGinterruptRegisters(pGPIOHandle);
}

uint8_t GPIO_IsPinPressed(GPIO_Handle_t *pGPIOHandle){
	if(pGPIOHandle->PinConfig.PUPD == GPIO_PUPDR_PULLDOWN)
	return GPIOReadFromInputPin(pGPIOHandle);
	else if(pGPIOHandle->PinConfig.PUPD == GPIO_PUPDR_PULLUP)
	return !GPIOReadFromInputPin(pGPIOHandle);
	return GPIOReadFromInputPin(pGPIOHandle);
}

/******************************************************************************************
 ********************** Private functions *************************************************
 ******************************************************************************************/

static void EnableNVICInterrupt(GPIO_Handle_t *pGPIOHandle){
	if(pGPIOHandle->PinConfig.PinNumber <=1)
		NVIC_p->ISER |= (SET << NVIC_IRQNUMBER_EXTI0_1);
	else if(pGPIOHandle->PinConfig.PinNumber > 2 && pGPIOHandle->PinConfig.PinNumber <=3)
		NVIC_p->ISER |= (SET << NVIC_IRQNUMBER_EXTI2_3);
	else if(pGPIOHandle->PinConfig.PinNumber > 4 && pGPIOHandle->PinConfig.PinNumber <=15)
		NVIC_p->ISER |= (SET << NVIC_IRQNUMBER_EXTI4_15);
}

static void SetInterruptTriggerType(GPIO_Handle_t *pGPIOHandle,uint8_t EXTItriggerType){
	if(EXTItriggerType == GPIO_EXTI_FallingTrigSR)
		EXTI_p->FTSR |= (ENABLE << pGPIOHandle->PinConfig.PinNumber);
	else if(EXTItriggerType == GPIO_EXTI_RisingTrigSR)
		EXTI_p->RTSR |= (ENABLE << pGPIOHandle->PinConfig.PinNumber);
}

static void EnableInterruptMaskRegister(GPIO_Handle_t *pGPIOHandle){
	EXTI_p->IMR |= (ENABLE << pGPIOHandle->PinConfig.PinNumber);
}

static uint8_t GPIOtoPortCode(GPIO_Handle_t * pGPIOHandle){
	uint8_t portCode;
	if(pGPIOHandle->pGPIOx == GPIOA_p)
		portCode = 0;
	else if(pGPIOHandle->pGPIOx == GPIOB_p)
		portCode = 1;
	else if(pGPIOHandle->pGPIOx == GPIOC_p)
		portCode = 2;
	else if(pGPIOHandle->pGPIOx == GPIOD_p)
		portCode = 3;
	else if(pGPIOHandle->pGPIOx == GPIOF_p)
		portCode = 5;
	return portCode;
}

static void ConfigureSYSCFGinterruptRegisters(GPIO_Handle_t * pGPIOHandle){
	uint8_t portCode = GPIOtoPortCode(pGPIOHandle);

	if(pGPIOHandle->PinConfig.PinNumber < 4)
		SYSCFG_p->EXTICR1 |= (portCode << pGPIOHandle->PinConfig.PinNumber % 4 * 4);
	else if((pGPIOHandle->PinConfig.PinNumber >= 4 ) && (pGPIOHandle->PinConfig.PinNumber < 8))
		SYSCFG_p->EXTICR2 |= (portCode << pGPIOHandle->PinConfig.PinNumber % 4 * 4 );
	else if((pGPIOHandle->PinConfig.PinNumber >= 8) && (pGPIOHandle->PinConfig.PinNumber < 12))
		SYSCFG_p->EXTICR3 |= (portCode << pGPIOHandle->PinConfig.PinNumber % 4 * 4 );
	else if((pGPIOHandle->PinConfig.PinNumber >= 12) && (pGPIOHandle->PinConfig.PinNumber < 16))
		SYSCFG_p->EXTICR4 |= (portCode << pGPIOHandle->PinConfig.PinNumber % 4 * 4 );
}

static void GPIOSetPin(GPIO_Handle_t *pGPIOHandle){
	pGPIOHandle->pGPIOx->BSRR |= (ENABLE << pGPIOHandle->PinConfig.PinNumber);
}

static void GPIOResetPin(GPIO_Handle_t *pGPIOHandle){
	pGPIOHandle->pGPIOx->BSRR |= (ENABLE << (pGPIOHandle->PinConfig.PinNumber + 16));
}

static uint8_t isOutputSet(GPIO_Handle_t *pGPIOHandle){
	return ( pGPIOHandle->pGPIOx->ODR & (SET << pGPIOHandle->PinConfig.PinNumber) ) >> pGPIOHandle->PinConfig.PinNumber;
}

static uint8_t isPendingRegisterSet(GPIO_Handle_t *pGPIOHandle){
	return ( EXTI_p->PR & (ENABLE << pGPIOHandle->PinConfig.PinNumber) ) >> pGPIOHandle->PinConfig.PinNumber;
}

static void resetPendingRegister(GPIO_Handle_t *pGPIOHandle){
	EXTI_p->PR = (ENABLE << pGPIOHandle->PinConfig.PinNumber);
}

static void GPIOSetPUPDR(GPIO_Handle_t *pGPIOHandle){
	pGPIOHandle->pGPIOx->PUPDR |= (pGPIOHandle->PinConfig.PUPD << pGPIOHandle->PinConfig.PinNumber * 2);
}

static void GPIOResetPUPDR(GPIO_Handle_t *pGPIOHandle){
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->PinConfig.PinNumber * 2);
}

static void GPIOSetMODER(GPIO_Handle_t *pGPIOHandle){
	pGPIOHandle->pGPIOx->MODER |= (pGPIOHandle->PinConfig.PinMode << pGPIOHandle->PinConfig.PinNumber*2);
}

static void GPIOResetMODER(GPIO_Handle_t *pGPIOHandle){
	pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->PinConfig.PinNumber*2);
}

static void GPIOSetAFRegister(GPIO_Handle_t *pGPIOHandle){
	if(pGPIOHandle->PinConfig.alternateFunMode <= GPIO_ALTERNATE_FUN_MODE_AF7)
	pGPIOHandle->pGPIOx->AFRL |= (pGPIOHandle->PinConfig.alternateFunMode << (4 * pGPIOHandle->PinConfig.PinNumber) );
	else pGPIOHandle->pGPIOx->AFRH |= (pGPIOHandle->PinConfig.alternateFunMode << (4 * pGPIOHandle->PinConfig.PinNumber) );
}



