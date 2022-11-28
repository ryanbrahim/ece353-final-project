/*
 * Copyright (c) 2016-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== main_freertos.c ========
 */
#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>
#include <stdio.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>

TaskHandle_t Task_Blink_LED1_Handle = NULL;
TaskHandle_t Task_Blink_RGB_Blue_Handle = NULL;

#define DELAY_MS 1000

/* ****************************************************************************
 * This Function initializes the hardware required to blink LED1 on the
 * MSP432 Launchpad
 * ***************************************************************************/
void blink_led1_hw_init(void)
{
    // set direction as an output
    P1->DIR |= BIT0;

    // Turn off LED
    P1->OUT &= ~BIT0;
}

/******************************************************************************
* Tasked used to blink LED1 on MSP432 Launchpad
******************************************************************************/
void Task_Blink_LED1(void *pvParameters)
{
    while(1)
    {
        // turn on the LED
        P1->OUT |= BIT0;

        // Delay
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));

        // turn off the LED
        P1->OUT &= ~BIT0;

        // Delay
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}


/* ****************************************************************************
 * This Function initializes the hardware required to blink RGB blue on the
 * MSP432 Launchpad
 * ***************************************************************************/
void blink_rgb_blue_hw_init(void)
{
    // set direction as an output
    P2->DIR |= BIT2;

    // Turn off LED
    P2->OUT &= ~BIT2;
}

/******************************************************************************
* Tasked used to blink RGB blue on MSP432 Launchpad
******************************************************************************/
void Task_Blink_RGB_Blue(void *pvParameters)
{
    while(1)
    {
        // turn on the LED
        P2->OUT |= BIT2;

        // Delay
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));

        // turn off the LED
        P2->OUT &= ~BIT2;

        // Delay
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}


/*
 *  ======== main ========
 */
int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    blink_led1_hw_init();
    blink_rgb_blue_hw_init();

    xTaskCreate
    (   Task_Blink_LED1,
        "LED1 Blink Task",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        &Task_Blink_LED1_Handle
    );

    xTaskCreate
    (   Task_Blink_RGB_Blue,
        "RGB Blue Blink Task",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        &Task_Blink_RGB_Blue_Handle
    );


    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    while(1){};
    return (0);
}

//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while(1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while(1)
    {
    }
}
