/*
 * SEV_SEG.h
 *
 * Created: 1/15/2021 7:34:00 PM
 *  Author: Bahaa
 */ 


#ifndef SEV_SEG_H_
#define SEV_SEG_H_


#include "SEV_SEG_CONFIG.h"
#include "../../Common/DataType.h"


void SEVSEG_Init(void);/*Initialization function of the module to define pin direction*/
void SEV_SEG_DISPLAY(uint8 data);/*Display value from (0 -> 99)*/

void SEVSEG_ENB1(void);/*Enable first seven segment*/
void SEVSEG_DIS1(void);/*Disable first seven segment*/
void SEVSEG_ENB2(void);/*Enable second seven segment*/
void SEVSEG_DIS2(void);/*Disable second seven segment*/
void SEVSEG_DIP_EN(void);/*Enable Decimal point*/
void SEVSEG_DIP_DS(void);/*Disable Decimal point*/

#endif /* SEV_SEG_H_ */
