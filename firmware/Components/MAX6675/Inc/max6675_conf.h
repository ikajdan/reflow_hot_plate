/**
 ******************************************************************************
 * @file           : max6675_conf.h
 * @brief          : MAX6675 library configuration
 *
 ******************************************************************************
 */

#ifndef __MAX6675_CONFIG_H__
#define __MAX6675_CONFIG_H__

/* Public includes -----------------------------------------------------------*/

/* Public typedefs -----------------------------------------------------------*/

/* Public defines ------------------------------------------------------------*/
/**
 * @brief SPI Port
 */
#define MAX6675_SPI_PORT hspi1

/**
 * @brief CS GPIO Port
 */
#define MAX6675_CS_PORT GPIOA

/**
 * @brief CS GPIO Port
 */
#define MAX6675_CS_PIN GPIO_PIN_4

/**
 * @brief Temperature drift calibration offset
 */
#define MAX6675_OFFSET 0.0f

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

#endif /* __MAX6675_CONFIG_H__ */
