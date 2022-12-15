/*
 * functions.c
 *
 *  Created on: Dec 2, 2022
 *      Author: aheto
 */

/* global variable declaration */
#include "functions.h"

void mood_checker(int mood){
    if (mood>8){
        sloth_image = 3;//happy
        red = false;
        green = true;
        blue = false;
    }
    else if (mood>3){
        sloth_image = 2;//ok
        red = true;
        green = true;
        blue = false;
    }
    else if (mood>0){
        sloth_image = 1;//sad
        red = false;
        green = false;
        blue = true;
    }
    else{
        sloth_image = 0;//dead
        red = true;
        green = false;
        blue = false;
    }
}
//active is the on color
//inactive is the background or off color
void drawSloath(uint16_t x, uint16_t y, uint8_t width, uint8_t height, const uint8_t bitmap[],  int active, int inactive)
{
    lcd_draw_image(
                    x,
                    y,
                    width,
                    height,
                    bitmap,
                    active,
                    inactive
            );//LCD_COLOR_RED,//LCD_COLOR_BLACK
}

void adc14_clock(){
    // Configure CTL0 to sample 16-times in pulsed sample mode.
        // NEW -- Indicate that this is a sequence-of-channels.
        ADC14->CTL0 = ADC14_CTL0_SHP| ADC14_CTL0_SHT02|ADC14_CTL0_MSC|ADC14_CTL0_CONSEQ_1;

        // Configure ADC to return 12-bit values
        ADC14->CTL1 = ADC14_CTL1_RES_2;

        // Associate the X direction analog signal with MEM[0]
        ADC14->MCTL[0] = ADC14_MCTLN_INCH_14; // FOR A15 for x mem

        // Associate the Y direction analog signal with MEM[1]
        ADC14->MCTL[1] = ADC14_MCTLN_INCH_13; // FOR A13 for y mem

        // Associate the Z direction analog signal with MEM[2]
        ADC14->MCTL[2] = ADC14_MCTLN_INCH_11; // FOR A11 for z mem

        // NEW -- Make sure to indicate this is the end of a sequence.
        //ADC14->MCTL[0]|= ADC14_MCTLN_EOS;
        ADC14->MCTL[2]|= ADC14_MCTLN_EOS;

        // Enable interrupts in the ADC AFTER a value is written into MEM[1].
        ADC14->IER0 = ADC14_IER0_IE1;
    //
    // NEW: This is not the same as what is demonstrated in the example
    // coding video.
        // Enable ADC Interrupt in the NVIC
        NVIC_EnableIRQ(ADC14_IRQn);
        NVIC_SetPriority(ADC14_IRQn, 2);
        // Turn ADC ON
        ADC14->CTL0|= ADC14_CTL0_ON;
}

void accel_init(){
    //x is P6.1 is A14 is j3.23
    //y is P4.0 is A13 is j3.24
    //z is P4.2 is A11 is j3.25

    P6->DIR &= ~BIT1;//config as input for x
    P4->DIR &= ~BIT0;//config as input for y
    P4->DIR &= ~BIT2;//config as input for z

    // Configure the accel as an analog input pin.
    P6->SEL0 |=BIT1; //for x
    P6->SEL1 |=BIT1;
    P4->SEL0 |=BIT0|BIT2; //for y and z
    P4->SEL1 |=BIT0|BIT2;

    adc14_clock();
}



