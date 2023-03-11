#include "Lectura ADCs.h"

#define NUMBER_OF_CONVERTIONS		3


static uint8_t		ConversionLista = 0;
static uint16_t		ConversorADC[NUMBER_OF_CONVERTIONS + 1];

EntradasAnalogicas	ADCs;

static void ADC_TIM_DMA_Config(void);
static void adcNVIC_Config(void);

void procesoADCs(void){

	if (!ConversionLista) 						// Si el bit mas significativo esta en 1 hay dato
		return; 								// Sino me voy

	ConversionLista = 0; 						// Borro flag de conversion disponible

	memcpy(&ADCs, ConversorADC, sizeof(ADCs));
}



void initADC(void){

	adcNVIC_Config();

	ADC_TIM_DMA_Config();
}

static void adcNVIC_Config(void){

	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable and set DMA1_Channel1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


static void ADC_TIM_DMA_Config(void){

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	/* ADC1 DeInit */
	ADC_DeInit(ADC1);

	/* ADC1 Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_TIM1, ENABLE);

	/* DMA1 clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	/* TIM2 Configuration */
	TIM_DeInit(TIM1);

	/* Time base configuration */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t)((SystemCoreClock / 1000000) - 1); 	// 1 MHz, from 48 MHz
	TIM_TimeBaseStructure.TIM_Period = 100 - 1; 										// 100 Hz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/* Output Compare PWM Mode configuration */
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 									/* low edge by default */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0x01;
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	/* TIM1 enable counter */
	TIM_Cmd(TIM1, ENABLE);

	/* Main Output Enable */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);

	/* DMA1 Channel1 Config */
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ConversorADC[0];
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = NUMBER_OF_CONVERTIONS;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	/* DMA1 Channel1 enable */
	DMA_Cmd(DMA1_Channel1, ENABLE);

	/* ADC DMA request in circular mode */
	ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);

	/* Enable DMA1 Channel1 Half Transfer and Transfer Complete interrupt */
	//	DMA_ITConfig(DMA1_Channel1, DMA_IT_HT, ENABLE);
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);

	/* Enable ADC_DMA */
	ADC_DMACmd(ADC1, ENABLE);

	/* Initialize ADC structure */
	ADC_StructInit(&ADC_InitStructure);

	/* Configure the ADC1 in continous mode withe a resolutuion equal to 12 bits  */
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
	ADC_InitStructure.ADC_ExternalTrigConv =  ADC_ExternalTrigConv_T1_CC4;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
	ADC_Init(ADC1, &ADC_InitStructure);

	/* Convert the  ADC_Channnel_1  with 7.5 Cycles as sampling time */
	ADC_ChannelConfig(ADC1, ADC_Channel_1 , ADC_SampleTime_71_5Cycles);				// PA2: Sensor presion

	/* Convert the  ADC_Channnel_2  with 7.5 Cycles as sampling time */
	ADC_ChannelConfig(ADC1, ADC_Channel_2 , ADC_SampleTime_71_5Cycles);				// PA2: Sensor presion

	/* Convert the  ADC_Channnel_3  with 7.5 Cycles as sampling time */
	ADC_ChannelConfig(ADC1, ADC_Channel_3 , ADC_SampleTime_71_5Cycles);				// PA3: Sensor humo

	/* ADC Calibration */
	ADC_GetCalibrationFactor(ADC1);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Wait the ADCEN flag */
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN));

	/* ADC1 regular Software Start Conv */
	ADC_StartOfConversion(ADC1);
}


void ADC_InterruptRoutine(void){

	ConversionLista = 1;
}
