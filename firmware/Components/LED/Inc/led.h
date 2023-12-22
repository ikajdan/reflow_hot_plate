/**
 ******************************************************************************
 * @file           : led.h
 * @brief          : LED library
 *
 ******************************************************************************
 */

#ifndef __LED_H__
#define __LED_H__

/* Public includes -----------------------------------------------------------*/

/* Public typedefs -----------------------------------------------------------*/

/* Public defines ------------------------------------------------------------*/
typedef enum LED_State {
    LED_PRE,
    LED_SOAK,
    LED_REF,
    LED_COOL,
    LED_OFF,
    LED_ON
} LED_State;

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief  Set the state of LEDs
 * @param  state: The desire state
 * @retval None
 */
void LED_SetState(const LED_State state);

#endif /* __LED_H__ */
