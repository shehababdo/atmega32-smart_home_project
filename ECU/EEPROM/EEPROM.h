/*
 * EEPROM.h
 *
 * Created: 2/24/2022 2:07:56 PM
 *  Author: sheha
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#define F_CPU 16000000


void eeprom_init();
void eeprom_write_byte(uint8 Device_Page,uint8 byte_address,sint8 data);
uint8 eeprom_read_byte(uint8 Device_Page,uint8 byte_address);

void EEPROM_WriteString(uint8 Device_Page ,uint8 data_add ,uint8* Data,  uint8 lenght );
void EEPROM_ReadString(uint8 Device_Page, uint8 Data_Add, uint8* data, uint8 Data_Size);



#endif /* EEPROM_H_ */