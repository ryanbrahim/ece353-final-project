/*
 * interrupts.h
 *
 *  Created on: Dec 2, 2022
 *      Author: aheto
 */
#include "msp.h"
#include <stdint.h>
#include <stdbool.h>

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

extern volatile uint32_t X_ACCEL;
extern volatile uint32_t Y_ACCEL;
extern volatile uint32_t Z_ACCEL;
void T32_INT1_IRQHandler(void);

void ADC14_IRQHandler(void);


#endif /* INTERRUPTS_H_ */
