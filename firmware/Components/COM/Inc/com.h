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

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern uint8_t USB_BUFFER_RX[APP_RX_DATA_SIZE];
extern bool USB_DATA_RECEIVED_FLAG;

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
uint8_t COM_Data_Send(const char *buffer);

/**
 * @brief  Sends a JSON message with the current state of the FSM
 * @param  hfsm: The FSM handle
 * @retval Result of all the operations
 */
uint8_t COM_Msg_Send(const FSM_Handle_TypeDef *hfsm);

#endif /* __COM_H__ */
