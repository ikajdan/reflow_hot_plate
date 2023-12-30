/**
 ******************************************************************************
 * @file           : max6675.c
 * @brief          : MAX6675 library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "max6675.h"
#include "stm32f1xx_hal.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
static uint32_t conversion_time = 0;
volatile static uint16_t data = 0;
static float temperature = 0;
/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void MAX6675_ReceiveData(void) {
    if(HAL_GetTick() - conversion_time > 250) {
        if(HAL_GPIO_ReadPin(MAX6675_CS_PORT, MAX6675_CS_PIN) == GPIO_PIN_SET) {
            HAL_GPIO_WritePin(MAX6675_CS_PORT, MAX6675_CS_PIN, GPIO_PIN_RESET);
            HAL_SPI_Receive_IT(&hspi1, (uint8_t*)&data, 1);
        }
        conversion_time = HAL_GetTick();
    }
}

void MAX6675_CalculateTemperature(void) {
    HAL_GPIO_WritePin(MAX6675_CS_PORT, MAX6675_CS_PIN, GPIO_PIN_SET);

    // Check if the input is open
    if(data & 0x4) {
        temperature = MAX6675_TC_OPEN;
    } else {
        temperature = (data >> 3) * 0.25f;
    }
}

float MAX6675_GetTemperature(void) {
    return temperature + MAX6675_OFFSET;
}
