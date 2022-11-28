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
#include <stdbool.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <task1.h>
#include <task2.h>
#include <ece353_staff.h>


 extern QueueHandle_t Queue_Task1;
 extern QueueHandle_t Queue_Task2;


#endif /* MAIN_H_ */
