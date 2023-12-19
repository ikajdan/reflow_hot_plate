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
        .current_item = NULL,
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

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void MENU_Init(MENU_Handle_TypeDef *hmenu) {
    hmenu->current_item = &item1;

    item1.next = &item2;
    item1.prev = &item3;
    item2.next = &item3;
    item2.prev = &item1;
    item3.next = &item1;
    item3.prev = &item2;
}
