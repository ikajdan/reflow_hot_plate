/**
 ******************************************************************************
 * @file           : rtd.c
 * @brief          : RTD library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include "rtd.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static const float A = 3.9083e-3; // Alpha coefficient
static const float B = -5.775e-7; // Beta coefficient

/* Public variables ----------------------------------------------------------*/
volatile uint16_t RTD_ADC_REGISTER[RTD_SAMPLES];

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
static float RTD_CalculateResistance(void) {
    // Average the readings
    float sum = 0;
    for(unsigned int i = 0; i < RTD_SAMPLES; i++) {
        sum += RTD_ADC_REGISTER[i];
    }
    float adc_value = sum / RTD_SAMPLES;

    // Convert to volts
    float v_out = adc_value * (3.3f / 4095) / RTD_GAIN;

    float resistance =
            (RTD_R2 * RTD_R3 + RTD_R3 * (RTD_R1 + RTD_R2) * v_out / RTD_VIN)
                    / (RTD_R1 - (RTD_R1 + RTD_R2) * (v_out / RTD_VIN));
    return resistance;
}

/* Public functions ----------------------------------------------------------*/
float RTD_GetTemperature(void) {
    float resistance = RTD_CalculateResistance();
    float discriminant = A * A - 4 * B * (1 - resistance / RTD_R0);

    // Handle negative discriminant
    if(discriminant < 0) {
        return 0;
    }

    float temperature = (-A + sqrt(discriminant)) / (2 * B);
    return temperature + RTD_OFFSET;
}
