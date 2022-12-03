/*
 * opt3001.h
 *
 *  Created on: Oct 20, 2020
 *      Author: Joe Krachey
 */

#ifndef OPT3001_H_
#define OPT3001_H_

#include "msp.h"
#include "i2c.h"
#include <stdint.h>
#include <stdbool.h>

#define I2C_LIGHT_ADDR   0x44

#define I2C_LIGHT_RESULT         0x00
#define I2C_LIGHT_CONFIG         0x01
#define I2C_LIGHT_LOW            0x02
#define I2C_LIGHT_HIGH           0x03
#define I2C_LIGHT_MFGID          0x7E
#define I2C_LIGHT_DEVID          0X7F

/* CONFIGURATION REGISTER SETTINGS */
#define OPT3001_RN_FULL          0x8000
#define OPT3001_CT_100MS         0x

/******************************************************************************
 * Initialize the opt3001 temperature sensor on the MKII.  This function assumes
 * that the I2C interface has already been configured to operate at 100KHz.
 ******************************************************************************/
void opt3001_init(void);

/******************************************************************************
 * Returns the current temperature in degrees C.
 ******************************************************************************/
float opt3001_read_light(void);

#endif /* OPT3001_H_ */
