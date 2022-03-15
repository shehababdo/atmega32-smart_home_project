


#include "EXT_INT.h"
#include "../../Common/BitMath.h"
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define INT0    6
#define INT1    7
#define INT2    5 


ptrFunction EXT_INT0_ISR = NULL, EXT_INT1_ISR = NULL, EXT_INT2_ISR = NULL;
	
void SET_EXT_INT0_ISR_Handler( ptrFunction handler)
{
	if(handler != NULL)
	{
		EXT_INT0_ISR = handler;
	}
}
void SET_EXT_INT1_ISR_Handler( ptrFunction handler)
{
	if(handler != NULL)
	{
		EXT_INT1_ISR = handler;
	}
}
void SET_EXT_INT2_ISR_Handler( ptrFunction handler)
{
	if(handler != NULL)
	{
		EXT_INT2_ISR = handler;
	}
}
/*Interrupt Service Routine for INT0*/
ISR(INT0_vect)
{

	if(EXT_INT0_ISR != NULL)
	{
		EXT_INT0_ISR();
	}

}

/*Interrupt Service Routine for INT1*/
ISR(INT1_vect)
{

	if(EXT_INT1_ISR != NULL)
	{
		EXT_INT0_ISR();
	}

}


/*Interrupt Service Routine for INT2*/
ISR(INT2_vect)
{

	if(EXT_INT2_ISR != NULL)
	{
		EXT_INT2_ISR();
	}

}


void GLOBAL_INTERRUPT_Enable(void)
{

	set_bit(SREG, 7);

}

void GLOBAL_INTERRUPT_Disable(void)
{

	clr_bit(SREG, 7);

}

void EXT_INTERRUPT0_Init(void)
{
	/*Disable global interrupt*/
	GLOBAL_INTERRUPT_Disable();

	/*Enable External Interrupt 0*/
	set_bit(GICR, INT0);
	//SET_BIT(GICR, 6);

	/*How to trigger an interrupt*/
	#if EXT_INT0_TRIGGER == EXT_INT_TRG_LOW
		clr_bit(MCUCR, ISC01);
		clr_bit(MCUCR, ISC00);
	#elif EXT_INT0_TRIGGER == EXT_INT_TRG_ANY_LOGICAL
		clr_bit(MCUCR, ISC01);
		set_bit(MCUCR, ISC00);
	#elif EXT_INT0_TRIGGER == EXT_INT_TRG_FALLING_EDGE
		set_bit(MCUCR, ISC01);
		clr_bit(MCUCR, ISC00);
	#elif EXT_INT0_TRIGGER == EXT_INT_TRG_RISING_EDGE
		set_bit(MCUCR, ISC01);
		set_bit(MCUCR, ISC00);
	#endif

		/*Enable global interrupt*/
		GLOBAL_INTERRUPT_Enable();
}
void EXT_INTERRUPT1_Init(void)
{
   /*Disable global interrupt*/
   GLOBAL_INTERRUPT_Disable();

	/*Enable External Interrupt 1*/
	set_bit(GICR, INT1);
	//SET_BIT(GICR, 7);

		/*How to trigger an interrupt*/
	#if EXT_INT1_TRIGGER == EXT_INT_TRG_LOW
	clr_bit(MCUCR, ISC11);
	clr_bit(MCUCR, ISC10);
	#elif EXT_INT1_TRIGGER == EXT_INT_TRG_ANY_LOGICAL
	clr_bit(MCUCR, ISC11);
	set_bit(MCUCR, ISC10);
	#elif EXT_INT1_TRIGGER == EXT_INT_TRG_FALLING_EDGE
	set_bit(MCUCR, ISC11);
	clr_bit(MCUCR, ISC10);
	#elif EXT_INT1_TRIGGER == EXT_INT_TRG_RISING_EDGE
	set_bit(MCUCR, ISC11);
	set_bit(MCUCR, ISC10);
	#endif

    /*Enable global interrupt*/
	GLOBAL_INTERRUPT_Enable();
}
void EXT_INTERRUPT2_Init(void)
{
	/*Disable global interrupt*/
	GLOBAL_INTERRUPT_Disable();

	/*Enable External Interrupt 0*/
	set_bit(GICR, INT2);
	//SET_BIT(GICR, 5);

		/*How to trigger an interrupt*/
   #if EXT_INT2_TRIGGER == EXT_INT_TRG_FALLING_EDGE
	clr_bit(MCUCSR, ISC2);
	#elif EXT_INT2_TRIGGER == EXT_INT_TRG_RISING_EDGE
	set_bit(MCUCSR, ISC2);
	#endif

	/*Enable global interrupt*/
	GLOBAL_INTERRUPT_Enable();	
}
