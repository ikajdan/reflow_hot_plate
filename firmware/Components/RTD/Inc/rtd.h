/**
 ******************************************************************************
 * @file           : rtd.h
 * @brief          : RTD library
 *
 ******************************************************************************
 */

#ifndef __RTD_H__
#define __RTD_H__

/* Public includes -----------------------------------------------------------*/
#include "rtd_conf.h"
#include "stm32f1xx_hal.h"

/* Public typedefs -----------------------------------------------------------*/

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern volatile uint16_t RTD_ADC_REGISTER[RTD_SAMPLES];

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Read the temperature reading from the RTD sensor
 * @retval The temperature reading in degrees Celsius
 */
float RTD_GetTemperature(void);

#endif /* __RTD_H__ */
