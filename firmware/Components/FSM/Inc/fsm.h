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
#include <stdbool.h>
#include <stdint.h>
#include "fsm_conf.h"

/* Public typedefs -----------------------------------------------------------*/
enum FSM_Device_State {
    FSM_PRE,
    FSM_SOAK,
    FSM_REF,
    FSM_COOL,
    FSM_IDLE
};

typedef enum FSM_Device_State FSM_Device_State;

typedef struct {
    bool enabled;
    uint32_t duration;
    uint32_t profile_duration;
    float temperature;
    uint8_t target_temperature;
    float output;
    FSM_Device_State state;
    uint8_t *profile;
    uint16_t *stages;
} FSM_Handle_TypeDef;

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern FSM_Handle_TypeDef hfsm1;

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief  Initialize the finite-state machine
 * @param  hfsm: Pointer to the finite-state machine handle
 * @param  profile_duration: The duration of the profile
 * @param  profile: Pointer to the profile array
 * @param  stages: Pointer to the stages array
 * @retval None
 */
void FSM_Init(FSM_Handle_TypeDef *hfsm, size_t profile_duration, uint8_t *profile, uint16_t *stages);

#endif /* __FSM_H__ */
