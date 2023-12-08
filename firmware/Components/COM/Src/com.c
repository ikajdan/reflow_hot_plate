/**
 ******************************************************************************
 * @file           : com.c
 * @brief          : Communication library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "com.h"
#include "usbd_cdc_if.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
uint8_t USB_BUFFER_RX[APP_RX_DATA_SIZE];
bool USB_DATA_RECEIVED_FLAG = false;

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
int __io_putchar(int ch)
{
    ITM_SendChar(ch);
    return ch;
}

uint8_t COM_Send(const char *buffer)
{
    return CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer));
}

uint8_t COM_Msg_Send(const FSM_Handle_TypeDef *hfsm)
{
    static char buffer[APP_TX_DATA_SIZE];
    sprintf(buffer, "{\"Duration\":%lu,\"Temperature\":%f,\"TargetTemperature\":%d,\"State\":%d}\n",
            hfsm1.duration / 1000, hfsm1.temperature, hfsm1.target_temperature, hfsm1.state);
    return COM_Send(buffer);
}
