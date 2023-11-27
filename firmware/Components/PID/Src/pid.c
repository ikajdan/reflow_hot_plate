/**
 ******************************************************************************
 * @file           : pid.c
 * @brief          : PID controller library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "pid.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
float PID_GetOutput(const float input, const float target) {
    static float integral = 0.0f; // Integral term accumulator
    static float previous_error = 0.0f; // Previous error for derivative term

    float error = target - input;
    float proportional = PID_KP * error;
    integral += PID_KI * error * PID_TS;
    float derivative = PID_KD * (error - previous_error) / PID_TS;
    previous_error = error;

    return proportional + integral + derivative;
}
