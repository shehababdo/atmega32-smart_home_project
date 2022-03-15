/*
 * LED.h
 *
 *  Created on: Nov 17, 2021
 *      Author: user
 */

#ifndef ECU_LED_LED_H_
#define ECU_LED_LED_H_

//#include "../../Common/CPU_CONFIG.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../COMMON/BitMath.h"

typedef enum{
	LED_0,
	LED_1,
	LED_2,
}LED_NUMBER_en;

void LED_Init(LED_NUMBER_en led);
void LED_ON(LED_NUMBER_en led);
void LED_OFF(LED_NUMBER_en led);
void LED_TOG(LED_NUMBER_en led);

#endif /* ECU_LED_LED_H_ */
