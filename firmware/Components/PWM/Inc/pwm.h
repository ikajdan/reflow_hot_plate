/**
 ******************************************************************************
 * @file           : pwm.h
 * @brief          : PWM library
 *
 ******************************************************************************
 */

#ifndef __PWM_H__
#define __PWM_H__

/* Public includes -----------------------------------------------------------*/

/* Public typedefs -----------------------------------------------------------*/

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief  Sets the duty cycle for a PWM signal on a specific channel of a timer
 * @param  htim: TIM handle
 * @param  channel: Channel of the timer
 * @param  duty_cycle: The desired duty cycle
 * @retval None
 */
void PWM_SetDutyCycle(TIM_HandleTypeDef *const htim, const uint32_t channel, float duty_cycle);

#endif /* __PWM_H__ */
