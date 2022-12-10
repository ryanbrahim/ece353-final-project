/*
 * opt3001.c
 *
 *  Created on: Oct 20, 2020
 *      Author: Joe Krachey
 */

#include "main.h"
#include <math.h>


/* INTERNAL FUNCTIONS */

/******************************************************************************
 * Converts light register value to lux.
 ******************************************************************************/
float reg2lux(uint16_t result_reg)
{
    // Convert register to lux (See OPT3001 Data Sheet)
    uint16_t exp = (result_reg & OPT3001_RSLT_EXP_MASK) >> 12;
    uint16_t frac = (result_reg & OPT3001_RSLT_FRAC_MASK);
    float lux = ( frac<<exp ) / 100;
    return lux;
}

/******************************************************************************
 * Converts lux value to light register value.
 ******************************************************************************/
uint16_t lux2reg(float f_lux)
{
    // Round lux to nearest int
    uint16_t i_lux = (uint16_t)roundf(f_lux);
    // Convert lux to register (See OPT3001 Data Sheet)
    uint16_t exp = OPT3001_RN_EXP;
    uint16_t frac = (100 * i_lux)>>exp;
    uint16_t reg = (OPT3001_RSLT_EXP_MASK&(exp<<12)) | (OPT3001_RSLT_FRAC_MASK&frac);
    return reg;
}


/* PUBLIC FUNCTIONS */

/******************************************************************************
 * Initialize the opt3001 temperature sensor on the MKII.  This function assumes
 * that the I2C interface has already been configured to operate at 100KHz.
 ******************************************************************************/
void opt3001_init(void)
{
    int i;

    // Reset the device using the CONFIG register
    i2c_write_16(OPT3001_I2C_ADDR, OPT3001_CONFIG_REG, 0x0000);

    // delay
    for(i = 0; i < 50000; i++){};

    // Program the CONFIG register to POWER_UP and bein CR_2 mode
    uint16_t config_reg = (OPT3001_CFG_RN_MASK & (OPT3001_RN_EXP << 12))
            | OPT3001_CFG_CT_100MS
            | OPT3001_CFG_M_CONTINUOUS
            | OPT3001_CFG_L_LATCHED_WINDOW
            | OPT3001_CFG_POL_ACTIVE_LOW
            | OPT3001_CFG_ME_USE_MASK_EXP
            | OPT3001_CFG_FC_ONE_FAULT;
    i2c_write_16(OPT3001_I2C_ADDR, OPT3001_CONFIG_REG, config_reg);

    // Program the limit registers to interrupt beyond low/high thresholds
    uint16_t low_limit = lux2reg(OPT3001_LOW_LIM_LUX);
    uint16_t high_limit = lux2reg(OPT3001_HIGH_LIM_LUX);
    i2c_write_16(OPT3001_I2C_ADDR, OPT3001_LOW_LIM_REG, low_limit);
    i2c_write_16(OPT3001_I2C_ADDR, OPT3001_HIGH_LIM_REG, high_limit);

    // Configure interrupts on P4
    OPT3001_INT_PORT->DIR &= ~OPT3001_INT_PIN;  // Set as input pin
    OPT3001_INT_PORT->REN &= ~OPT3001_INT_PIN;  // Disable pull-up/down resistors (OPT3001 already pulls up!)
    OPT3001_INT_PORT->IE |= OPT3001_INT_PIN;    // Enable interrupts
    OPT3001_INT_PORT->IES |= OPT3001_INT_PIN;   // Interrupt on hi->lo transition

    // Enable the NVIC
    __enable_irq();
    NVIC_EnableIRQ(PORT4_IRQn);
    NVIC_SetPriority(PORT4_IRQn, 0);

}


/******************************************************************************
 * Returns the current ambient light in lux.
 ******************************************************************************/
float opt3001_read_light(void)
{
    // Read the ambient light from register
    uint16_t result_reg = i2c_read_16(OPT3001_I2C_ADDR, OPT3001_RESULT_REG);
    // Parse register data into lux
    float lux = reg2lux(result_reg);
    // Return the data in lux.
    return lux;
}

/* IRQ HANDLER */
void PORT4_IRQHandler()
{
    printf("Light interrupt!\r\n");
    // Clear pending interrupt
    OPT3001_INT_PORT->IFG &= ~OPT3001_INT_PIN;
}





