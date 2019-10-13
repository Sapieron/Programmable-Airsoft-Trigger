/*
 * STM32F030C8T6_flash.h
 *
 *  Created on: Oct 13, 2019
 *      Author: pawel
 */

#ifndef INC_STM32F030C8T6_FLASH_H_
#define INC_STM32F030C8T6_FLASH_H_

/******************************************************************************************
 ********************************* Typedef structures *************************************
 ******************************************************************************************/

typedef struct{
	//TODO write flash config
}Flash_Config_t;


typedef struct{
	Flash_Config_t config;
	Flash_RegDef_t *pFlash;
}Flash_Handle_t;


/******************************************************************************************
 ********************************* Main functions *****************************************
 ******************************************************************************************/



/******************************************************************************************
 ********************************* FLASH Specific defines **********************************
 ******************************************************************************************/

#define FLASH_ACR_LATENCY		0
#define FLASH_ACR_PRFTBE		4
#define FLASH_ACR_PRFTBS		5

#define FLASH_KEYR_FKEY			0

#define FLASH_OPTKEYR_OPTKEY	0

#define FLASH_SR_BSY			0
#define FLASH_SR_PGERR			2
#define FLASH_SR_WRPRTERR		4
#define FLASH_SR_EOP			5

#define FLASH_CR_PG				0
#define FLASH_CR_PER			1
#define FLASH_CR_MER			2
#define FLASH_CR_OPTPG			4
#define FLASH_CR_OPTER			5
#define FLASH_CR_STRT			6
#define FLASH_CR_LOCK			7
#define FLASH_CR_OPTWRE			9
#define FLASH_CR_ERRIE			10
#define FLASH_CR_EOPIE			12
#define FLASH_CR_OBL_LAUNCH		13


#endif /* INC_STM32F030C8T6_FLASH_H_ */
