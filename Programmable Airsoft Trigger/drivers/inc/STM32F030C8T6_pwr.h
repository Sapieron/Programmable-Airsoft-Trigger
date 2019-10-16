/*
 * STM32F030C8T6_pwr.h
 *
 *  Created on: 31.08.2019
 *      Author: Pawel
 */

#ifndef INC_STM32F030C8T6_PWR_H_
#define INC_STM32F030C8T6_PWR_H_

/******************************************************************************************
 * ******************************* PWR macros definitions *********************************
 ******************************************************************************************/

#define PWR_CR_LPDS			0
#define PWR_CR_PDDS			1
#define PWR_CR_CWUF			2
#define PWR_CR_CSBF			3
#define PWR_CR_DBP			8


#define PWR_CSR_WUF			0
#define PWR_CSR_SBF			1
#define PWR_CSR_EWUP1		8
#define PWR_CSR_EWUP2		9
#define PWR_CSR_EWUP4		11
#define PWR_CSR_EWUP5		12
#define PWR_CSR_EWUP6		13
#define PWR_CSR_EWUP7		14


/******************************************************************************************
 * ******************************* PWR Structures *****************************************
 ******************************************************************************************/




/******************************************************************************************
 * ******************************* Main functions *****************************************
 ******************************************************************************************/

uint8_t PWR_isFlagSet(uint8_t PWR_CSR_xxxx);

void PWR_LowPowerHandling();

void PWR_WKUPxHandling(uint8_t pwrCsrEwup, uint8_t enOrDis);

#endif /* INC_STM32F030C8T6_PWR_H_ */
