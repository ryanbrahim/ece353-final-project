/*
 * interrupts.h
 *
 *  Created on: Dec 2, 2022
 *      Author: aheto
 */
#include "msp.h"
#include <main.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

extern volatile uint32_t X_ACCEL;
extern volatile uint32_t Y_ACCEL;
extern volatile uint32_t Z_ACCEL;

extern TaskHandle_t Task_Accel_Handle;
extern TaskHandle_t Task_Accel_Bottom_Half_Handle;


void T32_INT1_IRQHandler(void);

void ADC14_IRQHandler(void);

/******************************************************************************
* Examines the ADC data from the joystick on the MKII
******************************************************************************/
void Task_Accel_Bottom_Half(void *pvParameters);

typedef enum {
    ACCEL_CENTER,
    ACCEL_LEFT,
    ACCEL_RIGHT,
    ACCEL_UP,
    ACCEL_DOWN,
} ACCEL_t;
#endif /* INTERRUPTS_H_ */
