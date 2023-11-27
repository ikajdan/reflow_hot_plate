/**
 ******************************************************************************
 * @file           : pid.h
 * @brief          : PID controller library
 *
 ******************************************************************************
 */

#ifndef __PID_H__
#define __PID_H__

/* Public includes -----------------------------------------------------------*/
#include "pid_conf.h"

/* Public typedefs -----------------------------------------------------------*/

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief  Calculate the output of a PID controller
 * @param  input: The current value of the process variable
 * @param  target: The desired value of the process variable
 * @retval The computed output of the PID controller
 */
float PID_GetOutput(const float input, const float target);

#endif /* __PID_H__ */
