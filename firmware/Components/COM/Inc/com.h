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

/* Public typedefs -----------------------------------------------------------*/

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

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
uint8_t COM_Send(const char *buffer);

#endif /* __COM_H__ */
