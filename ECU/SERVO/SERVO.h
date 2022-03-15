/*
 * SERVO.h
 *
 * Created: 2/27/2022 11:42:10 PM
 *  Author: sheha
 */ 


#ifndef SERVO_H_
#define SERVO_H_
#include  "../../MCAL/TIMER/TIMER.h"
#include "../../COMMON/CPU_CONFIG.h"

void servo_init(void);
void servo_90_right(void);
void servo_90_left(void);
void servo_stop(void);




#endif /* SERVO_H_ */