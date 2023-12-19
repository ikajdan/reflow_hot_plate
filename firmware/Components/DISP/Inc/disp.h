/**
 ******************************************************************************
 * @file           : disp.h
 * @brief          : Display library
 *
 ******************************************************************************
 */

#ifndef __LCD_H__
#define __LCD_H__

/* Public includes -----------------------------------------------------------*/
#include <stdbool.h>

/* Public typedefs -----------------------------------------------------------*/
typedef enum {
    LCD_DONE,
    LCD_ABORTED,
    LCD_ERROR,
    LCD_WAITING,
} LCD_Prompt_Type;

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern bool LCD_REDRAW;

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Draw the welcome screen
 * @retval None
 */
void LCD_DrawWelcome(void);

/**
 * @brief Draw the menu screen
 * @retval None
 */
void LCD_DrawMenu(void);

/**
 * @brief Draw the process info screen
 * @retval None
 */
void LCD_DrawProcessInfo(void);

/**
 * @brief Draw the prompt screen
 * @retval None
 */
void LCD_DrawPrompt(LCD_Prompt_Type type);

/**
 * @brief Schedule the LCD redraw
 * @retval None
 */
void LCD_ScheduleRedraw(void);

#endif /* __LCD_H__ */
