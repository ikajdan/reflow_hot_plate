/**
 ******************************************************************************
 * @file           : fsm.h
 * @brief          : Finite-state machine library
 *
 ******************************************************************************
 */

#ifndef __FSM_H__
#define __FSM_H__

/* Public includes -----------------------------------------------------------*/
#include "fsm_conf.h"
#include "menu.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Public typedefs -----------------------------------------------------------*/
typedef enum {
    FSM_WELCOME,
    FSM_MENU,
    FSM_PRECHECK,
    FSM_HEATING,
    FSM_DONE,
    FSM_ABORTED,
    FSM_ERROR,
} FSM_Device_State;

typedef enum {
    FSM_HEATING_PRE,
    FSM_HEATING_SOAK,
    FSM_HEATING_REF,
    FSM_HEATING_COOL,
} FSM_Heating_Stage;

typedef struct {
    FSM_Device_State state;
    FSM_Heating_Stage stage;
    uint32_t duration;
    uint32_t profile_duration;
    uint8_t error_duration;
    int16_t tc_temperature;
    int16_t rtd_temperature;
    int16_t temperature;
    uint8_t target_temperature;
    float output;
    char *name;
    uint16_t *stages;
    uint8_t *profile;
} FSM_Handle_TypeDef;

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern FSM_Handle_TypeDef hfsm;

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief  Set the active profile
 * @param  hmenu: Pointer to the menu handle
 * @param  hfsm: Pointer to the finite-state machine handle
 * @retval None
 */
void FSM_SetActiveProfile(MENU_Handle_TypeDef *hmenu, FSM_Handle_TypeDef *hfsm);

#endif /* __FSM_H__ */
