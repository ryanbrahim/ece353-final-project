/*
 * task_console.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */
#include <main.h>

QueueHandle_t Queue_Console;
TaskHandle_t Task_Console_Handle;

/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_Console(void *pvParameters)
{
    ACCEL_t dir;

    while(1)
    {
        /* ADD CODE
         * wait until we receive a message in Queue_Console
         */
        //waiting
        xQueueReceive(Queue_Console,&dir, portMAX_DELAY);


        /* ADD CODE
         * based on the message that was received, print out one of the following
         * message to the UART.
         *
         *  "Task_Console: Joystick position - CENTER\n\r"
         *  "Task_Console: Joystick position - LEFT\n\r"
         *  "Task_Console: Joystick position - RIGHT\n\r"
         *  "Task_Console: Joystick position - UP\n\r"
         *  "Task_Console: Joystick position - DOWN\n\r"
         *
         * NOTE, the UART is only accessed in this task, so
         * there is no need to use a semaphore for mutual exclusion of the UART.
         */
        if(dir == ACCEL_CENTER){
            printf( "Task_Console: Accel position - CENTER\n\r");
            //continue;
        }
        if(dir == ACCEL_LEFT){
             printf( "Task_Console: Accel position - LEFT\n\r");

        }
        if(dir == ACCEL_RIGHT){
             printf( "Task_Console: Accel position - RIGHT\n\r");
        }
        if(dir == ACCEL_UP){
             printf( "Task_Console: Accel position - UP\n\r");
            }
        if(dir == ACCEL_DOWN){
             printf( "Task_Console: Accel position - DOWN\n\r");
         }
    }
}


