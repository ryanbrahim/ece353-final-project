/*
 * interrupts.c
 *
 *  Created on: Dec 2, 2022
 *      Author: aheto
 */

#include "interrupts.h"
//#include "ece353.h"
#include "msp.h"

volatile uint32_t X_ACCEL = 4092/2;
volatile uint32_t Y_ACCEL = 4092/2;
volatile uint32_t Z_ACCEL = 4092/2;

void T32_INT1_IRQHandler(void)
{
    // Start the ADC conversion
    ADC14->CTL0 |= ADC14_CTL0_SC|ADC14_CTL0_ENC;
    // Clear the timer interrupt
    TIMER32_1->INTCLR = BIT0; //WRITE ANY NUMBER WILL CLEAR IT

}

void ADC14_IRQHandler(void)
{
    // Read the X channel
X_ACCEL = ADC14->MEM[0];//changing the value of the global variable of x
Y_ACCEL = ADC14->MEM[1];//changing the value of the global variable of y
Z_ACCEL = ADC14->MEM[2];//changing the value of the global variable of z
}


