/*
 * STM32F030C8T6.h
 *
 *  Created on: 16.08.2019
 *      Author: Pawel
 */

#ifndef INC_STM32F030C8T6_H_
#define INC_STM32F030C8T6_H_

#include <stdint.h>

/******************************************************************************************
 ********************** Generic macros ****************************************************
 ******************************************************************************************/

#define ENABLE							1
#define DISABLE							0
#define CLEAR							DISABLE
#define SET								ENABLE
#define F_CPU							16000000
#define TIME_BASE_OF_ONE_MS_FOR_SYSTICK (uint32_t)(F_CPU/32000)

/******************************************************************************************
 ********************** Register definition structures ************************************
 ******************************************************************************************/

typedef struct{
	volatile uint32_t CFGR1;
	volatile uint32_t reserved;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t CFGR2;
}SYSCFG_RegDef_t;

typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;
	volatile uint32_t CFGR3;
	volatile uint32_t CR2;
}RCC_RegDef_t;

typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
	volatile uint32_t BRR;
}GPIO_RegDef_t;

typedef struct{
	volatile uint32_t CR;
	volatile uint32_t CSR;
}PWR_RegDef_t;

typedef struct{
	volatile uint32_t CSR;
	volatile uint32_t RVR;
	volatile uint32_t CVR;
	volatile uint32_t CALIB;
}SYSTICK_RegDef_t;

typedef struct{
	volatile uint32_t ISER;
	uint32_t reserved1[32];
	volatile uint32_t ICER;
	uint32_t reserved2[32];
	volatile uint32_t ISPR;
	uint32_t reserved3[32];
	volatile uint32_t ICPR;
	uint32_t reserved4[96];
	volatile uint32_t IPR[8];
}NVIC_RegDef_t;

typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_RegDef_t;

typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	uint32_t reserved1;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	uint32_t reserved2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
}TIMER3_RegDef_t;

typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RCR;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t BDTR;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
}TIMER1_RegDef_t;

typedef struct{
	volatile uint32_t CR1;
	uint32_t reserved1[2];
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	uint32_t reserved2[3];
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
}TIMER6_7_RegDef_t;

typedef struct{
	volatile uint32_t CPUID;
	volatile uint32_t ICSR;
	uint32_t reserved[1];
	volatile uint32_t AIRCR;
	volatile uint32_t SCR;
	volatile uint32_t CCR;
	uint32_t reserved2[1];
	volatile uint32_t SHPR2;
	volatile uint32_t SHPR3;
}SystemControlBlock_RegDef_t;


typedef struct{
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t AR;
	uint32_t reserved[1];
	volatile uint32_t OBR;
	volatile uint32_t WRPR;
}Flash_RegDef_t;

/******************************************************************************************
 ********************** RegDef pointers to peripherals ************************************
 ******************************************************************************************/

#define TIMER1_p				((TIMER1_RegDef_t *)TIMER1_BASE_ADDR)
#define TIMER3_p				((TIMER3_RegDef_t *)TIMER3_BASE_ADDR)
#define TIMER6_p				((TIMER6_7_RegDef_t *)TIMER6_BASE_ADDR)
#define TIMER7_p				((TIMER6_7_RegDef_t *)TIMER7_BASE_ADDR)


#define GPIOA_p					((GPIO_RegDef_t*)GPIOA_BASE_ADDR)
#define GPIOB_p					((GPIO_RegDef_t*)GPIOB_BASE_ADDR)
#define GPIOC_p					((GPIO_RegDef_t*)GPIOC_BASE_ADDR)
#define GPIOD_p					((GPIO_RegDef_t*)GPIOD_BASE_ADDR)
#define GPIOF_p					((GPIO_RegDef_t*)GPIOF_BASE_ADDR)


#define SYSCFG_p				((SYSCFG_RegDef_t*)SYSCFG_BASE_ADDR)


#define RCC_p					((RCC_RegDef_t*)RCC_BASE_ADDR)


#define NVIC_p					((NVIC_RegDef_t*)NVIC_BASE_ADDR)


#define SYSTICK_p				((SYSTICK_RegDef_t*)SYSTICK_BASEADDR)


#define EXTI_p					((EXTI_RegDef_t*)EXTI_BASE_ADDR)

#define SCB_p					((SCB_RegDef_t*)SCB_BASE_ADDR)

#define PWR_p					((PWR_RegDef_t*)PWR_BASE_ADDR)
/******************************************************************************************
 ********************** Base addresses defines ********************************************
 ******************************************************************************************/

#define APB_BASE_ADDR			0x40000000
#define AHB1_BASE_ADDR			0x40020000
#define AHB2_BASE_ADDR			0x48000000
#define SRAM_BASE_ADDR			0x20000000
#define FLASH_BASE_ADDR			0x08000000
#define SYSTICK_BASEADDR		0xE000E010
#define NVIC_BASE_ADDR			0xE000E100
#define SCB_BASE_ADDR			0xE000ED00


#define RCC_BASE_ADDR			(AHB1_BASE_ADDR + 0x1000)


#define GPIOA_BASE_ADDR			(AHB2_BASE_ADDR)
#define GPIOB_BASE_ADDR			(AHB2_BASE_ADDR + 0x400)
#define GPIOC_BASE_ADDR			(AHB2_BASE_ADDR + 0x800)
#define GPIOD_BASE_ADDR			(AHB2_BASE_ADDR + 0xC00)
//there is no GPIO E port in this MCU
#define GPIOF_BASE_ADDR			(AHB2_BASE_ADDR + 0x1400)


#define SYSCFG_BASE_ADDR		(APB_BASE_ADDR + 0x10000)


#define EXTI_BASE_ADDR			(APB_BASE_ADDR + 0x10400)


#define TIMER1_BASE_ADDR		(APB_BASE_ADDR + 0x12C00)
#define TIMER3_BASE_ADDR		(APB_BASE_ADDR + 0x400)
#define TIMER6_BASE_ADDR		(APB_BASE_ADDR + 0x1000)
#define TIMER7_BASE_ADDR		(APB_BASE_ADDR + 0x1400)


#define PWR_BASE_ADDR			(APB_BASE_ADDR + 0x7000)

#endif /* INC_STM32F030C8T6_H_ */
