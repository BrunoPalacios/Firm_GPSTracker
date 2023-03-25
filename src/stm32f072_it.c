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
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */



void DMA1_Channel2_3_IRQHandler(void){

	if( DMA_GetITStatus(DMA1_IT_HT3)){

		DMA_ClearITPendingBit(DMA1_IT_HT3);

	}else if(DMA_GetITStatus(DMA1_IT_TC3)){

		DMA_ClearITPendingBit(DMA1_IT_TC3);
	}
}


void DMA1_Channel4_5_6_7_IRQHandler(void){

	if(DMA_GetITStatus(DMA1_IT_TC7)){

		USART_IRQ_Tx(USART_3);
		DMA_ClearITPendingBit(DMA1_IT_TC7);
	}

	if( DMA_GetITStatus(DMA1_IT_TE7)){

		DMA_ClearITPendingBit(DMA1_IT_TE7);

	}
	// RX
	if(DMA_GetITStatus(DMA1_IT_TC6)){

		//USART_IRQ_Rx(USART_3);
		DMA_ClearITPendingBit(DMA1_IT_TC6);
	}

	if(DMA_GetITStatus(DMA1_IT_TE6)){

		DMA_ClearITPendingBit(DMA1_IT_TE6);
	}
}


void TIM3_IRQHandler(void){

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){

		ISR_TimerUSART(USART_1);
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}


void TIM2_IRQHandler(void){

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		ISR_TimerUSART(USART_3);
	}
}


void USART1_IRQHandler(void){

	USART_IRQ_Rx(USART_1);
}

void USART3_4_IRQHandler(void){

	USART_IRQ_Rx(USART_3);
}

/* ------------------------------ End of file ------------------------------ */
