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
    MENU_MenuItem_TypeDef *current_item;
    bool debouncing;
} MENU_Handle_TypeDef;

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern MENU_Handle_TypeDef hmenu;

/* Public function prototypes ------------------------------------------------*/
void MENU_Init(MENU_Handle_TypeDef *hmenu);

#endif /* __MENU_H__ */
