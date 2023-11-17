/**
 ******************************************************************************
 * @file           : rtd_conf.h
 * @brief          : RTD library configuration
 *
 ******************************************************************************
 */

#ifndef __RTD_CONFIG_H__
#define __RTD_CONFIG_H__

/* Public includes -----------------------------------------------------------*/

/* Public typedefs -----------------------------------------------------------*/

/* Public defines ------------------------------------------------------------*/
/**
 * RTD's nominal resistance
 */
#define RTD_R0 100

/**
 * Wheatstone bridge resistor values
 *
 *
 *       ┌───[ R3 ]──(Vout+)──[ Rx ]───┐
 *       │                             │
 * VIN ──┤                             ├── GND
 *       │                             │
 *       └───[ R1 ]──(Vout-)──[ R2 ]───┘
 *
 */
#define RTD_R1 1000
#define RTD_R2 100
#define RTD_R3 1000

/**
 * Wheatstone bridge reference voltage
 */
#define RTD_VIN 3.3f

/**
 * Instrumentation amplifier gain
 */
#define RTD_GAIN 6

/**
 * The number of samples to be averaged when measuring the temperature
 */
#define RTD_SAMPLES 100

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

#endif /* __RTD_CONFIG_H__ */
