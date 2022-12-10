/*
 * task_console.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */
#include <main.h>

QueueHandle_t Queue_Console;
TaskHandle_t Task_Console_Handle;
int x_pos = 64;
int y_pos = 64;
int xmax = 130;
int ymax = 130;
int inc =2;


int sloth_image =2;//start at okay
int mood = 5;//init mood
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
        uint8_t width;
        uint8_t height;
        const uint8_t *bitmap;
        switch (sloth_image){
            case 0:{//dead
                width = deadSlothsmallmonoWidthPixels;
                height = deadSlothsmallmonoHeightPixels;
                bitmap = deadSlothsmallmonoBitmaps;
                break;
            }
            case 1:{//sad
                width = sadSloth_monoWidthPixels;
                height = sadSloth_monoHeightPixels;
                bitmap = sadSloth_monoBitmaps;
                break;
             }
            case 2:{//okay
                width = okSloth_monoWidthPixels;
                height = okSloth_monoHeightPixels;
                bitmap = okSloth_monoBitmaps;
                break;
            }
            case 3:{//happy
                width = happySloth_small_monoWidthPixels;
                height = happySloth_small_monoHeightPixels;
                bitmap = happySloth_small_monoBitmaps;
                break;
            }

        }





        switch (dir)
        {
            case ACCEL_DOWN:
            {
                printf( "Task_Console: Accel position - DOWN\n\r");
                if((y_pos+inc)<(ymax-height/2)){
                    drawSloath(x_pos,y_pos,width, height, bitmap, LCD_COLOR_BLACK,LCD_COLOR_BLACK);
                    y_pos+=inc;
                    drawSloath(x_pos,y_pos,width, height, bitmap, LCD_COLOR_RED, LCD_COLOR_BLACK);
                }
                break;
            }
            case ACCEL_UP:
            {
                printf( "Task_Console: Accel position - UP\n\r");
                if((y_pos-inc)>(height/2)){
                    drawSloath(x_pos,y_pos, width, height, bitmap,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
                    y_pos-=inc;
                    drawSloath(x_pos,y_pos,width, height, bitmap, LCD_COLOR_RED, LCD_COLOR_BLACK);
               }
                break;
            }
            case ACCEL_RIGHT:
            {
                printf( "Task_Console: Accel position - RIGHT\n\r");
                if((x_pos+inc)<(xmax-width/2)){
                    drawSloath(x_pos,y_pos, width, height, bitmap,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
                    x_pos+=inc;
                    drawSloath(x_pos,y_pos,width, height, bitmap, LCD_COLOR_RED, LCD_COLOR_BLACK);
                }
                break;
            }
            case ACCEL_LEFT:
            {
                printf( "Task_Console: Accel position - LEFT\n\r");
                if((x_pos-inc)>(width/2)){
                    drawSloath(x_pos,y_pos,width, height, bitmap,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
                    x_pos-=inc;
                    drawSloath(x_pos,y_pos, width, height, bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
                }
                break;
            }
            case ACCEL_CENTER:
            {
                //printf( "Task_Console: Accel position - CENTER\n\r");
                drawSloath(x_pos,y_pos, width, height, bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
                break;
            }
        }

    }
}


