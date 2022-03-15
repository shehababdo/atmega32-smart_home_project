/*
 * Atmega32_Registers.h
 *
 * Created: 8/7/2021 12:01:47 AM
 *  Author: Bahaa
 */ 


#ifndef ATMEGA32_REGISTERS_H_
#define ATMEGA32_REGISTERS_H_

/************************************** DIO-Registers *******************************************/
#define  PINC    (*(volatile char*)0x33 )
#define  DDRC    (*(volatile char*)0x34 )
#define  PORTC   (*(volatile char*)0x35 )

#define  PINB    (*(volatile char*)0x36 )
#define  DDRB    (*(volatile char*)0x37 )
#define  PORTB   (*(volatile char*)0x38 )

#define  PIND    (*(volatile char*)0x30 )
#define  DDRD    (*(volatile char*)0x31 )
#define  PORTD   (*(volatile char*)0x32 )

#define  PINA    (*(volatile char*)0x39 )
#define  DDRA    (*(volatile char*)0x3A )
#define  PORTA   (*(volatile char*)0x3B )

/************************************** INTERRUPT-Registers *******************************************/

#define SREG    (*(volatile char*) (0x5F))
#define GICR    (*(volatile char*) (0x5B))
#define GIFR    (*(volatile char*) (0x5A))
#define MCUCR   (*(volatile char*) (0x55))
#define MCUCSR  (*(volatile char*) (0x54))



#endif /* ATMEGA32_REGISTERS_H_ */
