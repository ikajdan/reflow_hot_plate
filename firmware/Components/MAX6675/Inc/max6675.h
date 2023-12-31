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
#include "stm32f1xx_hal.h"

/* Public typedefs -----------------------------------------------------------*/
extern SPI_HandleTypeDef MAX6675_SPI_PORT;

/* Public defines ------------------------------------------------------------*/
#define MAX6675_TC_OPEN -1

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Read the data from the IC
 * @retval None
 */
void MAX6675_ReceiveData(void);

/**
 * @brief Calculate the temperature from the received data
 * @retval None
 */
void MAX6675_CalculateTemperature(void);

/**
 * @brief Read the temperature from the thermocouple sensor
 * @retval The temperature reading in degrees Celsius * 100
 */
int16_t MAX6675_GetTemperature(void);
#endif /* __MAX6675_H__ */
