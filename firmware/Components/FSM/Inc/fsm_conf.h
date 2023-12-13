/**
 ******************************************************************************
 * @file           : fsm_conf.h
 * @brief          : Finite-state machine library configuration
 *
 ******************************************************************************
 */

#ifndef __FSM_CONFIG_H__
#define __FSM_CONFIG_H__

/* Public includes -----------------------------------------------------------*/

/* Public typedefs -----------------------------------------------------------*/

/* Public defines ------------------------------------------------------------*/
/**
 * @brief Firmware version
 */
#define FIRMWARE_VERSION "v0.1.0"

/**
 * @brief Startup delay in miliseconds
 */
#define STARTUP_DELAY 2000

/**
 * @brief Minimum allowable temperature
 */
#define TEMPERATURE_MIN 10

/**
 * @brief Maximum allowable temperature
 */
#define TEMPERATURE_MAX 270

/**
 * @brief Maximum allowable number of cycles for the deviation
 */
#define MAXIMUM_CYCLES 10

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

#endif /* __FSM_CONFIG_H__ */
