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
#ifndef _PINOUT_H_
#define _PINOUT_H_

/* ----------------------------- Include files ----------------------------- */
#include "stm32f0xx_gpio.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
#define	PUERTOS			3
#define	PINES			16

#define	PIN				0
#define	MODO			1
#define	OTYPE			2
#define	PUPD			3
#define	SPEED			4
#define	CONFIG			5
/* ------------------------------- Data types ------------------------------ */
uint32_t	Puerto[PUERTOS] = {GPIOA_BASE, GPIOB_BASE, GPIOC_BASE};
uint32_t	Pin[PUERTOS][PINES][6] =
{
		{		/* GPIOA */
				{GPIO_Pin_0, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},		//
				{GPIO_Pin_1, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},		//
				{GPIO_Pin_2, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 1},		//	VBATT
				{GPIO_Pin_3, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},		//
				{GPIO_Pin_4, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},		//
				{GPIO_Pin_5, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},		//
				{GPIO_Pin_6, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},		//
				{GPIO_Pin_7, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},		//
				{GPIO_Pin_8, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 1},	//	GPS_ON
				{GPIO_Pin_9, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 1},		//  GPS RX
				{GPIO_Pin_10, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 1},	//	GPS TX
				{GPIO_Pin_11, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},	//
				{GPIO_Pin_12, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},	//
				{GPIO_Pin_13, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},	//
				{GPIO_Pin_14, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},	//
				{GPIO_Pin_15, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0}		//
		},

		{		/* GPIOB */
				{GPIO_Pin_0, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},	//
				{GPIO_Pin_1, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},	//
				{GPIO_Pin_2, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 1},	//	reset sim800
				{GPIO_Pin_3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},		//
				{GPIO_Pin_4, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},	//
				{GPIO_Pin_5, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},	//
				{GPIO_Pin_6, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},	//
				{GPIO_Pin_7, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},	//
				{GPIO_Pin_8, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},	//
				{GPIO_Pin_9, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},		//
				{GPIO_Pin_10, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 1},	// SIM RX
				{GPIO_Pin_11, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 1},	// SIM TX
				{GPIO_Pin_12, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},	//
				{GPIO_Pin_13, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},	//
				{GPIO_Pin_14, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},	//
				{GPIO_Pin_15, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 1}	//	GPS Reset
		},
		{		/* GPIOC */
				{GPIO_Pin_0, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},
				{GPIO_Pin_1, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},
				{GPIO_Pin_2, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},
				{GPIO_Pin_3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},
				{GPIO_Pin_4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},
				{GPIO_Pin_5, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},
				{GPIO_Pin_6, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},
				{GPIO_Pin_7, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},
				{GPIO_Pin_8, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},
				{GPIO_Pin_9, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},
				{GPIO_Pin_10, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},
				{GPIO_Pin_11, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},
				{GPIO_Pin_12, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},
				{GPIO_Pin_13, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},
				{GPIO_Pin_14, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0},
				{GPIO_Pin_15, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Level_1, 0}
		}
};

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
