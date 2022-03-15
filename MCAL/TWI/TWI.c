/*
* I2C.c
*
*  Created on: Dec 23, 2021
*      Author: sheba
*/

#include "TWI.h"
#define F_CPU 16000000
#include <util/delay.h>



void TWI_MASTER_INIT(void)
{
	TWBR = 0x0C;
	set_bit(TWCR,TWEN);
}
/*
void TWI_SLAVE_INIT(void)
{
	TWAR = (1<<1)|0x01;
	set_bit(TWCR,TWEN);
}*/
void TWI_START_CONDITION(void)
{

	TWCR =(1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
	while((TWSR&0xF8) != TW_START);
 	_delay_ms(100);

}
void TWI_REPEATED_START(void)
{
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
	while((TWSR&0xF8) != TW_REP_START);
 	_delay_ms(100);
	
}
void TWI_SEND_SLAVE_ADDRESS_WRITE(uint8 address)
{
		TWDR = (address << 1);  // SETTING FIRST BIT ZERO FOR WRITING 
		TWCR = (1 << TWEN) | (1 << TWINT);
		while((TWSR&0xF8) != TW_MT_SLA_W_ACK);
 		_delay_ms(100);
		
}
void TWI_SEND_SLAVE_ADDRESS_READ(uint8 address)
{
		TWDR = ((address << 1) | 1); // SETTING FIRST BIT ZERO FOR WRITING
		TWCR = (1 << TWEN) | (1 << TWINT);
		while((TWSR&0xF8) != TW_MT_SLA_R_ACK);
 		_delay_ms(100);
		 
}
void TWI_SEND_DATA(uint8 data)
{
		TWDR = data;
		TWCR = (1 << TWEN) | (1 << TWINT);
		while((TWSR&0xF8) != TW_MT_DATA_ACK);
 		_delay_ms(100);	
}
uint8 TWI_READ_DATA(void)
{
		TWCR = (1 << 2) | (1 << 7);
		while((TWSR&0xF8) != TW_MR_DATA_NACK);
		 /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
		 while (get_bit(TWCR, TWINT) == 0U);
		 _delay_ms(100);
		return TWDR;
}
void TWI_SendMultiData(uint8* Data, uint8 Data_Size)
{
	uint8 i = 0;
	for (i = 0; i < Data_Size; i++)
	{
		TWI_SEND_DATA(Data[i]);
	}
}

uint8 TWI_ReadMultiData(void)
{
	TWCR = (1<<TWEN)|(1<<TWEA)|(1<<TWINT);
	while (!(TWCR & (1<<TWINT))); //Polling on interrupt flag until the flag is raised up
	return TWDR;
}

void TWI_STOP_CONDITION(void)
{
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}