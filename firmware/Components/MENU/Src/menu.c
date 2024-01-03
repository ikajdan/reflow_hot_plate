/**
 ******************************************************************************
 * @file           : menu.c
 * @brief          : Menu library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "menu.h"
#include "LITTLE_INFERNO.h"
#include "OLIMEX_SAC305.h"
#include "QUALITEK_DSP863.h"
#include "SMD291SNL.h"
#include "SMDLTLFP.h"
#include "TS1LT500C.h"
#include "TS991AX35T4.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define MENU_ITEM(name, stages, profile)                                    \
{                                                                           \
    name, stages, sizeof(profile) / sizeof(profile[0]), profile, NULL, NULL \
}

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
MENU_Handle_TypeDef hmenu = {
        .index = 0,
        .root_item = NULL,
        .selected_item = NULL,
        .debouncing = false,
};

MENU_MenuItem_TypeDef item1 = MENU_ITEM(QUALITEK_DSP863_name, QUALITEK_DSP863_stages, QUALITEK_DSP863_profile);
MENU_MenuItem_TypeDef item2 = MENU_ITEM(OLIMEX_SAC305_name, OLIMEX_SAC305_stages, OLIMEX_SAC305_profile);
MENU_MenuItem_TypeDef item3 = MENU_ITEM(SMDLTLFP_name, SMDLTLFP_stages, SMDLTLFP_profile);
MENU_MenuItem_TypeDef item4 = MENU_ITEM(SMD291SNL_name, SMD291SNL_stages, SMD291SNL_profile);
MENU_MenuItem_TypeDef item5 = MENU_ITEM(TS991AX35T4_name, TS991AX35T4_stages, TS991AX35T4_profile);
MENU_MenuItem_TypeDef item6 = MENU_ITEM(TS1LT500C_name, TS1LT500C_stages, TS1LT500C_profile);
MENU_MenuItem_TypeDef item7 = MENU_ITEM(LITTLE_INFERNO_name, LITTLE_INFERNO_stages, LITTLE_INFERNO_profile);

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void MENU_Init(MENU_Handle_TypeDef *hmenu) {
    hmenu->root_item = &item1;
    hmenu->selected_item = hmenu->root_item;

    item1.next = &item2;
    item1.prev = &item7;
    item2.next = &item3;
    item2.prev = &item1;
    item3.next = &item4;
    item3.prev = &item2;
    item4.next = &item5;
    item4.prev = &item3;
    item5.next = &item6;
    item5.prev = &item4;
    item6.next = &item7;
    item6.prev = &item5;
    item7.next = &item1;
    item7.prev = &item6;
}

void MENU_Next(MENU_Handle_TypeDef *hmenu) {
    if(hmenu->selected_item->next != NULL) {
        hmenu->selected_item = hmenu->selected_item->next;
    }

    if(hmenu->index == MENU_SIZE - 1) {
        if(hmenu->root_item->next != NULL) {
            hmenu->root_item = hmenu->root_item->next;
        }
    } else {
        hmenu->index++;
    }
}

void MENU_Prev(MENU_Handle_TypeDef *hmenu) {
    if(hmenu->selected_item->prev != NULL) {
        hmenu->selected_item = hmenu->selected_item->prev;
    }

    if(hmenu->index == 0) {
        if(hmenu->root_item->prev != NULL) {
            hmenu->root_item = hmenu->root_item->prev;
        }
    } else {
        hmenu->index--;
    }
}
