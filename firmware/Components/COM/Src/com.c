/**
 ******************************************************************************
 * @file           : com.c
 * @brief          : Communication library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "com.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
COM_Handle_TypeDef hcom = {
        .buffer = '\0',
        .data_received = false,
        .send_message = false,
};

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
int __io_putchar(int ch)
{
    ITM_SendChar(ch);
    return ch;
}

uint8_t COM_SendData(const char *const buffer)
{
    return CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer));
}

uint8_t COM_SendMsg(const FSM_Handle_TypeDef *const hfsm)
{
    static char buffer[APP_TX_DATA_SIZE];
    sprintf(buffer, "{\"Duration\":%lu,\"Temperature\":%f,\"TargetTemperature\":%d,\"State\":%d}\n",
            hfsm->duration / 1000, hfsm->temperature, hfsm->target_temperature, hfsm->state);
    return COM_SendData(buffer);
}

void COM_ScheduleSend() {
    hcom.send_message = true;
}
