/*
* SEV_SEG.c
*
* Created: 1/15/2021 7:34:10 PM
*  Author: Bahaa
*/
#include "SEV_SEG.h"
#include <util/delay.h>
#include "../../MCAL/ATMEGA_REG/Atmega32_Registers.h"

void SEVSEG_Init(void)/*Initialization function of the module to define pin direction*/
{
	/*Command port pins*/
	DIO_SetDir(SEVSEG_CMD_PORT, SEVSEG_EN1, SEVSEG_OUTPUT);
	DIO_SetDir(SEVSEG_CMD_PORT, SEVSEG_EN2, SEVSEG_OUTPUT);
	DIO_SetDir(SEVSEG_CMD_PORT, SEVSEG_DIP, SEVSEG_OUTPUT);
	/*Data port pins*/
	DIO_SetDir(SEVSEG_DTA_PORT, SEVSEG_DTA0_A, SEVSEG_OUTPUT);
	DIO_SetDir(SEVSEG_DTA_PORT, SEVSEG_DTA1_B, SEVSEG_OUTPUT);
	DIO_SetDir(SEVSEG_DTA_PORT, SEVSEG_DTA2_C, SEVSEG_OUTPUT);
	DIO_SetDir(SEVSEG_DTA_PORT, SEVSEG_DTA3_D, SEVSEG_OUTPUT);
}
void SEVSEG_ENB1(void)/*Enable first seven segment*/
{
	DIO_SetHigh(SEVSEG_CMD_PORT, SEVSEG_EN1);
}
void SEVSEG_DIS1(void)/*Disable first seven segment*/
{
	DIO_SetHigh(SEVSEG_CMD_PORT, SEVSEG_EN1);
}
void SEVSEG_ENB2(void)/*Enable second seven segment*/
{
	DIO_SetHigh(SEVSEG_CMD_PORT, SEVSEG_EN2);
}
void SEVSEG_DIS2(void)/*Disable second seven segment*/
{
	DIO_SetHigh(SEVSEG_CMD_PORT, SEVSEG_EN2);
}
void SEVSEG_DIP_EN(void)/*Enable Decimal point*/
{
	DIO_SetHigh(SEVSEG_CMD_PORT, SEVSEG_DIP);
}
void SEVSEG_DIP_DS(void)/*Disable Decimal point*/
{
	DIO_SetHigh(SEVSEG_CMD_PORT, SEVSEG_DIP);
}
void SEV_SEG_DISPLAY(uint8_t data)/*Display value from (0 -> 99)*/
{
	/*POV*/
	/*
	19
	10 -> tenth
	9 -> unit
	*/
	uint8 data0 = data % 10;/*First number in units*/
	uint8 data1 = data / 10;/*Second number in tenth*/

	SEVSEG_ENB1();
	SEVSEG_DIS2();
	PORTA = (data0 << 4) | (PORTA & 0x0F);
	_delay_ms(10);

	SEVSEG_DIS1();
	SEVSEG_ENB2();
	PORTA = (data1 << 4) | (PORTA & 0x0F);
	_delay_ms(10);
}
