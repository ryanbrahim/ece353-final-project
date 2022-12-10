/*
 * main.h
 *
 *  Created on: Oct 20, 2020
 *      Author: Joe Krachey
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>
#include <stdio.h>
#include <stdint.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include "ece353_staff.h"
#include "functions.h"
#include "interrupts.h"
#include "image.h"
#include "lcd.h"
#include "ece353.h"
#include "task_console.h"
#include "task_mkII_s1.h"
#include "task_mkII_s2.h"
#include "buzzer.h"


/* USER SETTINGS */
#define PWM_FREQ    3000


#endif /* MAIN_H_ */
