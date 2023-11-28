/**
 ******************************************************************************
 * @file           : pid.c
 * @brief          : PID controller library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include "pid.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
static float clamp(float value, float min, float max) {
    if(value < min) {
        return min;
    } else if(value > max) {
        return max;
    } else {
        return value;
    }
}

/* Public functions ----------------------------------------------------------*/
float PID_GetOutput(const float input, const float target) {
    // Integral term accumulator
    static float integral = 0.0f;
    // Previous error for the derivative term
    static float previous_error = 0.0f;

    float error = target - input;
    float proportional = PID_KP * error;
    integral += PID_KI * error * PID_TS;
    float derivative = PID_KD * (error - previous_error) / PID_TS;
    previous_error = error;

    float output = proportional + integral + derivative;

    // Anti-windup
    float output_saturated = clamp(output, PID_MIN, PID_MAX);
    if(fabs(output_saturated - output) > 1e-6) {
        integral -= PID_KI * error * PID_TS;
    }

    return output_saturated;
}
