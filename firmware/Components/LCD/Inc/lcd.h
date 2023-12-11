/**
 ******************************************************************************
 * @file           : lcd.h
 * @brief          : LCD library
 *
 ******************************************************************************
 */

#ifndef __LCD_H__
#define __LCD_H__

/* Public includes -----------------------------------------------------------*/
#include <stdbool.h>

/* Public typedefs -----------------------------------------------------------*/

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern bool LCD_REDRAW;

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Show the welcome screen
 * @retval None
 */
void LCD_ShowWelcome(void);

/**
 * @brief Show the progress bar
 * @retval None
 */
void LCD_ShowProgresBar(void);

/**
 * @brief Show the process info
 * @retval None
 */
void LCD_ShowProcessInfo(void);

/**
 * @brief Schedule the LCD redraw
 * @retval None
 */
void LCD_ScheduleRedraw(void);

#endif /* __LCD_H__ */
