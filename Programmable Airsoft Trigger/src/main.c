/* ******************************************
    Programmable Trigger for airsoft replicas
    Copyright (c) 2019 Pawel Klisz (pawelochojec@gmail.com)
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


#define MOTOR_PWM_FREQUENCY_IN_HZ 				1000
#define MOTOR_PWM_DUTY_CYCLE_IN_PERCENT			2


void Setup();

GPIO_Handle_t autoHandler_t,
semiHandler_t,
triggerHandler_t,
gearSensorHandler_t,
motorHandler_t;

TIMER3_Handler_t motorBeeping;

SysTick_Handler_t sysTickHandler;

PASGM_BeepMotorHandler_t BeepMotorHandler;

int main(void){
	if(! PWR_isFlagSet(PWR_CSR_SBF)){	//check if device wakes up from standby mode
		Setup();
		if( GPIO_IsPinPressed(&semiHandler_t) || GPIO_IsPinPressed(&autoHandler_t) || GPIO_IsPinPressed(&triggerHandler_t)){
			GPIO_DeInit(&semiHandler_t);
			GPIO_DeInit(&autoHandler_t);
			GPIO_DeInit(&triggerHandler_t);
			GPIO_DeInit(&motorHandler_t);
			//TODO reset system with systemControlBlock registers
		}

		NVIC_InitVector(NVIC_IRQNUMBER_TIMER3);
		TIMER3_Init(&motorBeeping);

		BeepMotorHandler.beepForTimes = 2;
		BeepMotorHandler.intervalOfBeepsInMs = 200;
		BeepMotorHandler.durationOfBeepInMs = 400;
		PASGM_BeepMotorHandling(&BeepMotorHandler, &sysTickHandler, &motorBeeping);

		Systick_EnableTimerForSetTimeInMs(&sysTickHandler,2000, DISABLE);

		while( ! SysTick_isFlagSet(&sysTickHandler))
			if(GPIO_IsPinPressed(&semiHandler_t)){
				sysTickHandler.config.counterInitialize = DISABLE;
				SysTick_CounterHandling(&sysTickHandler);

				PASGM_StartUserProgrammingProcedure();

				GPIO_DeInit(&semiHandler_t);
				GPIO_DeInit(&autoHandler_t);
				GPIO_DeInit(&triggerHandler_t);
				GPIO_DeInit(&motorHandler_t);
				//TODO reset system with systemControlBlock registers
			}

		sysTickHandler.config.counterInitialize = DISABLE;
		SysTick_CounterHandling(&sysTickHandler);

		BeepMotorHandler.beepForTimes = 4;
		BeepMotorHandler.intervalOfBeepsInMs = 300;
		BeepMotorHandler.durationOfBeepInMs = 200;
		PASGM_BeepMotorHandling(&BeepMotorHandler, &sysTickHandler, &motorBeeping);

		TIMER3_DeInit(&motorBeeping);

		motorHandler_t.PinConfig.PinMode = GPIO_MODE_OUTPUT;
		motorHandler_t.PinConfig.alternateFunMode = DISABLE;
		motorHandler_t.PinConfig.PUPD = GPIO_PUPDR_PULLDOWN;
		GPIO_Init(&motorHandler_t);

		GPIO_ExtiInit(GPIO_EXTI_FallingTrigSR, &triggerHandler_t);	//TODO: that should be handled as event,
		//as no interrupt handling is done by compiler, thus procedure is done faster
		PWR_LowPowerHandling();
		PWR_WKUPxHandling(PWR_CSR_EWUP1, ENABLE);
	}else{
		//TODO make it SetupAfterWakeup
		GPIO_Init(&semiHandler_t);
		GPIO_Init(&autoHandler_t);

		RCC_SetAPBClockPrescaler(RCC_CFGR_PRESCALER_APB_div8);
		RCC_SetAHBClockPrescaler(RCC_CFGR_PRESCALER_AHB_div16);

		EXTI_InitEvent(triggerHandler_t.PinConfig.PinNumber);
		EXTI_SWIER_Handling(ENABLE,triggerHandler_t.PinConfig.PinNumber);
	}
	while(1);
}


void Setup(){
	//TODO whole setup should be saved in flash
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
	semiHandler_t.PinConfig.PUPD = GPIO_PUPDR_PULLUP;

	autoHandler_t.pGPIOx = GPIOA_p;
	autoHandler_t.PinConfig.PinNumber = GPIO_PIN_NUMBER_3;
	autoHandler_t.PinConfig.PinMode = GPIO_MODE_INPUT;
	autoHandler_t.PinConfig.PUPD = GPIO_PUPDR_PULLUP;


	//this structure is valid only till WKUP1 is initialized, then it's overwritten
	triggerHandler_t.pGPIOx = GPIOA_p;
	triggerHandler_t.PinConfig.PinNumber = GPIO_PIN_NUMBER_0;
	triggerHandler_t.PinConfig.PinMode = GPIO_MODE_INPUT;
	triggerHandler_t.PinConfig.PUPD = GPIO_PUPDR_PULLDOWN;

	gearSensorHandler_t.pGPIOx = GPIOA_p;
	gearSensorHandler_t.PinConfig.PinNumber = GPIO_PIN_NUMBER_2;
	gearSensorHandler_t.PinConfig.PinMode = GPIO_MODE_INPUT;
	gearSensorHandler_t.PinConfig.PUPD = GPIO_PUPDR_PULLUP;

	sysTickHandler.pSysTick = SYSTICK_p;
	sysTickHandler.config.clockSource = SYSTICK_CSR_CLKSOURCE_PROC_CLK;
	sysTickHandler.config.exceptionRequestEnable = DISABLE;
	sysTickHandler.config.counterInitialize = DISABLE;


	RCC_SetAPBClockPrescaler(RCC_CFGR_PRESCALER_APB_div8);
	RCC_SetAHBClockPrescaler(RCC_CFGR_PRESCALER_AHB_div16);


	motorBeeping.pTIMER3 = TIMER3_p;
	motorBeeping.TIMER3Config.PWMConfig.frequencyInHz = MOTOR_PWM_FREQUENCY_IN_HZ;
	motorBeeping.TIMER3Config.PWMConfig.dutyCycleInPercent = MOTOR_PWM_DUTY_CYCLE_IN_PERCENT;
	motorBeeping.TIMER3Config.PWMConfig.channel = TIMER_PWM_CONFIG_CHANNEL_2;
	motorBeeping.TIMER3Config.PWMConfig.PWMMode = TIMER_PWM_CONFIG_MODE_PWM1;
	motorBeeping.TIMER3Config.PWMConfig.ActivePolarity = TIMER_PWM_CONFIG_ACTIVE_POLARITY_HIGH;
	motorBeeping.TIMER3Config.PWMConfig.enablePWMMode = ENABLE;
	motorBeeping.TIMER3Config.counterInitialize = DISABLE;


	GPIO_Init(&motorHandler_t);
	GPIO_Init(&semiHandler_t);
	GPIO_Init(&autoHandler_t);
	GPIO_Init(&triggerHandler_t);
}

void EXTI0_1_IRQHandler(){
	GPIO_IrqPendingRegisterHandling(&triggerHandler_t);
	GPIO_ToggleOutputPin(&motorHandler_t);
}


