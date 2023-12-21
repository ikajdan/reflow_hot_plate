/**
 ******************************************************************************
 * @file           : menu.c
 * @brief          : Menu library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "menu.h"
#include "DSP863.h"
#include "SMDLTLFP.h"
#include "TS991AX35T4.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
MENU_Handle_TypeDef hmenu = {
        .index = 0,
        .root_item = NULL,
        .selected_item = NULL,
        .debouncing = false,
};

MENU_MenuItem_TypeDef item1 = {
        DSP863_name,
        DSP863_stages,
        sizeof(DSP863_profile) / sizeof(DSP863_profile[0]),
        DSP863_profile,
        NULL,
        NULL,
};

MENU_MenuItem_TypeDef item2 = {
        SMDLTLFP_name,
        SMDLTLFP_stages,
        sizeof(SMDLTLFP_profile) / sizeof(SMDLTLFP_profile[0]),
        SMDLTLFP_profile,
        NULL,
        NULL,
};

MENU_MenuItem_TypeDef item3 = {
        TS991AX35T4_name,
        TS991AX35T4_stages,
        sizeof(TS991AX35T4_profile) / sizeof(TS991AX35T4_profile[0]),
        TS991AX35T4_profile,
        NULL,
        NULL,
};

MENU_MenuItem_TypeDef item4 = {
        "Dummy 1",
        TS991AX35T4_stages,
        sizeof(TS991AX35T4_profile) / sizeof(TS991AX35T4_profile[0]),
        TS991AX35T4_profile,
        NULL,
        NULL,
};

MENU_MenuItem_TypeDef item5 = {
        "Dummy 2",
        TS991AX35T4_stages,
        sizeof(TS991AX35T4_profile) / sizeof(TS991AX35T4_profile[0]),
        TS991AX35T4_profile,
        NULL,
        NULL,
};

MENU_MenuItem_TypeDef item6 = {
        "Dummy 3",
        TS991AX35T4_stages,
        sizeof(TS991AX35T4_profile) / sizeof(TS991AX35T4_profile[0]),
        TS991AX35T4_profile,
        NULL,
        NULL,
};

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void MENU_Init(MENU_Handle_TypeDef *hmenu) {
    hmenu->root_item = &item1;
    hmenu->selected_item = hmenu->root_item;

    item1.next = &item2;
    item1.prev = &item6;
    item2.next = &item3;
    item2.prev = &item1;
    item3.next = &item4;
    item3.prev = &item2;
    item4.next = &item5;
    item4.prev = &item3;
    item5.next = &item6;
    item5.prev = &item4;
    item6.next = &item1;
    item6.prev = &item5;
}

void MENU_Next(MENU_Handle_TypeDef *hmenu) {
    if(hmenu->index == 3) {
        hmenu->root_item = hmenu->root_item->next;
    } else {
        hmenu->index++;
    }
    hmenu->selected_item = hmenu->selected_item->next;
}

void MENU_Prev(MENU_Handle_TypeDef *hmenu) {
    if(hmenu->index == 0) {
        hmenu->root_item = hmenu->root_item->prev;
    } else {
        hmenu->index--;
    }
    hmenu->selected_item = hmenu->selected_item->prev;
}
