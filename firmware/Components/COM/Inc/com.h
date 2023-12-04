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
 * @brief  Transmit a character via the ITM channel
 * @param  ch: The character to be transmitted
 * @return The transmitted character
 */
int __io_putchar(int ch);

/**
 * @brief  Transmit a character over the CDC interface
 * @param  ch: The character to be transmitted
 * @return The transmitted character
 */
int COM_Send(int ch);

#endif /* __COM_H__ */
