/*
 * task_print1.h
 *
 *  Created on: Oct 19, 2020
 *      Author: Joe Krachey
 */

#ifndef TASK_LED_H_
#define TASK_LED_H_

#include "main.h"

typedef enum {LED_RED, LED_GREEN, LED_BLUE} LED_COLOR;
typedef enum {MSP432, MKIIEDU} LED_LOCATION;

typedef struct {
    LED_LOCATION led_location;
    LED_COLOR color;
}LED_MSG_t;

extern QueueHandle_t Queue_LED;



/******************************************************************************
* Controls the RGB LED on the MKII
******************************************************************************/
void Task_LED(void *pvParameters);



#endif /* TASK_LED_H_ */
