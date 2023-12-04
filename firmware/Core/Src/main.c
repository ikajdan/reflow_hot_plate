/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdbool.h>
#include "com.h"
#include "led.h"
#include "pwm.h"
#include "pid.h"
#include "ssd1306.h"
#include "max6675.h"
#include "rtd.h"
#include "dsp_863.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static bool STARTUP = true;
static bool DEBOUNCING = false;
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USB_DEVICE_Init();
    MX_ADC1_Init();
    MX_I2C2_Init();
    MX_SPI1_Init();
    MX_SPI2_Init();
    MX_TIM3_Init();
    MX_I2C1_Init();
    MX_TIM1_Init();
    MX_TIM2_Init();
    MX_TIM4_Init();
    /* USER CODE BEGIN 2 */
    HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)RTD_ADC_REGISTER, RTD_SAMPLES);

    HAL_TIM_Base_Start_IT(&htim1); // (10 Hz) Control loop
    HAL_TIM_Base_Start_IT(&htim2); // (10 Hz) GUI update
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // (1 kHz) Heatbed driver

    LED_SetState(LED_ON);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while(1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
    RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
            {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
            | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
            {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC | RCC_PERIPHCLK_USB;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
    PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
    if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
            {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
/**
 * @brief  Period elapsed callback in non-blocking mode
 * @param  htim: TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if(htim == &htim1) {
        static uint32_t process_time = 0; // Process time in ms
        uint32_t process_time_seconds = process_time / 1000;
        int process_stage = 0;
        float output = 0;

        // Get the output from the PID controller
        if(process_time_seconds < DSP_863_SIZE) {
            float temperature = RTD_GetTemperature();
            float targret_temperature = dsp_863[process_time_seconds];
            output = PID_GetOutput(temperature, targret_temperature);
        }

        PWM_SetDutyCycle(&htim3, TIM_CHANNEL_1, output);

        // Determine the process stage based on the current time
        for(int i = 0; i < 4; i++) {
            if(process_time_seconds >= dsp_863_stages[i]) {
                process_stage = i + 1;
            } else {
                break;
            }
        }

        LED_SetState(process_stage);

        process_time += 100;
    } else if(htim == &htim2) {
        // Turn off LEDs after the startup
        if(STARTUP == true && HAL_GetTick() > 2000) {
            LED_SetState(LED_OFF);
            STARTUP = false;
        }
    } else if(htim == &htim4) {
        DEBOUNCING = false;
        HAL_TIM_Base_Stop_IT(&htim4);
    }
}

/**
 * @brief  EXTI line detection callbacks
 * @param  GPIO_Pin: Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    // Check if buttons are being debounced
    if(DEBOUNCING) {
        return;
    }

    switch(GPIO_Pin) {
        case BUTTON_UP_Pin:
            // Stub
            break;
        case BUTTON_DOWN_Pin:
            // Stub
            break;
        case BUTTON_LEFT_Pin:
            // Stub
            break;
        case BUTTON_RIGHT_Pin:
            // Stub
            break;
        default:
            break;
    }

    DEBOUNCING = true;
    HAL_TIM_Base_Start_IT(&htim4); // (25 ms) SW debouncing
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    __disable_irq();
    while(1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    // printf("Wrong parameters value: file %s on line %lu\r\n", file, line);
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
