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

/* GLOBAL ALERT VARIABLES */
extern bool ALERT_LIGHT_LOW;
extern bool ALERT_LIGHT_HIGH;

/* USER DEFINED SETTINGS */
#define OPT3001_RN_EXP              0x5
#define OPT3001_LOW_LIM_LUX         50
#define OPT3001_HIGH_LIM_LUX        600

/* INTERRUPT SETTINGS */
#define OPT3001_INT_PORT            P4
#define OPT3001_INT_PIN             BIT6

/* OPT3001 I2C ADDRESS */
#define OPT3001_I2C_ADDR            0x44

/* REGISTER ADDRESSES */
#define OPT3001_RESULT_REG          0x00
#define OPT3001_CONFIG_REG          0x01
#define OPT3001_LOW_LIM_REG         0x02
#define OPT3001_HIGH_LIM_REG        0x03
#define OPT3001_MFGID_REG           0x7E
#define OPT3001_DEVID_REG           0X7F

/* RESULT REGISTER MASKS */
#define OPT3001_RSLT_EXP_MASK         0xF000
#define OPT3001_RSLT_FRAC_MASK        0x0FFF

/* CONFIGURATION REGISTER SETTINGS */
#define OPT3001_CFG_RN_AUTO_FULL_SCALE      0xC000
#define OPT3001_CFG_CT_100MS                0x0000
#define OPT3001_CFG_CT_800MS                0x0800
#define OPT3001_CFG_M_SHUTDOWN              0x0000
#define OPT3001_CFG_M_SINGLE_SHOT           0x0200
#define OPT3001_CFG_M_CONTINUOUS            0x0600
#define OPT3001_CFG_L_TRANSPARENT_HYST      0x0000
#define OPT3001_CFG_L_LATCHED_WINDOW        0x0010
#define OPT3001_CFG_POL_ACTIVE_LOW          0x0000
#define OPT3001_CFG_POL_ACTIVE_HIGH         0x0008
#define OPT3001_CFG_ME_CLEAR_MASK_EXP       0x0004
#define OPT3001_CFG_ME_USE_MASK_EXP         0x0000
#define OPT3001_CFG_FC_ONE_FAULT            0x0000
#define OPT3001_CFG_FC_TWO_FAULT            0x0001
#define OPT3001_CFG_FC_FOUR_FAULT           0x0002
#define OPT3001_CFG_FC_EIGHT_FAULT          0x0003

/* CONFIGURATION REGISTER MASKS */
#define OPT3001_CFG_RN_MASK         0xF000
#define OPT3001_CFG_CT_MASK         0x0800
#define OPT3001_CFG_M_MASK          0x0600
#define OPT3001_CFG_OVF_MASK        0x0100
#define OPT3001_CFG_CRF_MASK        0x0080
#define OPT3001_CFG_FH_MASK         0x0040
#define OPT3001_CFG_FL_MASK         0x0020
#define OPT3001_CFG_L_MASK          0x0010
#define OPT3001_CFG_POL_MASK        0x0008
#define OPT3001_CFG_ME_MASK         0x0004
#define OPT3001_CFG_FC_MASK         0x0003

/* LOW LIMIT REGISTER MASKS */
#define OPT3001_LOW_LIM_EXP_MASK         0xF000
#define OPT3001_LOW_LIM_RSLT_MASK        0x0FFF

/* HIGH LIMIT REGISTER MASKS */
#define OPT3001_HIGH_LIM_EXP_MASK         0xF000
#define OPT3001_HIGH_LIM_RSLT_MASK        0x0FFF

/******************************************************************************
 * Initialize the opt3001 temperature sensor on the MKII.  This function assumes
 * that the I2C interface has already been configured to operate at 100KHz.
 ******************************************************************************/
void opt3001_init(void);

/******************************************************************************
 * Returns the current temperature in degrees C.
 ******************************************************************************/
float opt3001_read_light(void);

/******************************************************************************
 * FreeRTOS task to monitor light level
 ******************************************************************************/
void task_light_monitor(void *pvParameters)


#endif /* OPT3001_H_ */
