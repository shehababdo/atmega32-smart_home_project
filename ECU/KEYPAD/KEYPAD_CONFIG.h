

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_
/*Macros*/

#include "../../Common/DataType.h"
#include "../../MCAL/DIO/DIO.h"

/*Keypad port needed*/
#define KEYPAD_PORT          PORT_C
/*Keypad output pins*/
#define KEYPAD_OUT_PIN0      PIN_0
#define KEYPAD_OUT_PIN1      PIN_1
#define KEYPAD_OUT_PIN2      PIN_2
#define KEYPAD_OUT_PIN3      PIN_3
/*Keypad input pins*/
#define KEYPAD_INP_PIN0      PIN_4
#define KEYPAD_INP_PIN1      PIN_5
#define KEYPAD_INP_PIN2      PIN_6
#define KEYPAD_INP_PIN3      PIN_7
/*Keypad state*/
#define KEYPAD_INPUT         INPUT
#define KEYPAD_OUTPUT        OUTPUT

/*Start and end of columns pins*/
#define COL_INIT             0
#define COL_FINAL            3
/*Start and end of rows pins*/
#define ROW_INIT             4
#define ROW_FINAL            7
#endif /* KEYPAD_CONFIG_H_ */
