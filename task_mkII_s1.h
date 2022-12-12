/*
 * task_mkII_s1.h
 *
 *  Created on: Oct 14, 2020
 *      Author: Joe Krachey
 */

#ifndef TASK_MKII_S1_H_
#define TASK_MKII_S1_H_

#include "msp.h"
#include <stdint.h>
#include <stdio.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include "main.h"
extern bool red;
extern bool blue;
extern bool green;


extern TaskHandle_t Task_mkII_s1_Handle;

void task_mkII_s1(void *pvParameters);

#endif /* TASK_MKII_S1_H_ */
