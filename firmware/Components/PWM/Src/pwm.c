/**
 ******************************************************************************
 * @file           : pwm.c
 * @brief          : PWM library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "pwm.h"

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
void PWM_SetDutyCycle(TIM_HandleTypeDef *const htim, const uint32_t channel, float duty_cycle) {
    duty_cycle = clamp(duty_cycle, 0.0f, 100.0f);
    uint32_t COMPARE = (duty_cycle * (__HAL_TIM_GET_AUTORELOAD(htim) + 1)) / 100;
    __HAL_TIM_SET_COMPARE(htim, channel, COMPARE);
}
