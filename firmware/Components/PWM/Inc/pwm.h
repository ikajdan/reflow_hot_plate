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
 * @brief Set the duty cycle for a PWM signal on a specific Channel of a Timer.
 * @param htim Pointer to the Timer handle structure.
 * @param channel The PWM channel on which to set the duty cycle.
 * @param duty_cycle The desired duty cycle in the range [0.0, 100.0].
 * @retval None
 */
void PWM_SetDutyCycle(TIM_HandleTypeDef *const htim, const uint32_t channel, float duty_cycle);

#endif /* __PWM_H__ */
