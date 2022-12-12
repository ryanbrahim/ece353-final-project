/*
 * task_console.h
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */

#ifndef TASK_CONSOLE_H_
#define TASK_CONSOLE_H_

#include <main.h>

extern QueueHandle_t Queue_Console;
extern TaskHandle_t Task_Console_Handle;
extern int x_pos;
extern int y_pos;
extern int sloth_image;
extern int mood;
extern uint16_t pwm_freq;

/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_Console(void *pvParameters);




#endif /* TASK_CONSOLE_H_ */
