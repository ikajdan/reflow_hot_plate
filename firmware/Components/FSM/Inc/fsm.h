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
    float temperature;
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
 * @brief  Initialize the finite-state machine
 * @param  hfsm: Pointer to the finite-state machine handle
 * @param  name: Pointer to the profile name array
 * @param  stages: Pointer to the stages array
 * @param  profile_duration: The duration of the profile
 * @param  profile: Pointer to the profile array
 * @retval None
 */
void FSM_Init(FSM_Handle_TypeDef *hfsm, const char *name, const uint16_t *stages,
        const size_t profile_duration, const uint8_t *profile);

#endif /* __FSM_H__ */
