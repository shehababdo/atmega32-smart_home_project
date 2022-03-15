/*
 * SWITCH.c
 *
 *  Created on: Nov 17, 2021
 *      Author: user
 */

#include "SWITCH.h"

void SWITCH_Init(SWITCH_NUMBER_en sw)
{
	switch(sw)
	{
		case SWITCH_0 :
		{
			DIO_SetDir(PORT_B,PIN_0,INPUT);
			break;
		}

		case SWITCH_1 :
		{
			DIO_SetDir(PORT_D,PIN_6,INPUT);
			break;
		}

		case SWITCH_2 :
		{
			DIO_SetDir(PORT_D,PIN_2,INPUT);
			break;
		}

		default:
			break;

	}
}
uint8 SWITCH_Read(SWITCH_NUMBER_en sw)
{
	uint8 retValue =0;

	switch(sw)
	{
		case SWITCH_0 :
		{
			retValue = DIO_GetValue(PORT_B,PIN_0);
			break;
		}

		case SWITCH_1 :
		{
			retValue = DIO_GetValue(PORT_D,PIN_6);
			break;
		}

		case SWITCH_2 :
		{
			retValue = DIO_GetValue(PORT_D,PIN_2);
			break;
		}

		default:
			break;

	}

	return retValue;
}
