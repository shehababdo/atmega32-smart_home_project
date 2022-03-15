



#ifndef EXT_INT_CONFIG_H_
#define EXT_INT_CONFIG_H_

/*Macros and libraries needed*/
#include "../ATMEGA_REG/Atmega32_Registers.h"



/*Logical to fire interrupt, events*/
#define EXT_INT_TRG_LOW          0
#define EXT_INT_TRG_ANY_LOGICAL  1
#define EXT_INT_TRG_FALLING_EDGE 2
#define EXT_INT_TRG_RISING_EDGE  3


/*Interrupts states*/
#define EXT_INT0_TRIGGER          EXT_INT_TRG_LOW
#define EXT_INT1_TRIGGER          EXT_INT_TRG_FALLING_EDGE
#define EXT_INT2_TRIGGER          EXT_INT_TRG_LOW
/*End of configuration file*/
#endif /* EXT_INT_CONFIG_H_ */
