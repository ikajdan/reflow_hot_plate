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
    sprintf(buffer, "{\"Duration\":%lu,\"TC\":%d,\"RTD\":%d,\"Temperature\":%d,\"TargetTemperature\":%d,\"Stage\":%d}\n",
            hfsm->duration / 1000,
            hfsm->tc_temperature,
            hfsm->rtd_temperature,
            hfsm->temperature,
            hfsm->target_temperature,
            hfsm->stage);
    return COM_SendData(buffer);
}

void COM_ScheduleSend() {
    hcom.send_message = true;
}
