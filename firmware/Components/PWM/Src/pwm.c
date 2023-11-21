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

/* Public functions ----------------------------------------------------------*/
void PWM_SetDutyCycle(TIM_HandleTypeDef *const htim, const uint32_t channel, float duty_cycle) {
    if(duty_cycle < 0.0f) {
        duty_cycle = 0.0f;
    } else if(duty_cycle > 100.0f) {
        duty_cycle = 100.0f;
    }

    uint32_t COMPARE = (duty_cycle * (__HAL_TIM_GET_AUTORELOAD(htim) + 1)) / 100;
    __HAL_TIM_SET_COMPARE(htim, channel, COMPARE);
}
