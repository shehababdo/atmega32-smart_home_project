 
 #include "BUZZER.h"
 #include "../../MCAL/DIO/DIO.h"
 #include "util/delay.h"
 
 
 void BUZZ_INIT(void)
 {
	 DIO_SetDir(PORT_A,PIN_3,OUTPUT);
 }
 
 
 void BUZZ_DIS(void)
 {
	 DIO_SetLow(PORT_A,PIN_3);
 }
 
 
 void BUZZ_EN(void)
 {
	 DIO_SetHigh(PORT_A,PIN_3);
 }