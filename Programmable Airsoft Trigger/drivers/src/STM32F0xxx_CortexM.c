/*
 * STM32F0xxx_CortexM.c
 *
 *  Created on: Oct 11, 2019
 *      Author: pawel
 */

#include <STM32F030C8T6.h>
#include <STM32F030C8T6_pwr.h>
#include <STM32F0xxx_CortexM.h>

/*
WFI (Wait for Interrupt) or WFE (Wait for Event) while:
– Set SLEEPDEEP in ARM ® Cortex ® -M0 System Control register
– Set PDDS bit in Power Control register (PWR_CR)
– Clear WUF bit in Power Control/Status register (PWR_CSR)
*/

void PWR_WKUPxHandling(uint8_t pwrCsrEwup, uint8_t enOrDis){
	PWR_p->CSR |= (ENABLE << pwrCsrEwup);
}

void PWRInitPowerSavingMode(SystemBlockContol_Handle_t *pSCB){
	if (pSCB->config.pwrSavingMode == PWR_STANDBY_MODE){
		pSCB->pSCBx->SCR |= (ENABLE << SCB_SCR_SLEEPDEEP);
		PWR_p->CR |= (ENABLE << PWR_CR_PDDS);
		PWR_ClearSCRWUFPendingRegister();
	}
}

void PWR_ClearSCRWUFPendingRegister(){
	PWR_p->CR |= (ENABLE << PWR_CR_CWUF);
}
