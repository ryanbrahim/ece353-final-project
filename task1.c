/*
 * task_print1.c
 *
 *  Created on: Oct 19, 2020
 *      Author: Joe Krachey
 */

#include <task1.h>



/******************************************************************************
* Prints a message to the Console
******************************************************************************/
void Task1(void *pvParameters)
{
    BaseType_t status;
    uint32_t button_num = 0;
    char msg[20];

    while(1)
    {
        // Check to see if the button has been pressed every 10mS
        if(ece353_staff_MKII_S1())
        {
            // Send a message to the
            button_num = 1;
        }

        if(ece353_staff_MKII_S2())
        {
            // Send a message to the
            button_num = 2;
        }

        if(button_num != 0)
        {
            sprintf(msg,"Task1 --> Task2: Button %d\n\r", button_num);
            printf(msg);

            // send a message to task 2
            status = xQueueSend(Queue_Task2, &button_num, portMAX_DELAY);
            if(status != pdTRUE)
            {
                // should never make it here
                printf("\n\r *** Unknown error sending to Queue_Task2 ***\n\r");
                while(1){};
            }

            // wait for response from task 2 before continuing on.
            status = xQueueReceive(Queue_Task1, &button_num, portMAX_DELAY);

            if(status != pdTRUE)
            {
                printf("\n\r *** Task2 failed to respond in time ***\n\r");
                button_num = 0; // Reset button num to 0.
            }
        }
        // sleep for 100mS
        vTaskDelay(pdMS_TO_TICKS(100));


    }
}



