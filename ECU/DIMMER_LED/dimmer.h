/*
 * dimmer.h
 *
 * Created: 3/15/2022 12:00:35 PM
 *  Author: sheha
 */ 


#ifndef DIMMER_H_
#define DIMMER_H_
#include "../../MCAL/TIMER/TIMER.h"
#include "../../COMMON/CPU_CONFIG.h"


void init_dimmer(void);
void dimmer_brithness(uint8 adc_val);
#endif /* DIMMER_H_ */