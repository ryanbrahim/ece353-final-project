/*
 * interrupts.c
 *
 *  Created on: Dec 2, 2022
 *      Author: aheto
 */

#include "interrupts.h"
//#include "ece353.h"
#include "msp.h"

 TaskHandle_t Task_Accel_Bottom_Half_Handle;
 TaskHandle_t Task_mkII_s2_Bottom_Half_Handle;
 TaskHandle_t Task_mkII_s1_Bottom_Half_Handle;
 TaskHandle_t Task_Accel_Timer_Handle;

volatile uint32_t X_ACCEL = 4092/2;
volatile uint32_t Y_ACCEL = 4092/2;
volatile uint32_t Z_ACCEL = 4092/2;




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
void Task_Accel_Bottom_Half(void *pvParameters)
{
    ACCEL_t dir;



    while(1)
    {
        /* ADD CODE
         * Wait until we get a task notification from the ADC14 ISR
         */

        ulTaskNotifyTake(pdTRUE,portMAX_DELAY);

        /*
         * Set the dir variable to one of the following values based
         * on the values of JOYSTICK_X_DIR and JOYSTIC_Y_DIR
         */
        if(X_ACCEL < 1800)
        {
           dir = ACCEL_LEFT;
        }
        else if(X_ACCEL > 2200)
        {
            dir = ACCEL_RIGHT;
        }
        else if(Y_ACCEL < 1800)
        {
            dir = ACCEL_DOWN;
        }
        else if(Y_ACCEL > 2200)
        {
            dir = ACCEL_UP;
        }
        else
        {
            dir = ACCEL_CENTER;
        }

        /* ADD CODE
         * Send dir to Queue_Console if the the current direction
         * of the joystick does not match the previous direction of the joystick
         */
        //if (dir!=ACCEL_CENTER){//don't do anything at center
            xQueueSendToBack(Queue_Console, &dir, portMAX_DELAY);
       // }
        /* ADD CODE
         * Update the prev_dir of the joystick
         */
        //prev_dir = dir;
    }
}
void ADC14_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        // Read the X channel
    X_ACCEL = ADC14->MEM[0];//changing the value of the global variable of x
    Y_ACCEL = ADC14->MEM[1];//changing the value of the global variable of y
    Z_ACCEL = ADC14->MEM[2];//changing the value of the global variable of z

    vTaskNotifyGiveFromISR(Task_Accel_Bottom_Half_Handle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}



