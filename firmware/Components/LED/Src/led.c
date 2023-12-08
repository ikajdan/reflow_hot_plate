/**
 ******************************************************************************
 * @file           : led.c
 * @brief          : LED library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "led.h"
#include "main.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void LED_SetState(const LED_State state) {
    static LED_State previous_state = LED_OFF;

    if(state == previous_state) {
        return;
    }

    previous_state = state;

    switch(state) {
        case LED_PRE:
            HAL_GPIO_WritePin(LED_PREHEAT_GPIO_Port, LED_PREHEAT_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_SOAK_GPIO_Port, LED_SOAK_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_REFLOW_GPIO_Port, LED_REFLOW_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_COOLING_GPIO_Port, LED_COOLING_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin, GPIO_PIN_SET);
            break;
        case LED_SOAK:
            HAL_GPIO_WritePin(LED_PREHEAT_GPIO_Port, LED_PREHEAT_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_SOAK_GPIO_Port, LED_SOAK_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_REFLOW_GPIO_Port, LED_REFLOW_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_COOLING_GPIO_Port, LED_COOLING_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin, GPIO_PIN_SET);
            break;
        case LED_REF:
            HAL_GPIO_WritePin(LED_PREHEAT_GPIO_Port, LED_PREHEAT_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_SOAK_GPIO_Port, LED_SOAK_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_REFLOW_GPIO_Port, LED_REFLOW_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_COOLING_GPIO_Port, LED_COOLING_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin, GPIO_PIN_SET);
            break;
        case LED_COOL:
            HAL_GPIO_WritePin(LED_PREHEAT_GPIO_Port, LED_PREHEAT_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_SOAK_GPIO_Port, LED_SOAK_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_REFLOW_GPIO_Port, LED_REFLOW_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_COOLING_GPIO_Port, LED_COOLING_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin, GPIO_PIN_SET);
            break;
        case LED_ON:
            HAL_GPIO_WritePin(LED_PREHEAT_GPIO_Port, LED_PREHEAT_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_SOAK_GPIO_Port, LED_SOAK_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_REFLOW_GPIO_Port, LED_REFLOW_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_COOLING_GPIO_Port, LED_COOLING_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin, GPIO_PIN_RESET);
            break;
        default:
            HAL_GPIO_WritePin(LED_PREHEAT_GPIO_Port, LED_PREHEAT_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_SOAK_GPIO_Port, LED_SOAK_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_REFLOW_GPIO_Port, LED_REFLOW_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_COOLING_GPIO_Port, LED_COOLING_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin, GPIO_PIN_RESET);
            break;
    }
}
