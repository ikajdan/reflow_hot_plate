/**
 ******************************************************************************
 * @file           : com.h
 * @brief          : Communication library
 *
 ******************************************************************************
 */

#ifndef __COM_H__
#define __COM_H__

/* Public includes -----------------------------------------------------------*/
#include "fsm.h"
#include "usbd_cdc_if.h"

/* Public typedefs -----------------------------------------------------------*/
typedef struct {
    uint8_t buffer[APP_RX_DATA_SIZE];
    bool data_received;
    bool send_message;
} COM_Handle_TypeDef;

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern COM_Handle_TypeDef hcom;

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief  Transmits a character via the ITM channel
 * @param  ch: The character to be transmitted
 * @retval The transmitted character
 */
int __io_putchar(int ch);

/**
 * @brief  Transmits the data over the USB CDC interface
 * @param  buffer: The data to be sent
 * @retval Result of all the operations
 */
uint8_t COM_SendData(const char *const buffer);

/**
 * @brief  Sends a JSON message with the current state of the FSM
 * @param  hfsm: The FSM handle
 * @retval Result of all the operations
 */
uint8_t COM_SendMsg(const FSM_Handle_TypeDef *const hfsm);

/**
 * @brief Schedule a send of the message
 * @retval None
 */
void COM_ScheduleSend(void);

#endif /* __COM_H__ */
