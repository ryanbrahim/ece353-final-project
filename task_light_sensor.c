/*
 * task_light.c
 *
 *  Created on: Dec 14, 2022
 *      Author: aheto
 */

#include "task_light_sensor.h"



/******************************************************************************
 * FreeRTOS task to monitor light level
 ******************************************************************************/
TaskHandle_t task_light_monitor_handle;
void task_light_monitor(void *pvParameters)
{
    while (1)
    {
        // Get a new light sensor reading
        uint16_t light_level = opt3001_read_light();

        // Check light limits
        ALERT_LIGHT_LOW = (light_level <= OPT3001_LOW_LIM_LUX) ? true : false;
        ALERT_LIGHT_HIGH = (light_level >= OPT3001_HIGH_LIM_LUX) ? true : false;

       // printf("In light sensor task ");
       // if (ALERT_LIGHT_LOW) { printf("LOW LIGHT"); }
       // if (ALERT_LIGHT_HIGH) { printf("HIGH LIGHT"); }
      //  printf("\r\n");

        // Go to sleep in FreeRTOS before starting again
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
