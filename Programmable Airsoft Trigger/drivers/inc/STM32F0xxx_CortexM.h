/*
 * STM32F0xxx_CortexM.h
 *
 *  Created on: Oct 11, 2019
 *      Author: pawel
 *  Whole code written here was written with reference to PM0215 / 4.3
 */

#ifndef INC_STM32F0XXX_CORTEXM_H_
#define INC_STM32F0XXX_CORTEXM_H_


#include <STM32F030C8T6.h>

/******************************************************************************************
 ********************************* Typedef structures *************************************
 ******************************************************************************************/
typedef struct{
	uint32_t pwrSavingMode;
}SystemBlockControl_Config_t;


typedef struct{
	SystemControlBlock_RegDef_t *pSCB;
	SystemBlockControl_Config_t config;
}SystemBlockContol_Handle_t;

/******************************************************************************************
 ********************************* Main functions *****************************************
 ******************************************************************************************/

void PWRInitPowerSavingMode(SystemBlockContol_Handle_t *pSCB);


/******************************************************************************************
 ********************************* CORTEX-M Specific defines **********************************
 ******************************************************************************************/

#define PWR_STANDBY_MODE		0

#define SCB_CPUID_REVISION		0
#define SCB_CPUID_PARTNO		4
#define SCB_CPUID_CONSTANT		16
#define SCB_CPUID_VARIANT		20
#define SCB_CPUID_IMPLEMENTER	24


#define SCB_ICSR_VECTACTIVE		0
#define SCB_ICSR_VECTPENDING	12
#define SCB_ICSR_ISRPENDING		22
#define SCB_ICSR_PENDSTCLR		25
#define SCB_ICSR_PENDSTSET		26
#define SCB_ICSR_PENDSVCLR		27
#define SCB_ICSR_PENDSVSET		28
#define SCB_ICSR_NMIPENDSET		31


#define SCB_AIRCR_VECTCLRACTIVE	1
#define SCB_AIRCR_SYSRESETREQ	2
#define SCB_AIRCR_ENDIANESS		15
#define SCB_AIRCR_VECTKEY		16


#define SCB_SCR_SLEEPONEXIT		1
#define SCB_SCR_SLEEPDEEP		2
#define SCB_SCR_SEVEONPENDBIT	4


#define SCB_CCR_UNALIGN_TRP		3
#define SCB_CCR_STKALIGN		9


#define SCB_SHPR2_PRI_11		24


#define SCB_SHPR3_PRI_14		16
#define SCB_SHPR3_PRI_15		24

//TODO move irq/nvic library here

#endif /* INC_STM32F0XXX_CORTEXM_H_ */
