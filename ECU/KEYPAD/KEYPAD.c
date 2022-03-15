

#include "KEYPAD.h"
#include <util/delay.h>

const uint8 KEYPAD[4][4] =
{
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'*','0','#','D'}
};


void KEYPAD_Init(void)/*Initialize keypad*/
{
	/*Define direction for output pins*/
	DIO_SetDir(KEYPAD_PORT, KEYPAD_OUT_PIN0, KEYPAD_OUTPUT);
	DIO_SetDir(KEYPAD_PORT, KEYPAD_OUT_PIN1, KEYPAD_OUTPUT);
	DIO_SetDir(KEYPAD_PORT, KEYPAD_OUT_PIN2, KEYPAD_OUTPUT);
	DIO_SetDir(KEYPAD_PORT, KEYPAD_OUT_PIN3, KEYPAD_OUTPUT);
	/*Define direction for input pins*/
	DIO_SetDir(KEYPAD_PORT, KEYPAD_INP_PIN0, KEYPAD_INPUT);
	DIO_SetDir(KEYPAD_PORT, KEYPAD_INP_PIN1, KEYPAD_INPUT);
	DIO_SetDir(KEYPAD_PORT, KEYPAD_INP_PIN2, KEYPAD_INPUT);
	DIO_SetDir(KEYPAD_PORT, KEYPAD_INP_PIN3, KEYPAD_INPUT);
	/*Activate internal pull-up resistor*/
	DIO_SetHigh(KEYPAD_PORT, KEYPAD_INP_PIN0);
	DIO_SetHigh(KEYPAD_PORT, KEYPAD_INP_PIN1);
	DIO_SetHigh(KEYPAD_PORT, KEYPAD_INP_PIN2);
	DIO_SetHigh(KEYPAD_PORT, KEYPAD_INP_PIN3);
	/*All output should be normally high*/
	DIO_SetHigh(KEYPAD_PORT, KEYPAD_OUT_PIN0);
	DIO_SetHigh(KEYPAD_PORT, KEYPAD_OUT_PIN1);
	DIO_SetHigh(KEYPAD_PORT, KEYPAD_OUT_PIN2);
	DIO_SetHigh(KEYPAD_PORT, KEYPAD_OUT_PIN3);
}
uint8 KEYPAD_READ(void)/*Read keypad value*/
{
	uint8 LOC_COL = 0; /*Counter for columns*/
	uint8 LOC_ROW = 0; /*Counter for rows*/
	uint8 read = 0;    /*To get reading from keypad*/
	uint8 val = 0;     /*To check value inside array 2D*/
	for(LOC_COL = COL_INIT; LOC_COL <= COL_FINAL; LOC_COL++)
	{
		DIO_SetLow(KEYPAD_PORT, LOC_COL);
		for (LOC_ROW = ROW_INIT; LOC_ROW <= ROW_FINAL; LOC_ROW++)
		{
			read = DIO_GetValue(KEYPAD_PORT, LOC_ROW);
			if(read == 0)/*Active LOW*/
			{
				val = KEYPAD[LOC_ROW - ROW_INIT][LOC_COL - COL_INIT];
				while (read == 0)
				{
					read = DIO_GetValue(KEYPAD_PORT, LOC_ROW);
				}
				_delay_ms(10);
			}
		}
		DIO_SetHigh(KEYPAD_PORT, LOC_COL);
	}
	return val;
}
