/*
 * task_mkII_s1.c
 *
 *  Created on: Oct 14, 2020
 *      Author: Joe Krachey
 */

#include "main.h"
#include "ece353_staff.h"
TaskHandle_t Task_mkII_s1_Handle = NULL;

/******************************************************************************
 * De-bounce switch S1.  If is has been pressed, change the tri-Color LED on
 * the MSP432 Launchpad. Everytime S1 is pressed, the color should change in
 * the following order:
 *      RED->GREEN->BLUE->RED->GREEN....
 *****************************************************************************/
void task_mkII_s1(void *pvParameters)
{
    // Declare a uint8_t variable that will be used to de-bounce S1
    uint8_t debounce_state = 0x00;
    bool red = true;
    bool green = false;
    bool blue = false;

    while(1)
    {

        // Shift the de-bounce variable to the left 
        debounce_state = debounce_state<<1;

        // If S1 is being pressed, set the LSBit of debounce_state to a 1;
        if (ece353_staff_MKII_S1()){
            debounce_state|=1;
        }
        // If the de-bounce variable is equal to 0x7F, change the color of the tri-color LED.
        if (debounce_state == 0x7F){
                    if (mood<10){
                        mood++;
                        mood_checker(mood);
                    }
                    if (red){
                        red = false;
                        green = true;
                        blue = false;
                    }
                    else if(green){
                        red = false;
                        green = false;
                        blue = true;
                    }
                    else if(blue){
                        red = true;
                        green = false;
                        blue = false;
                    }
                    ece353_staff_RGB_LED(red, green, blue);
                }
        // Delay for 10mS using vTaskDelay
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}
