/*
 * EEPROM.c
 *
 * Created: 2/24/2022 2:08:12 PM
 *  Author: sheha
 */ 

#include "../../MCAL/TWI/TWI.h"
#include "EEPROM.h"
// #define ERROR     0
// #define SUCCSSED  1
#include <avr/io.h>
#include <avr/interrupt.h>  // define interrupt for avr
#include <util/delay.h>



void eeprom_init()
{
	TWI_MASTER_INIT();
}


void eeprom_write_byte(uint8 Device_Page,uint8 byte_address,sint8 data)
{
	if (Device_Page > 7)
	Device_Page = 7;
	//Device address calculation
	uint8 Device_Add = 0X50 | Device_Page;
	TWI_START_CONDITION();
	//sending slave address with write operation
	TWI_SEND_SLAVE_ADDRESS_WRITE(Device_Add);
	//sending data byte address
	TWI_SEND_DATA(byte_address);
	//sending the data byte
	TWI_SEND_DATA(data);
	//Sending stop condition
	TWI_STOP_CONDITION();
	_delay_ms(100);
}

uint8 eeprom_read_byte(uint8 Device_Page,uint8 byte_address)
{
	uint8 data = 0;
	if (Device_Page > 7)
	Device_Page = 7;
	//Device address calculation
	uint8 Device_Add = 0X50 | Device_Page;
	TWI_START_CONDITION();
	//sending slave address with write operation
	TWI_SEND_SLAVE_ADDRESS_WRITE(Device_Add);
	TWI_SEND_DATA(byte_address);             // WITH RESPECT TO I2C ITS A DATA BUT FOR EEPROM ITS THE ADDRESS
	//Sending repeated start condition
	TWI_REPEATED_START();
	//sending slave address with read operation
	TWI_SEND_SLAVE_ADDRESS_READ(Device_Add);
	data = TWI_READ_DATA();  // READING DATA WITH NO ACK
	TWI_STOP_CONDITION();
	return data;
}



void EEPROM_WriteString(uint8 Device_Page ,uint8 data_add ,uint8* Data,  uint8 lenght )
{
	Device_Page &= 0b0111;
	//Device address calculation
	uint8 Device_Add = 0X50 | Device_Page;
	
	TWI_START_CONDITION();
	TWI_SEND_SLAVE_ADDRESS_WRITE(Device_Add);
	// send the required location address
	TWI_SEND_DATA(data_add);  // WITH RESPECT TO I2C ITS A DATA BUT FOR EEPROM ITS THE ADDRESS
	//sending the data byte
	TWI_SendMultiData(Data, lenght);
	
	TWI_STOP_CONDITION();
	_delay_ms(100);
}

void EEPROM_ReadString(uint8 Device_Page, uint8 Data_Add, uint8* data, uint8 Data_Size)
{
	uint8 i;
	Device_Page &= 0b0111;
	//Device address calculation
	uint8 Device_Add = 0X50 | Device_Page;
	
	TWI_START_CONDITION();

	TWI_SEND_SLAVE_ADDRESS_WRITE(Device_Add);
	
	// send the required location address
	TWI_SEND_DATA(Data_Add);;   // WITH RESPECT TO I2C ITS A DATA BUT FOR EEPROM ITS THE ADDRESS
	
	
	// send a repeated start
	TWI_REPEATED_START();

	TWI_SEND_SLAVE_ADDRESS_READ(Device_Add);
	
	// read the data byte by byte
	for (i = 0; i < Data_Size; i++)
	{
		data[i] = TWI_ReadMultiData();
	
	}

	TWI_STOP_CONDITION();
	_delay_ms(100);	
}