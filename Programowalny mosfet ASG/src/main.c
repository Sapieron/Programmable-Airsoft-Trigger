/*
 * main.c
 *
 *  Created on: 16.08.2019
 *      Author: Pawel
 */


/*
 * PA0 -trigger, additional function: WKUP1
 * PA13 - SWDIO
 * PA14 - SWCLK
 *
 */

#include <stdint.h>
#include <STM32F030C8T6.h>
#include <STM32F030C8T6_gpio.h>


int main()
{
	GPIO_Handle_t LEDHandle;
	LEDHandle.pGPIOx = GPIOA;
	LEDHandle.PinConfig.PinNumber = GPIO_PIN_NUMBER_5;
	LEDHandle.PinConfig.PinMode = GPIO_MODE_OUTPUT;
	LEDHandle.PinConfig.PUPD = GPIO_PUPDR_NOPUPD;

	GPIO_Init(&LEDHandle);

	GPIO_WriteToOutput(&LEDHandle, ENABLE);

	while(1);
	return 0;
}
