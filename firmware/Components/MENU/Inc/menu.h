/**
 ******************************************************************************
 * @file           : menu.h
 * @brief          : Menu library
 *
 ******************************************************************************
 */

#ifndef __MENU_H__
#define __MENU_H__

/* Public includes -----------------------------------------------------------*/
#include "menu_conf.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/* Public typedefs -----------------------------------------------------------*/
typedef struct MENU_MenuItem MENU_MenuItem_TypeDef;

struct MENU_MenuItem {
    const char *profile_name;
    const uint16_t *profile_stages;
    const size_t profile_duration;
    const uint8_t *profile;
    MENU_MenuItem_TypeDef *next;
    MENU_MenuItem_TypeDef *prev;
};

typedef struct {
    uint8_t index;
    MENU_MenuItem_TypeDef *root_item;
    MENU_MenuItem_TypeDef *selected_item;
    bool debouncing;
} MENU_Handle_TypeDef;

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern MENU_Handle_TypeDef hmenu;

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief  Initialize menu
 * @param  hmenu: Pointer to the menu handle
 * @retval None
 */
void MENU_Init(MENU_Handle_TypeDef *hmenu);

/**
 * @brief  Select next item
 * @param  hmenu: Pointer to the menu handle
 * @retval None
 */
void MENU_Next(MENU_Handle_TypeDef *hmenu);

/**
 * @brief  Select previous item
 * @param  hmenu: Pointer to the menu handle
 * @retval None
 */
void MENU_Prev(MENU_Handle_TypeDef *hmenu);

#endif /* __MENU_H__ */
