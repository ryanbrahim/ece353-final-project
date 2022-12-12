#include "msp.h"
#include <stdint.h>
#include <stdbool.h>
#ifndef __ECE353_H__
#define __ECE353_H__
//#include "interrupts.h"

//****************************************************
//****************************************************
// 02-Ex-Code-Organization
//****************************************************
//****************************************************

//Initialize hardware resources used to control S1
void ece353_MKII_S1_Init(void);

//Initialize hardware resources used to control S2
void ece353_MKII_S2_Init(void);

/*****************************************************
 * returns if mkil.s1 is correctly pressed
 *
 * Parameters
 *  on: if true,  button1 is pressed
 *      if false, button1 is not pressed
 *****************************************************/
bool ece353_MKII_S1(void);

/*****************************************************
 * returns if mkil.s2 is correctly pressed
 *
 * Parameters
 *  on: if true,  button2 is pressed
 *      if false, button2 is not pressed
 *****************************************************/
bool ece353_MKII_S2(void);

/*****************************************************
 * Sets the pwm of the Buzzer. Duty cycle will be 50%
 *
 * Parameters
 *  ticks_period: Period of pwm pulse
 *****************************************************/
void ece353_MKII_Buzzer_Init(uint16_t ticks_period);

/*****************************************************
 *turns buzzer on
 *****************************************************/
void ece353_MKII_Buzzer_On(void);

/*****************************************************
 *turns buzzer off
 *****************************************************/
void ece353_MKII_Buzzer_Off(void);

/*****************************************************
 *Check buzzer run status
 *Parameters
 *       None
 * Returns
 *      True if timerA0 is On.
 *      False if timerA0 is Off.
 *****************************************************/
bool ece353_MKII_Buzzer_Run_Status(void);

void ece353_T32_1_wait(uint32_t ticks);

/* ***************************************************
 * Initialize hardware resources used to control LED1
 *****************************************************/
void ece353_led1_init(void);

/*****************************************************
 * Initialize hardware resources used to control Button1
 *****************************************************/
void ece353_button1_init(void);

/*****************************************************
 * Turn LED1 ON/Off.
 *
 * Parameters
 *  on: if true,  turn LED on
 *      if false, turn LED off
 *****************************************************/
void ece353_led1(bool on);

/*****************************************************
 * Returns if Button1 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true    :   Button1 is pressed
 *      false   :   Button1 is NOT pressed
 *****************************************************/
bool ece353_button1(void);



//****************************************************
//****************************************************
// 02-ICE-Code-Organization
//****************************************************
//****************************************************

/*****************************************************
 * Initialize hardware resources used to control RGBLED
 *****************************************************/
void ece353_rgb_init(void);

/*****************************************************
 * Turn RGBLED ON/Off.
 *
 * Parameters
 *  red_on      :   if true,  turn RGBLED.RED on
 *                  if false, turn RGBLED.RED off
 *  green_on    :   if true,  turn RGBLED.GREEN on
 *                  if false, turn RGBLED.GREEN off
 *  blue_on     :   if true,  turn RGBLED.BLUE on
 *                  if false, turn RGBLED.BLUE off
 *****************************************************/
void ece353_rgb(bool red_on, bool green_on, bool blue_on);

/*****************************************************
 * Initialize hardware resources used to control Button2
 *****************************************************/
void ece353_button2_init(void);

/*****************************************************
 * Returns if Button2 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true    :   Button2 is pressed
 *      false   :   Button2 is NOT pressed
 *****************************************************/
bool ece353_button2(void);

#endif

//*****************************************************************************
//*****************************************************************************
// ICE 03 - Timer32_1 Push Button Detection
//*****************************************************************************
//*****************************************************************************

/*****************************************************
 * Busy waits for 100mS and then returns.
 *
 * Timer32_1 MUST be configured as a 16-bit timer.
 * Assume that the MCU clock runs at 3MHz.  You will
 * need to use a pre-scalar in order to achieve a delay
 * of 100mS.
 *
 * Parameters:
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_T32_1_wait_100mS(void);


/*****************************************************
 * Debounces Button1 using Timer32_1.
 * This function does not return until Button 1 has
 * been pressed for a minimum of 5 seconds.
 *
 * Waiting 5 Seconds will require you to call
 * ece353_T32_1_wait_100mS multiple times.
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_button1_wait_for_press(void);




//*****************************************************************************
//*****************************************************************************
// ICE 04 - PWMing MKII tri-color LED.
//*****************************************************************************
//*****************************************************************************

/*****************************************************
 * Initialize the 3 GPIO pins that control the RGB
 * LED on the MKII.
 *
 * Parameters
 *      en_primary_function  - If set to true, enable the primary function
 *                             
 * Returns
 *      None
 *****************************************************/
void ece353_MKII_RGB_IO_Init(bool en_primary_function);

/*****************************************************
 * Sets the PWM levels for the MKII RGBLED
 *
 * Parameters
 *      ticks_period    :   Period of PWM Pulse
 *      ticks_red_on    :   Number of Ticks RED is on
 *      ticks_green_on  :   Number of Ticks GREEN is on
 *      ticks_blue_on   :   Number of Ticks BLUE is on
 * Returns
 *      None
 *****************************************************/
void ece353_MKII_RGB_PWM(
        uint16_t ticks_period,
        uint16_t ticks_red_on,
        uint16_t ticks_green_on,
        uint16_t ticks_blue_on
);


//*****************************************************************************
//*****************************************************************************
// ICE 06 - ADC14
//*****************************************************************************
/******************************************************************************
 * Configure the IO pins for BOTH the X and Y directions of the analog
 * joystick.  The X direction should be configured to place the results in
 * MEM[0].  The Y direction should be configured to place the results in MEM[1].
 *
 * After BOTH analog signals have finished being converted, a SINGLE interrupt
 * should be generated.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void ece353_ADC14_PS2_XY(void);

extern volatile uint32_t PS2_X_DIR;
extern volatile uint32_t PS2_Y_DIR;
    // Configure the X direction as an analog input pin.
    // Configure the Y direction as an analog input pin.
    // Configure CTL0 to sample 16-times in pulsed sample mode.
    // NEW -- Indicate that this is a sequence-of-channels.
    // Configure ADC to return 12-bit values
    // Associate the X direction analog signal with MEM[0]
    // Associate the Y direction analog signal with MEM[1]
    // NEW -- Make sure to indicate this is the end of a sequence.
    // Enable interrupts in the ADC AFTER a value is written into MEM[1].
//
// NEW: This is not the same as what is demonstrated in the example
// coding video.
    // Enable ADC Interrupt in the NVIC
    // Turn ADC ON


/*****************************************************
 * Turn RGB on the MKII LED ON/Off.
 *
 * Parameters
 *  red:    if true,  turn RED LED on
 *          if false, turn RED LED off
 *  green:  if true,  turn GREEN LED on
 *          if false, turn GREEN LED off
 *  blue:   if true,  turn BLUE LED on
 *          if false, turn BLUE LED off
 *****************************************************/
void ece353_MKII_RGB_LED(bool red, bool green, bool blue);

void ece353_T32_1_Interrupt_Ms(uint16_t ms);


void ece353_ADC14_PS2_X_COMP(void);
