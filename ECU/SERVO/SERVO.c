/*
 * SERVO.c
 *
 * Created: 2/27/2022 11:41:54 PM
 *  Author: sheha
 */ 
#include "SERVO.h"


void servo_init(void)
{
	// INITIALIZATION FOR TIMER 1 CHANNEL B
	DDRD |= (1<<5);  //set OC1A OUTPUT 
	TIMER_Set_ICR_Value(40000); // periodic time equals 20 ms 
    TIMER_Paramter_t timerUsed ;
    timerUsed.Timer_Channel = TIMER1;
    timerUsed.TMR1_Channel  = T1_A ;
    timerUsed.Timer1_Mode = FAST_PWM_ICR;
    timerUsed.COM_Pin = NON_INVERTED;
    timerUsed.Timer_OCR_Interrupt = OCR_disable;
    timerUsed.Timer_ICR_Interrupt = ICR_disable;
    timerUsed.Timer_OVF_Interrupt = TOVF_disable;
	 timerUsed.Timer_Prescale = PRESCALING_CLK8;
    TIMER_Init(timerUsed);
	
}

void servo_90_right(void)
{
	TCNT1=0; 
	TIMER_Set_OCR_Value(TIMER1_A,800);  //----------> TO get 1/2 ms high 
}

void servo_90_left(void)
{
	TCNT1=0;
	TIMER_Set_OCR_Value(TIMER1_A,2100);  //----------> TO get 1 ms high
}

void servo_stop(void)
{
	TCNT1=0;
	TIMER_Set_OCR_Value(TIMER1_A,3000);  //----------> TO get 1.5 ms high
}