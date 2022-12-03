/*
 * opt3001.c
 *
 *  Created on: Oct 20, 2020
 *      Author: Joe Krachey
 */

#include <opt3001.h>

/******************************************************************************
 * Initialize the opt3001 temperature sensor on the MKII.  This function assumes
 * that the I2C interface has already been configured to operate at 100KHz.
 ******************************************************************************/
void opt3001_init(void)
{
    int i;

    // Reset the device using the CONFIG register


    // delay
    for(i = 0; i < 50000; i++){};

    // Program the CONFIG register to POWER_UP and bein CR_2 mode
}

/******************************************************************************
 * Returns the current temperature in degrees C.
 ******************************************************************************/
float opt3001_read_temp(void)
{
    uint16_t temp;

    // Read the ambient temperature

    // Return the data in degrees C.  (See OPT3001 Data Sheet)
    // You will need to modify the line below to return this value
    return 0.0; 
}

