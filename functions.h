/*
 * functions.h
 *
 *  Created on: Dec 2, 2022
 *      Author: aheto
 */
#include "msp.h"
#include <stdint.h>
#include <stdbool.h>
#include "main.h"


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void adc14_clock();
void accel_init();
void drawSloath(uint16_t x, uint16_t y,int active, int inactive);
void set_speed(uint16_t speed);


#endif /* FUNCTIONS_H_ */
