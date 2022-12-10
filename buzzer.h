/*
 * buzzer.h
 *
 *  Created on: Dec 10, 2022
 *      Author: Ryan Almizyed
 */

#ifndef BUZZER_H_
#define BUZZER_H_

/* USER SETTINGS */
#define PWM_FREQ    3000



/* PUBLIC BUZZER FUNCTIONS */

/******************************************************
 * Sets the PWM freq of the Buzzer. The duty cycle
 * will be set to 50%
 *
 * Parameters
 *      pwm_freq    :   Frequency to buzz
 * Returns
 *      None
 ******************************************************/
void ece353_MKII_Buzzer_Init(uint16_t pwm_freq);


/******************************************************
 * Sets the PWM freq of the Buzzer.
 *
 * Parameters
 *      pwm_freq    :   Frequency to buzz
 * Returns
 *      None
 ******************************************************/
void ece353_MKII_Buzzer_Set_Freq(uint16_t pwm_freq);


/******************************************************
 * Turns the Buzzer on
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************/
void ece353_MKII_Buzzer_On(void);


/******************************************************
 * Turns the Buzzer off
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************/
void ece353_MKII_Buzzer_Off(void);


/******************************************************
 * Check Buzzer Run Status
 *
 * Parameters
 *      None
 * Returns
 *      true    :   TimerA0 is On
 *      false   :   TimerA0 is Off
 ******************************************************/
bool ece353_MKII_Buzzer_Run_Status(void);

#endif /* BUZZER_H_ */
