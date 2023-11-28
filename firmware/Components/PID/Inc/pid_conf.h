/**
 ******************************************************************************
 * @file           : pid_conf.h
 * @brief          : PID library configuration
 *
 ******************************************************************************
 */

#ifndef __PID_CONFIG_H__
#define __PID_CONFIG_H__

/* Public includes -----------------------------------------------------------*/

/* Public typedefs -----------------------------------------------------------*/

/* Public defines ------------------------------------------------------------*/
/**
 * @brief Proportional gain for the PID controller
 */
#define PID_KP 0.01f

/**
 * @brief Integral gain for the PID controller
 */
#define PID_KI 0.1f

/**
 * @brief Derivative gain for the PID controller
 */
#define PID_KD 0.01f

/**
 * @brief Sampling time for the PID controller
 */
#define PID_TS 100.0f

/**
 * @brief Minimum allowable value for the PID controller output
 */
#define PID_MIN 0.0f

/**
 * @brief Maximum allowable value for the PID controller output
 */
#define PID_MAX 100.0f

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

#endif /* __PID_CONFIG_H__ */
