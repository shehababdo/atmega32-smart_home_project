/*
 * dimmer.c
 *
 * Created: 3/15/2022 12:00:48 PM
 *  Author: sheha
 */ 
#include "dimmer.h"

void init_dimmer(void)
{
	DDRD |= (1<<7);  // OC2 OUTPUT
	TIMER_Paramter_t timerUsed_2;
	timerUsed_2.Timer_Channel = TIMER2;
	timerUsed_2.Timer_Mode = FAST_PWM;
	timerUsed_2.COM_Pin = NON_INVERTED;
	timerUsed_2.Timer_Prescale = PRESCALING_CLK1024;
	timerUsed_2.Timer_OCR_Interrupt = OCR_disable;
	timerUsed_2.Timer_OVF_Interrupt = TOVF_disable;
	TIMER_Init(timerUsed_2);
}

void dimmer_brithness(uint8 adc_val)
{
	TIMER_Set_OCR_Value(TIMER2,adc_val);
}