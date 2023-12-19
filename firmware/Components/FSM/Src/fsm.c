/**
 ******************************************************************************
 * @file           : fsm.c
 * @brief          : Finite-state machine library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "fsm.h"
#include <stddef.h>

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
FSM_Handle_TypeDef hfsm = {
        .state = FSM_WELCOME,
        .stage = FSM_HEATING_PRE,
        .duration = 0,
        .profile_duration = 0,
        .error_duration = 0,
        .temperature = 0.0f,
        .target_temperature = 0,
        .output = 0.0f,
        .name = NULL,
        .stages = NULL,
        .profile = NULL,
};

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void FSM_Init(FSM_Handle_TypeDef *hfsm, const char *name, const uint16_t *stages,
        const size_t profile_duration, const uint8_t *profile)
{
    hfsm->name = name;
    hfsm->stages = stages;
    hfsm->profile_duration = profile_duration;
    hfsm->profile = profile;
}
