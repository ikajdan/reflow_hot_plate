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
#include "iwdg.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "menu.h"
#include "fsm.h"
#include "disp.h"
#include "ssd1306.h"
#include "max6675.h"
#include "rtd.h"
#include "pid.h"
#include "pwm.h"
#include "led.h"
#include "com.h"
#include <stdbool.h>
#include <stdio.h>
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
    MX_ADC1_Init();
    MX_I2C1_Init();
    MX_I2C2_Init();
    MX_SPI1_Init();
    MX_SPI2_Init();
    MX_TIM1_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_USB_DEVICE_Init();
    MX_IWDG_Init();
    /* USER CODE BEGIN 2 */
    HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)RTD_ADC_REGISTER, RTD_SAMPLES);

    HAL_TIM_Base_Start_IT(&htim1); // (10 Hz) Control loop
    HAL_TIM_Base_Start_IT(&htim2); // (10 Hz) GUI update
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // (1 kHz) Heatbed driver

    LED_SetState(LED_ON);

    ssd1306_Init();

    MENU_Init(&hmenu);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while(1) {
        // Redraw the screen
        if(LCD_REDRAW) {
            LCD_REDRAW = false;
            ssd1306_Fill(Black);

            switch(hfsm.state) {
                case FSM_WELCOME:
                    LCD_DrawWelcome();
                    break;

                case FSM_MENU:
                    LCD_DrawMenu(&hmenu);
                    break;

                case FSM_PRECHECK:
                    LCD_DrawPrompt(LCD_WAITING);
                    break;

                case FSM_HEATING:
                    LCD_DrawProcessInfo();
                    break;

                case FSM_DONE:
                    LCD_DrawPrompt(LCD_DONE);
                    break;

                case FSM_ABORTED:
                    LCD_DrawPrompt(LCD_ABORTED);
                    break;

                case FSM_ERROR:
                    LCD_DrawPrompt(LCD_ERROR);
                    break;

                default:
                    break;
            }

            ssd1306_UpdateScreen();
        }

        // Send a message
        if(hcom.send_message) {
            hcom.send_message = false;
            COM_SendMsg(&hfsm);
        }
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
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
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
        hfsm.temperature = RTD_GetTemperature();

        // Check if the temperature is inside of the allowed range
        if(hfsm.temperature < TEMPERATURE_MIN || hfsm.temperature > TEMPERATURE_MAX) {
            if(hfsm.error_duration > MAXIMUM_CYCLES) {
                hfsm.state = FSM_ERROR;
                hfsm.error_duration = 0;
            }
            hfsm.error_duration += 1;
        } else {
            hfsm.error_duration = 0;
        }

        switch(hfsm.state) {
            case FSM_PRECHECK:
                // Start the process only if the temperature is within the desired range
                if(hfsm.temperature < hfsm.profile[0] * 2) {
                    hfsm.state = FSM_HEATING;
                    hfsm.duration = 0;
                }
                break;

            case FSM_HEATING:
                uint32_t duration_seconds = hfsm.duration / 1000;

                if(duration_seconds > hfsm.profile_duration) {
                    hfsm.state = FSM_DONE;
                } else {
                    hfsm.target_temperature = hfsm.profile[duration_seconds];
                    hfsm.output = PID_GetOutput(hfsm.temperature, hfsm.target_temperature);

                    // Determine the process stage based on the current time
                    for(int i = 0; i < 4; i++) {
                        if(duration_seconds >= hfsm.stages[i]) {
                            hfsm.stage = i;
                        } else {
                            break;
                        }
                    }
                }
                break;

            default:
                hfsm.target_temperature = 0;
                hfsm.output = 0;
                break;
        }

        PWM_SetDutyCycle(&htim3, TIM_CHANNEL_1, hfsm.output);
        HAL_IWDG_Refresh(&hiwdg); // 200 ms window

        hfsm.duration += 100;
    } else if(htim == &htim2) {
        LCD_ScheduleRedraw();

        if(hfsm.state != FSM_WELCOME) {
            // Check if a message has been received
            if(hcom.data_received) {
                hcom.data_received = false;

                if(hcom.buffer[0] == '1') {
                    hfsm.state = FSM_PRECHECK;
                } else if(hcom.buffer[0] == '0') {
                    hfsm.state = FSM_ABORTED;
                }
            }

            if(hfsm.state == FSM_HEATING) {
                LED_SetState(hfsm.stage);
            } else {
                LED_SetState(LED_OFF);
            }

            COM_ScheduleSend();
        } else {
            if(HAL_GetTick() > STARTUP_DELAY) {
                if(hfsm.state == FSM_WELCOME) {
                    hfsm.state = FSM_MENU;
                }
            }
        }
    } else if(htim == &htim4) {
        printf("Stopping TIM4: %lu\n\n", HAL_GetTick());
        HAL_TIM_Base_Stop_IT(&htim4);
        hmenu.debouncing = false;
    }
}

/**
 * @brief  EXTI line detection callbacks
 * @param  GPIO_Pin: Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    // Check if buttons are being debounced
    if(hmenu.debouncing) {
        uint32_t counter_value = __HAL_TIM_GET_COUNTER(&htim4);
        uint32_t timer_frequency = HAL_RCC_GetHCLKFreq() / (htim4.Init.Prescaler + 1);
        uint32_t time = (counter_value * 1000) / timer_frequency;
        printf("Debouncing: %lu\n", time);

        return;
    } else {
        // Ignore button callbacks from now on
        printf("Starting TIM4: %lu\n", HAL_GetTick());
        hmenu.debouncing = true;

        // Clear the interrupt flag, otherwise the update callback will be called
        __HAL_TIM_CLEAR_IT(&htim4, TIM_IT_UPDATE);
        __HAL_TIM_SET_COUNTER(&htim4, 0);

        HAL_TIM_Base_Start_IT(&htim4); // 100 ms
    }

    // Handle button events based on the current state
// @formatter:off
    switch(hfsm.state) {
        case FSM_WELCOME:
        case FSM_DONE:
        case FSM_ABORTED:
        case FSM_ERROR:
            hfsm.state = FSM_MENU;
            return;

        default:
            break;
    }
// @formatter:on

    switch(hfsm.state) {
        case FSM_MENU:
            if(GPIO_Pin == BUTTON_UP_Pin) {
                MENU_Prev(&hmenu);
            } else if(GPIO_Pin == BUTTON_DOWN_Pin) {
                MENU_Next(&hmenu);
            } else if(GPIO_Pin == BUTTON_RIGHT_Pin) {
                FSM_SetActiveProfile(&hmenu, &hfsm);
                hfsm.state = FSM_PRECHECK;
            }
            break;

        case FSM_HEATING:
            if(GPIO_Pin == BUTTON_LEFT_Pin) {
                hfsm.state = FSM_ABORTED;
            }
            break;

        default:
            break;
    }
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
    printf("Wrong parameters value: file %s on line %lu\r\n", file, line);
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
