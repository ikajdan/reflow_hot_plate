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
// TODO: Pack into a struct
uint8_t USB_BUFFER_RX[APP_RX_DATA_SIZE];
bool USB_DATA_RECEIVED = false;
bool COM_MSG_SEND = false;

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
int __io_putchar(int ch)
{
    ITM_SendChar(ch);
    return ch;
}

uint8_t COM_Send(const char *const buffer)
{
    return CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer));
}

uint8_t COM_Msg_Send(const FSM_Handle_TypeDef *const hfsm)
{
    static char buffer[APP_TX_DATA_SIZE];
    sprintf(buffer, "{\"Duration\":%lu,\"Temperature\":%f,\"TargetTemperature\":%d,\"State\":%d}\n",
            hfsm->duration / 1000, hfsm->temperature, hfsm->target_temperature, hfsm->state);
    return COM_Send(buffer);
}

void COM_ScheduleMsgSend() {
    COM_MSG_SEND = true;
}
