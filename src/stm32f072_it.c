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

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */

#include "stm32f0xx.h"
#include "stm32f0xx_it.h"
#include "APIs/ADCs/Lectura ADCs.h"
#include "USART.h"
#include "portUSART_STM32F072.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */

uint32_t				Systick = 0;

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

uint32_t getSystick(void){

	return Systick;
}

void SysTick_Handler(void){

	Systick++;
}



void TIM2_IRQHandler(void){

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		ISR_TimerUSART(USART_3);
	}
}


void USART3_4_IRQHandler(void){

	USART_IRQ_Rx(USART_3);
}
/* ------------------------------ End of file ------------------------------ */
