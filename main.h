/*
 * main.h
 *
 *  Created on: Oct 20, 2020
 *      Author: Sofya Akhetova
 *      Author: Ryan Almizyed
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
#include "functions.h"
#include "image.h"
#include "lcd.h"
#include "ece353.h"
#include "task_console.h"
#include "task_mkII_s1.h"
#include "task_mkII_s2.h"
#include "buzzer.h"
#include "opt3001.h"
#include "i2c.h"
#include "task_accel_bottom_half.h"
#include "task_light_sensor.h"
#include "task_timer.h"
#include "serial_debug.h"
#include "circular_buffer.h"

extern SemaphoreHandle_t Sem_UART;

/* USER SETTINGS */
#define PWM_FREQ    3000


#endif /* MAIN_H_ */
