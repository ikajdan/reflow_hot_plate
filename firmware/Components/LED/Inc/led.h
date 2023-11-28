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
enum LED_State {
    LED_OFF,
    LED_PRE,
    LED_SOAK,
    LED_REF,
    LED_COOL,
    LED_ON
};

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief  Set the state of the LEDs
 * @param  state: The state LEDs
 * @retval None
 */
void LED_SetState(const uint32_t state);

#endif /* __LED_H__ */
