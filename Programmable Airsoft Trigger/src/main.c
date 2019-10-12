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

void BeepMotorHandling(uint8_t numberOfCycles, uint32_t intervalInMs, uint32_t durationOfSingleBeep);

void PASGM_TurnOffMCU();

GPIO_Handle_t autoHandler_t,
semiHandler_t,
triggerHandler_t,
gearSensorHandler_t,
motorHandler_t;

TIMER3_Handler_t motorBeeping;

SysTick_Handler_t sysTickHandler;

int main(void){
	if(! isFlagSet(PWR_CSR_SBF)){	//check if device wakes up from standby mode
		Setup();
		if( GPIO_IsPinPressed(&semiHandler_t) || GPIO_IsPinPressed(&autoHandler_t) || GPIO_IsPinPressed(&triggerHandler_t)){
			PASGM_TurnOffMCU();
		}
	}else{
		//TODO make it SetupAfterWakeup
		GPIOInit(&motorHandler_t);
		GPIOInit(&semiHandler_t);
		GPIOInit(&autoHandler_t);
		GPIOInit(&triggerHandler_t);

		RCCSetAPBClockPrescaler(RCC_CFGR_PRESCALER_APB_div8);
		RCCSetAHBClockPrescaler(RCC_CFGR_PRESCALER_AHB_div16);
	}


	NVICInitVector(NVIC_IRQNUMBER_TIMER3);
	TIMER3_Init(&motorBeeping);

	//TODO code underneath should be handled by a structure
	uint16_t beepForTimes = 2;
	uint16_t intervalOfBeeps = 400;
	uint16_t durationOfBeep = 200;
	BeepMotorHandling(beepForTimes, intervalOfBeeps, durationOfBeep);

	Systick_EnableTimerForSetTimeInMs(&sysTickHandler,2000, DISABLE);

	while( ! isSysTickFlagSet(&sysTickHandler))
		if(GPIO_IsPinPressed(&semiHandler_t)){
			sysTickHandler.config.counterInitialize = DISABLE;
			SysTickCounterHandling(&sysTickHandler);

			StartUserProgrammingProcedure();

			PASGM_TurnOffMCU();
		}

	sysTickHandler.config.counterInitialize = DISABLE;
	SysTickCounterHandling(&sysTickHandler);

	beepForTimes = 4;
	intervalOfBeeps = 300;
	durationOfBeep = 200;
	BeepMotorHandling(beepForTimes, intervalOfBeeps, durationOfBeep);

	TIMER3_DeInit(&motorBeeping);

	motorHandler_t.PinConfig.PinMode = GPIO_MODE_OUTPUT;
	motorHandler_t.PinConfig.alternateFunMode = DISABLE;
	motorHandler_t.PinConfig.PUPD = GPIO_PUPDR_PULLDOWN;
	GPIOInit(&motorHandler_t);

	GPIOIrqExtiInit(GPIO_EXTI_FallingTrigSR, &triggerHandler_t);	//TODO: that should be handled as event,
	//as no interrupt handling is done by compiler, thus procedure is done faster
	PWRLowPowerHandling();

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
	autoHandler_t.PinConfig.PinNumber = GPIO_PIN_NUMBER_4;
	autoHandler_t.PinConfig.PinMode = GPIO_MODE_INPUT;
	autoHandler_t.PinConfig.PUPD = GPIO_PUPDR_PULLUP;

	triggerHandler_t.pGPIOx = GPIOA_p;
	triggerHandler_t.PinConfig.PinNumber = GPIO_PIN_NUMBER_6;
	triggerHandler_t.PinConfig.PinMode = GPIO_MODE_INPUT;
	triggerHandler_t.PinConfig.PUPD = GPIO_PUPDR_PULLDOWN;

	gearSensorHandler_t.pGPIOx = GPIOA_p;
	gearSensorHandler_t.PinConfig.PinNumber = GPIO_PIN_NUMBER_0;
	gearSensorHandler_t.PinConfig.PinMode = GPIO_MODE_INPUT;
	gearSensorHandler_t.PinConfig.PUPD = GPIO_PUPDR_PULLUP;

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
}


void BeepMotorHandling(uint8_t numberOfCycles, uint32_t intervalInMs, uint32_t durationOfSingleBeep){
	sysTickHandler.config.counterInitialize = DISABLE;
	SysTickCounterHandling(&sysTickHandler);

	sysTickHandler.config.autoReloadValue = TIME_BASE_OF_ONE_MS_FOR_SYSTICK * (intervalInMs+durationOfSingleBeep);
	sysTickHandler.config.counterValue = 0;
	SysTickInit(&sysTickHandler);

	sysTickHandler.config.counterInitialize = ENABLE;
	SysTickCounterHandling(&sysTickHandler);

	for(uint16_t i = 0; i < numberOfCycles ; ++i){
		motorBeeping.TIMER3Config.counterInitialize = ENABLE;
		TIMER3CounterHandling(&motorBeeping);

		while( (sysTickHandler.config.autoReloadValue - (TIME_BASE_OF_ONE_MS_FOR_SYSTICK * durationOfSingleBeep) ) <= SysTickReadCurrentCounterValue(&sysTickHandler) );

		motorBeeping.TIMER3Config.counterInitialize = DISABLE;
		TIMER3CounterHandling(&motorBeeping);

		while( ! isSysTickFlagSet(&sysTickHandler) );
	}
	sysTickHandler.config.counterInitialize = DISABLE;
	SysTickCounterHandling(&sysTickHandler);
}

void EXTI4_15_IRQHandler(){	//TODO: this will be handled by wkup1
	GPIOPendingRegisterHandling(&triggerHandler_t);
	GPIOToggleOutputPin(&motorHandler_t);
}

void PASGM_TurnOffMCU(){
	GPIODeInit(&semiHandler_t);
	GPIODeInit(&autoHandler_t);
	GPIODeInit(&triggerHandler_t);
	GPIODeInit(&motorHandler_t);
	//TODO reset system with systemControlBlock registers
}
