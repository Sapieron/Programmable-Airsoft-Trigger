/*
 * STM32F030C8T6_driver.c
 *
 *  Created on: 21.08.2019
 *      Author: Pawel
 */



#include <STM32F030C8T6.h>
#include <STM32F030C8T6_gpio.h>
#include <stdint.h>

/************************************************************
 * ******************** MAIN FUNCTIONS DEFINITIONS***********
 ************************************************************/

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)		//this function implements only ENABLE of the peripheral
{
	if(pGPIOHandle->pGPIOx == GPIOA)
	{
		RCC_p->APB2ENR |= (1 << RCC_APB2ENR_IOPAEN);
	}
	else if (pGPIOHandle->pGPIOx == GPIOB)
	{
		RCC_p->APB2ENR |= (1 << RCC_APB2ENR_IOPBEN);
	}
	else if (pGPIOHandle->pGPIOx == GPIOC)
	{
		RCC_p->APB2ENR |= (1 << RCC_APB2ENR_IOPCEN);
	}
	else if (pGPIOHandle->pGPIOx == GPIOD)
	{
		RCC_p->APB2ENR |= (1 << RCC_APB2ENR_IOPDEN);
	}
	else if (pGPIOHandle->pGPIOx == GPIOF)
	{
		RCC_p->APB2ENR |= (1 << RCC_APB2ENR_IOPFEN);
	}
	if(pGPIOHandle->PinConfig.PinNumber < 8)
	{								//if PinNumer is lesser than 8, then all configs should be made within CRL register
		pGPIOHandle->pGPIOx->CRL &= ~(0x3 << pGPIOHandle->PinConfig.PinNumber*4);
		pGPIOHandle->pGPIOx->CRL &= ~(0x3 << (pGPIOHandle->PinConfig.PinNumber * 4 + 2));
		pGPIOHandle->pGPIOx->CRL |= (pGPIOHandle->PinConfig.PinMode << pGPIOHandle->PinConfig.PinNumber*4);			//Set Mode to output or input
		pGPIOHandle->pGPIOx->CRL |= (pGPIOHandle->PinConfig.PinInOrOut << (pGPIOHandle->PinConfig.PinNumber * 4 + 2));

	}
	else
	{
		pGPIOHandle->pGPIOx->CRH &= ~(0x3 << ((pGPIOHandle->PinConfig.PinNumber % 8 ) * 4 + 2));
		pGPIOHandle->pGPIOx->CRH &= ~(0x3 << ((pGPIOHandle->PinConfig.PinNumber % 8 )*4));
		pGPIOHandle->pGPIOx->CRH |= (pGPIOHandle->PinConfig.PinInOrOut << ((pGPIOHandle->PinConfig.PinNumber % 8 )* 4 + 2));
		pGPIOHandle->pGPIOx->CRH |= (pGPIOHandle->PinConfig.PinMode << ((pGPIOHandle->PinConfig.PinNumber % 8 )*4));

	}
}



void GPIO_WriteToOutput(GPIO_Handle_t *pGPIOHandle, uint8_t pinNumber, uint8_t enOrDis)
{
	if(enOrDis == ENABLE)
	{
		pGPIOHandle->pGPIOx->BSRR |= (ENABLE << pinNumber);		//Atomic set
	}
	else
	{
		pGPIOHandle->pGPIOx->BSRR |= (DISABLE << (pinNumber + 16));
	}
}



uint8_t GPIO_ReadFromInput(GPIO_Handle_t *pGPIOHandle, uint8_t PinNumber)
{
	uint8_t result=0;
	result = (pGPIOHandle->pGPIOx->IDR & ( 1 << PinNumber));

	return result;
}


void GPIO_ToggleOutputPin(GPIO_Handle_t *pGPIOHandle, uint8_t pinNumber)
{
	//check if the output is set or reset, then perform write to corresponding BSRR register
	if(!(pGPIOHandle->pGPIOx->ODR & (1 << pinNumber))) 	//check if output is disabled
		{
			pGPIOHandle->pGPIOx->BSRR |= (ENABLE << pinNumber);		//if it's disabled, then enable
		}
		else
		{
			pGPIOHandle->pGPIOx->BSRR |= (ENABLE << (pinNumber + 16));
		}
}

//TODO
//void IRQ_Config(uint32_t IRQ_Number, uint8_t enOrDis)
//{
//	if(enOrDis == ENABLE)
//	{
//		if(IRQ_Number <= 31)
//			*(NVIC_ISER0) |= (1 << IRQ_Number);
//		else if(IRQ_Number > 31 && IRQ_Number <=63)
//			*(NVIC_ISER1) |= (1 << IRQ_Number%32);
//		else if(IRQ_Number > 63 && IRQ_Number <=80)
//			*(NVIC_ISER2) |= (1 << IRQ_Number%32);
//	}
//	else
//	{
//		if(IRQ_Number <= 31)
//			*(NVIC_ICER0) |= (1 << IRQ_Number);
//		else if(IRQ_Number > 31 && IRQ_Number <=63)
//			*(NVIC_ICER1) |= (1 << IRQ_Number);
//		else if(IRQ_Number > 63 && IRQ_Number <=80)
//			*(NVIC_ICER2) |= (1 << IRQ_Number);
//	}
//}


void GPIO_IRQHandling(EXTI_RegDef_t *pEXTI,uint8_t PinNumber)
{
	//1. Clean the PR register
	if(pEXTI->PR & (ENABLE << PinNumber))
		pEXTI->PR |= (ENABLE << PinNumber);
}

void GPIO_IRQ_EXTI_Init(EXTI_RegDef_t *pEXTI ,uint8_t EXTItriggerType, uint8_t PinNumber)
{
	if(!(RCC_p->APB2ENR & (ENABLE << 0)))
	{
		RCC_p->APB2ENR |= (ENABLE << 0);		//set AFIO clock
	}
	pEXTI->IMR |= (ENABLE << PinNumber);
	//set FT or RT
	if(EXTItriggerType == EXTI_IMR_FTSR)
	{
		pEXTI->FTSR |= (ENABLE << PinNumber);
	}
	else if(EXTItriggerType == EXTI_IMR_RTSR)
	{
		pEXTI->RTSR |= (ENABLE << PinNumber);
	}
}




