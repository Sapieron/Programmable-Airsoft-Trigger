/*
 * STM32F030C8T6_gpio.h
 *
 *  Created on: 21.08.2019
 *      Author: Pawel
 */

#ifndef INC_STM32F030C8T6_GPIO_H_
#define INC_STM32F030C8T6_GPIO_H_

#include <STM32F030C8T6.h>

/******************************************************************************************
 ********************************* Typedef structures *************************************
 ******************************************************************************************/

typedef struct{
	volatile uint32_t PUPD;
	volatile uint32_t PinMode;
	volatile uint32_t PinNumber;
	volatile uint32_t alternateFunMode;
}GPIO_PinConfig_t;

typedef struct{
	GPIO_RegDef_t *pGPIOx;
	GPIO_PinConfig_t PinConfig;
}GPIO_Handle_t;

/******************************************************************************************
 ********************************* Main functions *****************************************
 ******************************************************************************************/

void GPIOInit(GPIO_Handle_t *pGPIOHandle);

void GPIODeInit(GPIO_Handle_t *pGPIOHandle);

void GPIOWriteToOutputPin(GPIO_Handle_t *pGPIOHandle, uint8_t EnableOrDisable);

uint8_t GPIOReadFromInputPin(GPIO_Handle_t *pGPIOHandle);

uint8_t GPIO_IsPinPressed(GPIO_Handle_t *pGPIOHandle);

void GPIOToggleOutputPin(GPIO_Handle_t *pGPIOHandle);

void GPIOPendingRegisterHandling(GPIO_Handle_t *pGPIOHandle);

void GPIOIrqExtiInit(uint8_t EXTItriggerType, GPIO_Handle_t *pGPIOHandle);


/******************************************************************************************
 ********************************* GPIO Specific defines **********************************
 ******************************************************************************************/

#define GPIO_MODE_INPUT				0
#define GPIO_MODE_OUTPUT			1
#define GPIO_MODE_AF				2
#define GPIO_MODE_ANALOG			3


#define GPIO_ALTERNATE_FUN_MODE_AF0 0
#define GPIO_ALTERNATE_FUN_MODE_AF1 1
#define GPIO_ALTERNATE_FUN_MODE_AF2 2
#define GPIO_ALTERNATE_FUN_MODE_AF3 3
#define GPIO_ALTERNATE_FUN_MODE_AF4 4
#define GPIO_ALTERNATE_FUN_MODE_AF5 5
#define GPIO_ALTERNATE_FUN_MODE_AF6 6
#define GPIO_ALTERNATE_FUN_MODE_AF7 7
#define GPIO_ALTERNATE_FUN_MODE_AF8 0
#define GPIO_ALTERNATE_FUN_MODE_AF9 1
#define GPIO_ALTERNATE_FUN_MODE_AF10 2
#define GPIO_ALTERNATE_FUN_MODE_AF11 3
#define GPIO_ALTERNATE_FUN_MODE_AF12 4
#define GPIO_ALTERNATE_FUN_MODE_AF13 5
#define GPIO_ALTERNATE_FUN_MODE_AF14 6
#define GPIO_ALTERNATE_FUN_MODE_AF15 7


#define GPIO_PUPDR_NOPUPD			0
#define GPIO_PUPDR_PULLUP			1
#define GPIO_PUPDR_PULLDOWN			2
#define GPIO_PUPDR_RESERVED			3


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


#endif /* INC_STM32F030C8T6_GPIO_H_ */
