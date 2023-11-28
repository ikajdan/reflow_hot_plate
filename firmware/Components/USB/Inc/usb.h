/**
 ******************************************************************************
 * @file           : usb.h
 * @brief          : USB communication library
 *
 ******************************************************************************
 */

#ifndef __USB_H__
#define __USB_H__

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

#endif /* __USB_H__ */
