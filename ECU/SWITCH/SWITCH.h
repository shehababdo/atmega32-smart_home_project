/*
 * SWITCH.h
 *
 *  Created on: Nov 17, 2021
 *      Author: user
 */

#ifndef ECU_SWITCH_SWITCH_H_
#define ECU_SWITCH_SWITCH_H_


#include "../../Common/DataType.h"
#include "../../MCAL/DIO/DIO.h"

typedef enum{
	SWITCH_0,
	SWITCH_1,
	SWITCH_2,
}SWITCH_NUMBER_en;

void SWITCH_Init(SWITCH_NUMBER_en sw);
uint8 SWITCH_Read(SWITCH_NUMBER_en sw);


#endif /* ECU_SWITCH_SWITCH_H_ */
