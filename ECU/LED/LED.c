/*
 * LED.c
 *
 *  Created on: Nov 17, 2021
 *      Author: user
 */
#include "LED.h"

void LED_Init(LED_NUMBER_en led)
{
	switch(led)
	{
		case LED_0 :
		{
			DIO_SetDir(PORT_C,PIN_2,OUTPUT);
			break;
		}

		case LED_1 :
		{
			DIO_SetDir(PORT_C,PIN_7,OUTPUT);
			break;
		}

		case LED_2 :
		{
			DIO_SetDir(PORT_D,PIN_3,OUTPUT);
			break;
		}

		default:
			break;

	}


}
void LED_ON(LED_NUMBER_en led)
{
	switch(led)
	{
		case LED_0 :
		{
			DIO_SetHigh(PORT_C,PIN_2);
			break;
		}

		case LED_1 :
		{
			DIO_SetHigh(PORT_C,PIN_7);
			break;
		}

		case LED_2 :
		{
			DIO_SetHigh(PORT_D,PIN_3);
			break;
		}

		default:
			break;

	}
}
void LED_OFF(LED_NUMBER_en led)
{
	switch(led)
	{
		case LED_0 :
		{
			DIO_SetLow(PORT_C,PIN_2);
			break;
		}

		case LED_1 :
		{
			DIO_SetLow(PORT_C,PIN_7);
			break;
		}

		case LED_2 :
		{
			DIO_SetLow(PORT_D,PIN_3);
			break;
		}

		default:
			break;

	}
}

void LED_TOG(LED_NUMBER_en led)
{
	switch(led)
	{
		case LED_0 :
		{
		 DIO_TOGGLE(PORT_C,PIN_2);
			break;
		}

		case LED_1 :
		{
			DIO_TOGGLE(PORT_C,PIN_7);
			break;
		}

		case LED_2 :
		{
			DIO_TOGGLE(PORT_D,PIN_3);
			break;
		}

		default:
		break;

	}
}
