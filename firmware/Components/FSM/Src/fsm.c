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
FSM_Handle_TypeDef hfsm1 = {
        .running = false,
        .duration = 0,
        .profile_duration = 0,
        .temperature = 0.0f,
        .target_temperature = 0,
        .output = 0.0f,
        .state = FSM_IDLE,
        .name = NULL,
        .stages = NULL,
        .profile = NULL,
};

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void FSM_Init(FSM_Handle_TypeDef *hfsm, char *const name, uint16_t *const stages,
        const size_t profile_duration, uint8_t *const profile)
{
    hfsm->name = name;
    hfsm->stages = stages;
    hfsm->profile_duration = profile_duration;
    hfsm->profile = profile;
}
