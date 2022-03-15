


#ifndef EXT_INT_H_
#define EXT_INT_H_

#include "EXT_INT_CONFIG.h"

typedef void(*ptrFunction)(void);


void GLOBAL_INTERRUPT_Enable(void);
void GLOBAL_INTERRUPT_Disable(void);

void EXT_INTERRUPT0_Init(void);
void EXT_INTERRUPT1_Init(void);
void EXT_INTERRUPT2_Init(void);

void SET_EXT_INT0_ISR_Handler( ptrFunction handler);
void SET_EXT_INT1_ISR_Handler( ptrFunction handler);
void SET_EXT_INT2_ISR_Handler( ptrFunction handler);



#endif /* EXT_INT_H_ */
