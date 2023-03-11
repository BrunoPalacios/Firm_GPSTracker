/*
 *  --------------------------------------------------------------------------
 *
 *                               Apnea Detector
 *                               ----------------
 *
 *                      Copyright (C) 2019 Embels Ingeniería
 *          All rights reserved. Protected by international copyright laws.
 *
 *  e-mail: info@Embels.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file   main.c
 *  \brief  Main functions
 *
 *  Long description and purpose of this file.
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  BrPa  Bruno Palacios  BrunoPalacios@Embels.com
 */

/* --------------------------------- Module -------------------------------- */
#ifndef _MAIN_H_
#define _MAIN_H_

/* ----------------------------- Include files ----------------------------- */
#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_spi.h"
#include "stm32f0xx_it.h"
#include "system_stm32f0xx.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
#define	PIN				0
#define	MODO			1
#define	OTYPE			2
#define	PUPD			3
#define	SPEED			4

#define	LED_1_PORT		GPIOA
#define	LED_1_PIN		GPIO_Pin_13 // Pin de programación

#define	LED_2_PORT		GPIOC
#define	LED_2_PIN		GPIO_Pin_13
/* ------------------------------- Data types ------------------------------ */


/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */

int main(int argc, char *argv[]);
void Delay_ms(uint32_t Delay);
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
