/*
 * task_timer.c
 *
 *  Created on: Dec 14, 2022
 *      Author: aheto
 */


#include "task_timer.h"

 TaskHandle_t Task_Accel_Timer_Handle;

/******************************************************************************
* Used to start an ADC14 Conversion
******************************************************************************/
void Task_Accel_Timer(void *pvParameters)
{
    while(1)
    {
        /*
         * Start the ADC conversion
         */
        ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

        /*
         * Delay 50mS
         */
        vTaskDelay(pdMS_TO_TICKS(50));

    }
}
