/*
 * buzzer.c
 *
 *  Created on: Dec 10, 2022
 *      Author: Ryan Almizyed
 */
#include "main.h"


/******************************************************
 * Sets the PWM freq of the Buzzer. The duty cycle
 * will be set to 50%
 *
 * Parameters
 *      pwm_freq    :   Frequency to buzz initially
 * Returns
 *      None
 ******************************************************/
void ece353_MKII_Buzzer_Init1(uint16_t pwm_freq)
{
    // Set P2.7 to be a GPIO OUTPUT pin
    P2->DIR |= BIT7;

    // the TIMERA PWM controller will control the buzzer on the MKII
    // P2.7 <--> TA0.4
    P2->SEL0 |= BIT7;
    P2->SEL1 &= ~BIT7;

    // Turn off TA0
    TIMER_A0->CTL = 0;

    // Set the period of the timer
    ece353_MKII_Buzzer_Set_Freq1(pwm_freq);

    // Configure TA0.4 for RESET_SET Mode
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;

    // Select the master clock as the timer source
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK;
}


/******************************************************
 * Sets the PWM freq of the Buzzer.
 *
 * Parameters
 *      pwm_freq    :   Frequency to buzz
 * Returns
 *      None
 ******************************************************/
void ece353_MKII_Buzzer_Set_Freq1(uint16_t pwm_freq)
{
    // Calculate ticks needed to produce freq
    uint16_t ticks_period = (uint16_t)(SystemCoreClock/pwm_freq) - 1;

    // Set the period of the timer
    TIMER_A0->CCR[0] = ticks_period -1;

    // Configure BUZZER Duty Cycle to 50%
    TIMER_A0->CCR[4] = (ticks_period/2) - 1;

}


/******************************************************
 * Turns the Buzzer on
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************/
void ece353_MKII_Buzzer_On1(void)
{
    // Clear the current Mode Control Bits
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK;

    // Set Mode Control to UP and Clear the current count
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP | TIMER_A_CTL_CLR;
}


/******************************************************
 * Turns the Buzzer off
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************/
void ece353_MKII_Buzzer_Off1(void)
{
    // Turn off the timer
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK;
}


/******************************************************
 * Check Buzzer Run Status
 *
 * Parameters
 *      None
 * Returns
 *      true    :   TimerA0 is On
 *      false   :   TimerA0 is Off
 ******************************************************/
bool ece353_MKII_Buzzer_Run_Status1(void)
{
    return (TIMER_A0->CTL & TIMER_A_CTL_MC_MASK) != TIMER_A_CTL_MC__STOP;
}
