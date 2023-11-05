/**
 ******************************************************************************
 * @file           : max6675.h
 * @brief          : MAX6675 library
 *
 ******************************************************************************
 */

#ifndef __MAX6675_H__
#define __MAX6675_H__

/* Public includes -----------------------------------------------------------*/
#include "max6675_conf.h"

/* Public typedefs -----------------------------------------------------------*/
extern SPI_HandleTypeDef MAX6675_SPI_PORT;

/* Public defines ------------------------------------------------------------*/
#define MAX6675_TC_OPEN -1

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Read the temperature from the thermocouple sensor
 * @retval The temperature reading in degrees Celsius
 */
float MAX6675_GetTemperature(void);

#endif /* __MAX6675_H__ */
