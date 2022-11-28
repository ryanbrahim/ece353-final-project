/*
 * task_print2.c
 *
 *  Created on: Oct 19, 2020
 *      Author: Joe Krachey
 */

#include <task2.h>

/******************************************************************************
* Prints a message to the Console
******************************************************************************/
void Task2(void *pvParameters)
{
    BaseType_t status;
    uint32_t button_num = 0;
    while(1)
    {
        // wait for task 1 to send a message
        status = xQueueReceive(Queue_Task2, &button_num, portMAX_DELAY);

        // if button_num == 1, turn on red LED on MKII
        if(button_num == 1)
        {
            ece353_staff_MKII_RGB_LED(true, false, false);
        }

        // if button_num == 2, turn on green LED on MKII
        else if (button_num == 2)
        {
            ece353_staff_MKII_RGB_LED(false, true, false);
        }

        // respond to task 1
        printf("Task1 <-- Task2: Ok\n\r");
        button_num = 0;
        status = xQueueSend(Queue_Task1, &button_num, portMAX_DELAY);
        if(status != pdPASS)
        {
            printf("\n\r ** ERROR sending to Queue_Task1 **\n\r");
            while(1){};
        }
    }
}



