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
        .enabled = false,
        .duration = 0,
        .profile_duration = 0,
        .temperature = 0.0f,
        .target_temperature = 0,
        .output = 0.0f,
        .state = FSM_IDLE,
        .profile = NULL,
        .stages = NULL
};

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void FSM_Init(FSM_Handle_TypeDef *hfsm, size_t profile_duration, uint8_t *profile, uint16_t *stages)
{
    hfsm->profile_duration = profile_duration;
    hfsm->profile = profile;
    hfsm->stages = stages;
}
