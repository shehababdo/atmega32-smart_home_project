/*
 * UART_CFG.h
 *
 * Created: 6/25/2021 1:29:32 PM
 *  Author: ahmed
 */ 


#ifndef UART_CFG_H_
#define UART_CFG_H_

#define F_CPU 16000000

/*Parity Mode Selection*/
#define PARITY_MODE         EVEN_PARITY

/*Stop Bit Selection*/
#define STOP_BIT            _1_BIT

/*Data Size Selection*/
#define DATA_SIZE           _8_BIT

/*Baud Rate Selection*/
#define BAUD_RATE           B_38400





#endif /* UART_CFG_H_ */