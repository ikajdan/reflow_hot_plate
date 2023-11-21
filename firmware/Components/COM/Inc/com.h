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
 * @brief  Sends a character to the USB CDC interface
 * @param  ch: The character to be transmitted
 * @return The transmitted character
 */
int __io_putchar(int ch);

#endif /* __COM_H__ */
