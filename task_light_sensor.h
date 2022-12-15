/*
 * task_light_sensor.h
 *
 *  Created on: Dec 14, 2022
 *      Author: aheto
 */
#include "main.h"
#ifndef TASK_LIGHT_SENSOR_H_
#define TASK_LIGHT_SENSOR_H_

/******************************************************************************
 * FreeRTOS task to monitor light level
 ******************************************************************************/
TaskHandle_t task_light_monitor_handle;
void task_light_monitor(void *pvParameters);



#endif /* TASK_LIGHT_SENSOR_H_ */
