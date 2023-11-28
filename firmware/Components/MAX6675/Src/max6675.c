/**
 ******************************************************************************
 * @file           : max6675.c
 * @brief          : MAX6675 library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "max6675.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
float MAX6675_GetTemperature(void) {
    uint16_t data;

    HAL_GPIO_WritePin(MAX6675_CS_PORT, MAX6675_CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_Receive(&hspi1, (uint8_t*)&data, 1, 10);
    HAL_GPIO_WritePin(MAX6675_CS_PORT, MAX6675_CS_PIN, GPIO_PIN_SET);

    // Check if the input is open
    if((data >> 2) & 0x01) {
        return MAX6675_TC_OPEN;
    }

    float temperature = (data >> 3) * 0.25f;
    return temperature + MAX6675_OFFSET;
}
