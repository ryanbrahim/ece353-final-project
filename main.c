

/*
 *  ======== main_freertos.c ========
 */
#include "main.h"

char STUDENT1_NAME[]="Almizyed, Ryan";
char STUDENT2_NAME[]="Akhetova, Sofya";

SemaphoreHandle_t Sem_UART;

/******************************************************************************
 * Used to print team info
 *****************************************************************************/
void final_proj_print_team_info(void)
{
    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf("\x1b[2J\x1b[;H");
    printf("************************************\n\r");
    printf("* ECE353 Fall 2022\n\r");
    printf("* %s\n\r",STUDENT1_NAME);
    printf("* %s\n\r",STUDENT2_NAME);
    printf("* ");
    printf(__DATE__);
    printf(", ");
    printf(__TIME__);
    printf("\n\r");
    printf("* Final Project                     \n\r");
    printf("************************************\n\r");
}

/*
 *  ======== main ========
 */
int main(void)
{
    /*
     * Initialization
     */
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    ece353_staff_init(true);

    final_proj_print_team_info();

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
