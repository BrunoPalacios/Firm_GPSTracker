/*
 * DAC.c
 *
 *  Created on: 27/02/2019
 *      Author: HP
 */

#include "stm32f0xx.h"

#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_dma.h"
#include "stm32f0xx_dac.h"
#include "stm32f0xx_misc.h"
#include "stm32f0xx_it.h"

#include "DAC.h"

static	uint8_t					DACListo = 0;

static 	DAC_InitTypeDef    	 	DAC_InitStructure;
static	DMA_InitTypeDef     	DMA_InitStructure;
static 	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;


void initDAC(void){

	GPIO_InitTypeDef 		GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	DAC_DeInit();

	/* DAC channel1 Configuration */
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;

	DAC_Init(DAC_Channel_1, &DAC_InitStructure);					// PA4

	DAC_Cmd(DAC_Channel_1, ENABLE);									/* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is automatically connected to the DAC converter. */
}

void initDAC_DMA(void){

	GPIO_InitTypeDef 		GPIO_InitStructure;
	NVIC_InitTypeDef		NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	DAC_DeInit();

	/* DAC channel1 Configuration */
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;

	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR8R1_ADDRESS;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

	// Configuro Interrupciones
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);
	DMA_ITConfig(DMA1_Channel3, DMA_IT_HT, ENABLE);
	DMA_ITConfig(DMA1_Channel3, DMA_IT_TE, ENABLE);

}


void procesarDAC_DMA(uint8_t *Buffer, uint16_t Largo, uint32_t Frecuencia){

	DACListo = 0;

	/* Time base configuration */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = (48000000 / Frecuencia);		// 8K sample
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* TIM2 TRGO selection */
	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);

	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);

	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) Buffer;
	DMA_InitStructure.DMA_BufferSize = Largo;
	DMA_Init(DMA1_Channel3, &DMA_InitStructure);

	DMA_Cmd(DMA1_Channel3, ENABLE);

	DAC_Init(DAC_Channel_1, &DAC_InitStructure);					// PA4

	DAC_Cmd(DAC_Channel_1, ENABLE);											/* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is automatically connected to the DAC converter. */

	DAC_DMACmd(DAC_Channel_1, ENABLE);
}

void detenerDAC_DMA(void){

	/* TIM2 enable counter */
	TIM_Cmd(TIM2, DISABLE);

	DMA_Cmd(DMA1_Channel3, DISABLE);

	DAC_Init(DAC_Channel_1, &DAC_InitStructure);					// PA4

	DAC_Cmd(DAC_Channel_1, DISABLE);											/* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is automatically connected to the DAC converter. */

	DAC_DMACmd(DAC_Channel_1, DISABLE);
}

uint8_t	portDACDMA_Ready(void){

	return DACListo;
}

void DAC_DMA_ISR(void){

	DACListo = 1;
}


