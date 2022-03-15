/*
 * temp_sensor.h
 *
 * Created: 3/14/2022 11:45:17 PM
 *  Author: sheha
 */ 


#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

#include "../../MCAL/ADC/ADC.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../ECU/LCD/LCD.h"
#include <avr/interrupt.h>  // define interrupt for avr
#include <util/delay.h>     // built in delay function
#include <stdio.h>
#include "string.h"
#include "../../COMMON/BitMath.h"
#include "../../COMMON/DataType.h"

void temp_sensor(void);

#endif /* TEMP_SENSOR_H_ */