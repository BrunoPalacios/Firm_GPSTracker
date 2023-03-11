/* 
 * File:   LIS2DE12.h
 * Author: Bruno
 *
 */

#ifndef LIS2DE12_H
#define	LIS2DE12_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "portSPI.h"

void initLIS2(void);

#ifdef	__cplusplus
}
#endif

#endif

