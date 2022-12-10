/*
 * main.h
 *
 *  Created on: Oct 19, 2020
 *      Author: Joe Krachey
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>
#include <stdio.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <task_led.h>
#include <task_mkII_s1.h>
#include <task_mkII_s2.h>
#include "ece353_staff.h"
#include "buzzer.h"

extern SemaphoreHandle_t Sem_UART;


#endif /* MAIN_H_ */
