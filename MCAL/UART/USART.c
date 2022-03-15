

#include <avr/interrupt.h>  // define interrupt for avr
#include "USART.h"

ptrFunction UART_RX_INT_ISR = NULL;
ptrFunction UART_TX_INT_ISR = NULL;

uint8 rx = 0;


void SET_UART_RX_INT_ISR_Handler( ptrFunction handler)
{ 
	if(handler != NULL)
	{
		UART_RX_INT_ISR = handler;
	}
}

void SET_UART_TX_INT_ISR_Handler( ptrFunction handler)
{
	if(handler != NULL)
	{
		UART_TX_INT_ISR = handler;
	}
}

#define BAUD 19200                                   // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR

void UART_INIT(void)
{
	/*Set pin Directions*/
	/*pin_0 input*/
	clr_bit(DDRD, 0);
	/*pin_1 output*/
	set_bit(DDRD, 1);
	
	SREG = 1 << 7;
	
	/* Transmitter/ Receiver Enable */
	UCSRB = (1 << 3) | (1 << 4);
	/*Parity Bit Selection*/
	/*Data Size Selection 8-bit*/
	/*Stop Bit Selection*/
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	
	/*Baud Rate Selection*/
    UBRRH = (BAUDRATE>>8);                      // shift the register right by 8 bits
    UBRRL = BAUDRATE;                           // set baud rate
	
	
}


void UART_Tx(sint8 chr)
{
	while(!( UCSRA & (1<<UDRE)));
	UDR = chr;
}

void UART_Tx_String(char str[])
{
	int i = 0;
	while (str[i] != '\0')
	{
		UART_Tx(str[i]);
		//_delay_ms(150);
		i++;
	}
}
void UART_Rx_String(sint8 str[],uint8 size)
{
	uint8 i = 0;
	for (i=0 ; i<size-1 ; i++)
	{
	  while(!((UCSRA) & (1<<RXC)));	
	  str[i]=UDR;
	  _delay_ms(15);
	}
	
}
sint8 UART_Rx(void)
{
	uint8 received_data = 0;
	while(!((UCSRA) & (1<<RXC)));
	received_data = UDR;
	//UDR=0;
	return received_data;
}

// ISR(USART_RXC_vect)
// {
// 	rx = UDR ;
// 	if(UART_RX_INT_ISR != NULL)
// 	{
// 		UART_RX_INT_ISR();
// 	}
// }

ISR(USART_TXC_vect)
{
	if(UART_TX_INT_ISR != NULL)
	{
		UART_TX_INT_ISR();
	}
}