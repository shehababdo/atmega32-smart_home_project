/*
* SEV_SEG_CONFIG.h
*
* Created: 1/15/2021 7:33:50 PM
*  Author: Bahaa
*/


#ifndef SEV_SEG_CONFIG_H_
#define SEV_SEG_CONFIG_H_

#include "../../MCAL/DIO/DIO.h"


/*Renaming for ports*/
#define SEVSEG_CMD_PORT     PORT_B
#define SEVSEG_DTA_PORT     PORT_A
/*Renaming for pins*/
#define SEVSEG_EN1          PIN_1
#define SEVSEG_EN2          PIN_2
#define SEVSEG_DIP          PIN_3

#define SEVSEG_DTA0_A       PIN_4
#define SEVSEG_DTA1_B       PIN_5
#define SEVSEG_DTA2_C       PIN_6
#define SEVSEG_DTA3_D       PIN_7

#define SEVSEG_OUTPUT       OUTPUT


#endif /* SEV_SEG_CONFIG_H_ */
