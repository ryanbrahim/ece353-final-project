

/*
 *  ======== main_freertos.c ========
 */
#include "main.h"

SemaphoreHandle_t Sem_UART;

/*
 *  ======== main ========
 */
int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    ece353_staff_init(true);

    printf("\n\r");
    printf("*********************************************\n\r");
    printf("* ICE-15-Queues\n\r");
    printf("*********************************************\n\r");
    printf("\n\r");

    Sem_UART =  xSemaphoreCreateBinary();

    /*
     *  Initialize Queue_LED so that it is of size 2, and each entry
     *  is a LED_MSG_t.
     */
    Queue_LED = xQueueCreate(2, sizeof(LED_MSG_t));

    // Release print semaphore.
    xSemaphoreGive(Sem_UART);

    xTaskCreate
    (   task_mkII_s1,
        "task_mkII_s1",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );

    xTaskCreate
     (   task_mkII_s2,
         "task_mkII_s2",
         configMINIMAL_STACK_SIZE,
         NULL,
         1,
         NULL
     );

    xTaskCreate
    (   Task_LED,
        "Task_LED",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
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
