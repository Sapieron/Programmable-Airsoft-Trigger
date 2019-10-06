/* ******************************************
    Programmable Trigger for airsoft replicas
    Copyright (c) 2019 Pawe� Klisz (pawelochojec@gmail.com)
    [Released under MIT License. Please refer to license.txt for details]
   ****************************************** */

#include <PASGM_Lib.h>
#include <stdint.h>
#include <string.h>
#include <STM32F030C8T6.h>
#include <STM32F030C8T6_gpio.h>
#include <STM32F030C8T6_rcc.h>
#include <STM32F030C8T6_irq.h>
#include <STM32F030C8T6_timer.h>
#include <STM32F030C8T6_systick.h>
#include <STM32F030C8T6_pwr.h>

/*		TODO to wrzucic do readme
 * PA0 - trigger, additional function: WKUP1
 * PA1 - SEMI pushbutton
 * PA2 - GEAR pushbutton
 * PA3 - AUTO pushbutton
 * PA4 - motorOutput CIRCUIT
 *
 * PA9 - I2C1_SCL
 * PA10 - I2C1_SDA
 *
 * PA13 - SWDIO
 * PA14 - SWCLK
 *
 */

/*
 * TODO: dodac CRC, wywolanie trybu z pamieci
 */

#define MOTOR_PWM_FREQUENCY_IN_HZ 				1000
#define MOTOR_PWM_DUTY_CYCLE_IN_PERCENT			2

void Setup();

void BeepMotorHandling(uint8_t numberOfCycles, uint32_t intervalInMs, uint32_t durationOfSingleBeep);

GPIO_Handle_t autoHandler_t,
semiHandler_t,
triggerHandler_t,
gearSensorHandler_t,
motorHandler_t,
testLEDHandler;

TIMER3_Handler_t motorBeeping;

SysTick_Handler_t sysTickHandler;

int main(void){
	Setup();

	if(GPIO_IsPinPressed(&semiHandler_t) || GPIO_IsPinPressed(&autoHandler_t) || GPIO_IsPinPressed(&triggerHandler_t)){
		GPIODeInit(&semiHandler_t);
		GPIODeInit(&autoHandler_t);
		GPIODeInit(&triggerHandler_t);
		GPIODeInit(&motorHandler_t);
		//TODO restart MCU
	}

	uint16_t beepForTimes = 2;
	uint16_t intervalOfBeeps = 400;
	uint16_t durationOfBeep = 200;
	BeepMotorHandling(beepForTimes, intervalOfBeeps, durationOfBeep);

	sysTickHandler.config.counterValue = 0;			//todo refactor
	sysTickHandler.config.autoReloadValue = TIME_BASE_OF_ONE_MS_FOR_SYSTICK * 2000;		//1ms times 2000 = 2s
	sysTickHandler.config.counterInitialize = ENABLE;
	SystickCounterHandling(&sysTickHandler);

	while( ! isSystickFlagSet(&sysTickHandler))
		if(GPIO_IsPinPressed(&semiHandler_t)){
			sysTickHandler.config.counterInitialize = DISABLE;
			SystickCounterHandling(&sysTickHandler);
			StartUserProgrammingProcedure();
			//TODO restart MCU
		}

	sysTickHandler.config.counterInitialize = DISABLE;
	SystickCounterHandling(&sysTickHandler);

	beepForTimes = 4;		//TODO: to przeniesc jako element struktury do timera
	intervalOfBeeps = 300;
	durationOfBeep = 200;
	BeepMotorHandling(beepForTimes, intervalOfBeeps, durationOfBeep);

	TIMER3_DeInit(&motorBeeping);

	motorHandler_t.PinConfig.PinMode = GPIO_MODE_OUTPUT;
	motorHandler_t.PinConfig.alternateFunMode = DISABLE;
	GPIOInit(&motorHandler_t);

	GPIOIrqExtiInit(GPIO_EXTI_FallingTrigSR, &triggerHandler_t);	//TODO: to zreobic jako event, wtedy nie
	//mam calej obslugi przerwania = wszystko dzieje sie szybciej

	PWRLowPowerHandling();

	/*
	 * Now shooting is possible
	 */

	while(1);
}


void Setup(){
	memset(&motorHandler_t, CLEAR, sizeof(motorHandler_t));
	memset(&motorBeeping, CLEAR, sizeof(motorBeeping));
	memset(&autoHandler_t, CLEAR, sizeof(autoHandler_t));
	memset(&sysTickHandler, CLEAR, sizeof sysTickHandler);

	motorHandler_t.pGPIOx = GPIOA_p;
	motorHandler_t.PinConfig.PinNumber = GPIO_PIN_NUMBER_7;
	motorHandler_t.PinConfig.PinMode = GPIO_MODE_AF;
	motorHandler_t.PinConfig.alternateFunMode = GPIO_ALTERNATE_FUN_MODE_AF1;
	motorHandler_t.PinConfig.PUPD = GPIO_PUPDR_NOPUPD;

	semiHandler_t.pGPIOx = GPIOA_p;
	semiHandler_t.PinConfig.PinNumber = GPIO_PIN_NUMBER_1;
	semiHandler_t.PinConfig.PinMode = GPIO_MODE_INPUT;
	semiHandler_t.PinConfig.PUPD = GPIO_PUPDR_PULLDOWN;

	autoHandler_t.pGPIOx = GPIOA_p;
	autoHandler_t.PinConfig.PinNumber = GPIO_PIN_NUMBER_4;
	autoHandler_t.PinConfig.PinMode = GPIO_MODE_INPUT;
	autoHandler_t.PinConfig.PUPD = GPIO_PUPDR_PULLDOWN;

	triggerHandler_t.pGPIOx = GPIOA_p;
	triggerHandler_t.PinConfig.PinNumber = GPIO_PIN_NUMBER_6;
	triggerHandler_t.PinConfig.PinMode = GPIO_MODE_INPUT;
	triggerHandler_t.PinConfig.PUPD = GPIO_PUPDR_PULLDOWN;

	gearSensorHandler_t.pGPIOx = GPIOA_p;
	gearSensorHandler_t.PinConfig.PinNumber = GPIO_PIN_NUMBER_0;
	gearSensorHandler_t.PinConfig.PinMode = GPIO_MODE_INPUT;
	gearSensorHandler_t.PinConfig.PUPD = GPIO_PUPDR_NOPUPD;

	testLEDHandler.pGPIOx = GPIOA_p;
	testLEDHandler.PinConfig.PinNumber = GPIO_PIN_NUMBER_5;
	testLEDHandler.PinConfig.PinMode = GPIO_MODE_OUTPUT;
	testLEDHandler.PinConfig.PUPD = GPIO_PUPDR_NOPUPD;

	sysTickHandler.pSysTick = SYSTICK_p;
	sysTickHandler.config.clockSource = SYSTICK_CSR_CLKSOURCE_PROC_CLK;
	sysTickHandler.config.exceptionRequestEnable = DISABLE;
	sysTickHandler.config.counterInitialize = DISABLE;


	RCCSetAPBClockPrescaler(RCC_CFGR_PRESCALER_APB_div8);
	RCCSetAHBClockPrescaler(RCC_CFGR_PRESCALER_AHB_div16);


	motorBeeping.pTIMER3 = TIMER3_p;
	motorBeeping.TIMER3Config.PWMConfig.frequencyInHz = MOTOR_PWM_FREQUENCY_IN_HZ;
	motorBeeping.TIMER3Config.PWMConfig.dutyCycleInPercent = MOTOR_PWM_DUTY_CYCLE_IN_PERCENT;
	motorBeeping.TIMER3Config.PWMConfig.channel = TIMER_PWM_CONFIG_CHANNEL_2;
	motorBeeping.TIMER3Config.PWMConfig.PWMMode = TIMER_PWM_CONFIG_MODE_PWM1;
	motorBeeping.TIMER3Config.PWMConfig.ActivePolarity = TIMER_PWM_CONFIG_ACTIVE_POLARITY_HIGH;
	motorBeeping.TIMER3Config.PWMConfig.enablePWMMode = ENABLE;
	motorBeeping.TIMER3Config.counterInitialize = DISABLE;


	GPIOInit(&motorHandler_t);
	GPIOInit(&semiHandler_t);
	GPIOInit(&autoHandler_t);
	GPIOInit(&triggerHandler_t);
	GPIOInit(&testLEDHandler);


	NVICInitVector(NVIC_IRQNUMBER_TIMER3);
	TIMER3_Init(&motorBeeping);

	//TODO configure WFE (wake up core) 11.2.3 in RM0360
}


void BeepMotorHandling(uint8_t numberOfCycles, uint32_t intervalInMs, uint32_t durationOfSingleBeep){
	//TODO: Dziala, ale trzeba napisac ladniej
	sysTickHandler.config.counterInitialize = DISABLE;
	SystickCounterHandling(&sysTickHandler);
	sysTickHandler.config.autoReloadValue = TIME_BASE_OF_ONE_MS_FOR_SYSTICK * (intervalInMs+durationOfSingleBeep);
	sysTickHandler.config.counterValue = 0;
	SysTickInit(&sysTickHandler);
	sysTickHandler.config.counterInitialize = ENABLE;
	SystickCounterHandling(&sysTickHandler);

	for(uint16_t i = 0; i < numberOfCycles ; ++i){
		motorBeeping.TIMER3Config.counterInitialize = ENABLE;
		TIMER3CounterHandling(&motorBeeping);

		while( ( sysTickHandler.config.autoReloadValue - (TIME_BASE_OF_ONE_MS_FOR_SYSTICK * durationOfSingleBeep) ) <= sysTickHandler.pSysTick->CVR );

		motorBeeping.TIMER3Config.counterInitialize = DISABLE;
		TIMER3CounterHandling(&motorBeeping);

		while( ! isSystickFlagSet(&sysTickHandler) );
	}
	sysTickHandler.config.counterInitialize = DISABLE;
	SystickCounterHandling(&sysTickHandler);
}

void EXTI4_15_IRQHandler(){	//TODO: to bedzie obslugiwane z wkup
	GPIOPendingRegisterHandling(&triggerHandler_t);
	GPIOToggleOutputPin(&motorHandler_t);
}
