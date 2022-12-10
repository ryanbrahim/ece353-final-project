

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

    // test buzzer

    // Configure TimerA0
    static uint16_t pwm_freq = PWM_FREQ;
    ece353_MKII_Buzzer_Init(pwm_freq);


    while(1)
    {
        if(ece353_staff_MKII_S1())    // If SW1 is being pressed, turn the buzzer on
        {
            // Only turn the buzzer on if its current status is off
            if(!ece353_MKII_Buzzer_Run_Status())
            {
                pwm_freq = (pwm_freq < 200) ? PWM_FREQ : pwm_freq - 100;
                ece353_MKII_Buzzer_Set_Freq(pwm_freq);
                ece353_MKII_Buzzer_On();
            }

        }
        else    // SW1 is not pressed, so turn the buzzer off
            ece353_MKII_Buzzer_Off();
    }



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
