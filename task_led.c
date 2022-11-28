/*
 * task_led.c
 *
 *  Created on: Oct 19, 2020
 *      Author: Joe Krachey
 */

#include <main.h>

 QueueHandle_t Queue_LED;

/******************************************************************************
* Controls the RGB LED on the MSP432 Launchpad
******************************************************************************/
static void update_rgb_led(LED_COLOR color)
{
    switch(color)
    {
        case LED_RED:
            {
                ece353_staff_RGB_LED(true, false, false);
                break;
            }
        case LED_GREEN:
            {
                ece353_staff_RGB_LED(false, true, false);
                break;
            }
        case LED_BLUE:
            {
                ece353_staff_RGB_LED(false, false, true);
                break;
            }
        default:
        {
            break;
        }
    }

}

/******************************************************************************
* Controls the RGB LED on the MKII
******************************************************************************/
static void update_mkII_rgb_led(LED_COLOR color)
{
    switch(color)
    {
        case LED_RED:
            {
                ece353_staff_MKII_RGB_LED(true, false, false);
                break;
            }
        case LED_GREEN:
            {
                ece353_staff_MKII_RGB_LED(false, true, false);
                break;
            }
        case LED_BLUE:
            {
                ece353_staff_MKII_RGB_LED(false, false, true);
                break;
            }
        default:
        {
            break;
        }
    }

}

/******************************************************************************
* Controls the RGB LED on the MSP432 Launchpad
******************************************************************************/
void Task_LED(void *pvParameters)
{
    LED_MSG_t msg;

    while(1)
    {
        /*
         * Wait until we receive a message from the Queue_LED
         */
        xQueueReceive(Queue_LED, &msg, portMAX_DELAY);

        /*
        * take Sem_UART semaphore
        */
        xSemaphoreTake(Sem_UART, portMAX_DELAY);

        printf("Task_LED updating LED\n\r");

        /*
         * give Sem_UART semaphore
         */
        xSemaphoreGive(Sem_UART);

        /*
         * Turn on the specified LED based on the message
         * received from Queue_LED.
         *
         * The color of the LED is also specified
         * in the message received from Queue_LED.
         *
         * There are two helper functions provided above to
         * make this process easier.
         */
        if (msg.led_location == MKIIEDU)
            update_mkII_rgb_led(msg.color);
        else
            update_rgb_led(msg.color);

    }

}



