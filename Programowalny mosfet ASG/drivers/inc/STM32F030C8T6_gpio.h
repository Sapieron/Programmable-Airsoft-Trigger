/*
 * STM32F030C8T6_gpio.h
 *
 *  Created on: 21.08.2019
 *      Author: Pawel
 */

#ifndef INC_STM32F030C8T6_GPIO_H_
#define INC_STM32F030C8T6_GPIO_H_

#include <STM32F030C8T6.h>

/*
 * MODEy bits - written to CRL/CRH to set speed (only if pin is used as output)
 */

//TODO zmienic te nazwy nizej na lepsze

#define GPIO_MODE_INPUT				0
#define GPIO_MODE_OUTPUT			1
#define GPIO_MODE_AF				2
#define GPIO_MODE_ANALOG			3

/*
 * CNFy - port configuration bits
 */

//if MODE[1:0] == 0, which means it's in input mode
#define GPIO_PIN_INPUT_ANALOG_MODE	0
#define GPIO_PIN_INPUT_FLOATING		1
#define GPIO_PIN_INPUT_W_PUPD		2


//if MODE[1:0] > 0, which means it's in output mode
#define GPIO_PUPDR_NOPUPD			0
#define GPIO_PUPDR_PULLUP			1
#define GPIO_PUPDR_PULLDOWN			2
#define GPIO_PUPDR_RESERVED			3


/*
 * Pin Numbers
 */
#define GPIO_PIN_NUMBER_0			0
#define GPIO_PIN_NUMBER_1			1
#define GPIO_PIN_NUMBER_2			2
#define GPIO_PIN_NUMBER_3			3
#define GPIO_PIN_NUMBER_4			4
#define GPIO_PIN_NUMBER_5			5
#define GPIO_PIN_NUMBER_6			6
#define GPIO_PIN_NUMBER_7			7
#define GPIO_PIN_NUMBER_8			8
#define GPIO_PIN_NUMBER_9			9
#define GPIO_PIN_NUMBER_10			10
#define GPIO_PIN_NUMBER_11			11
#define GPIO_PIN_NUMBER_12			12
#define GPIO_PIN_NUMBER_13			13
#define GPIO_PIN_NUMBER_14			14
#define GPIO_PIN_NUMBER_15			15

/***************************************************
 * *********************** TYPEDEFS ****************
 ***************************************************/
typedef struct
{
	volatile uint32_t PUPD;
	volatile uint32_t PinMode;
	volatile uint32_t PinNumber;
}GPIO_PinConfig_t;

typedef struct
{
	GPIO_RegDef_t *pGPIOx;
	GPIO_PinConfig_t PinConfig;
}GPIO_Handle_t;


void GPIO_Init(GPIO_Handle_t *pGPIOHandle);

void GPIO_WriteToOutput(GPIO_Handle_t *pGPIOHandle, uint8_t pinNumber, uint8_t enOrDis);

//void GPIO_IRQ_EXTI_Init(EXTI_RegDef_t *pEXTI ,uint8_t EXTItriggerType, uint8_t PinNumber);


uint8_t GPIO_ReadFromInput(GPIO_Handle_t *pGPIOHandle, uint8_t PinNumber);

void GPIO_ToggleOutputPin(GPIO_Handle_t *pGPIOHandle, uint8_t pinNumber);

//void GPIO_IRQHandling(EXTI_RegDef_t *pEXTI,uint8_t PinNumber);


#endif /* INC_STM32F030C8T6_GPIO_H_ */
