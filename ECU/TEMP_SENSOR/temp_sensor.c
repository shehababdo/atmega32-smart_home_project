/*
 * temp_sensor.c
 *
 * Created: 3/14/2022 11:45:35 PM
 *  Author: sheha
 */ 
#include "temp_sensor.h"
void temp_sensor(void)
{
	uint8 TempC =100*(0.39/1023)*adc_read(ADC_PIN_1);
	/* TURNING ON DC MOTOR */
	if (TempC>=28)
	{
		LCD_Clear();
		LCD_WriteString("TEMP=");
		LCD_WriteINTEGER(TempC);
		LCD_WriteChar('C');
		LCD_WriteAtPosition(2,1);
		LCD_WriteString("DC ON");
		//DC_ON();
		DIO_SetLow(PORT_C,PIN_5);
		DIO_SetHigh(PORT_C,PIN_6);
		_delay_ms(1000);
		LCD_Clear();
	}
	/* TURNING OFF DC MOTOR */
	else if (TempC<=21)
	{
		LCD_Clear();
		LCD_WriteString("TEMP=");
		LCD_WriteINTEGER(TempC);
		LCD_WriteChar('C');
		LCD_WriteAtPosition(2,1);
		LCD_WriteString("DC OFF");
		//DC_OFF();
		DIO_SetLow(PORT_C,PIN_5);
		DIO_SetLow(PORT_C,PIN_6);
		_delay_ms(1000);
		LCD_Clear();
	}
	else
	{
		LCD_Clear();
		LCD_WriteString("TEMP=");
		LCD_WriteINTEGER(TempC);
		LCD_WriteChar('C');
		_delay_ms(1000);
		LCD_Clear();
	}
}