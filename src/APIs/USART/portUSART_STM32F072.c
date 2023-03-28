/*
 * portUSART_STM32F072.c
 *
 *  Created on: 20/08/2019
 *      Author: BMP
 */

#include "portUSART_STM32F072.h"


const	uint32_t		USARTx[MAX_USARTS][ULTIMO_CAMPO_USART] = {
		/* USART 1*/
		//0						1						2						3							4						5
		{RCC_AHBPeriph_GPIOA, 	RCC_AHBPeriph_GPIOA, 	RCC_APB2Periph_USART1, 	RCC_AHBPeriph_DMA1,			GPIOA_BASE,				GPIO_PinSource9,
		//6						7						8						9							10						11							12
		 GPIO_AF_1,				GPIOA_BASE, 			GPIO_PinSource10, 		GPIO_AF_1, 					GPIO_Pin_9,				GPIO_Pin_10, 				USART1_BASE,
		//13					14						15						16							17						18
		 DMA1_Channel2_BASE, 	DMA1_Channel3_BASE, 	DMA1_Channel2_3_IRQn, 	DMA1_Channel2_3_IRQn, 		USART1_IRQn,			(uint32_t) (&(USART1->TDR)),
		//19					20						21						22							23						24							25
		 RCC_APB1Periph_TIM3,	TIM3_BASE, 				TIM3_IRQn, 				DMA1_FLAG_TC2, 				DMA1_FLAG_TE2, 			DMA1_FLAG_TC3, 				DMA1_FLAG_TE3,
		 // 26
		 (uint32_t) (&(USART1->RDR))},

		/* USART 3*/
		 //0					1						2						3							4						5
		{RCC_AHBPeriph_GPIOB, 	RCC_AHBPeriph_GPIOB, 	RCC_APB1Periph_USART3, 	RCC_AHBPeriph_DMA1,			GPIOB_BASE,				GPIO_PinSource10,
		 //6					7						8						9							10						11							12
		 GPIO_AF_4,				GPIOB_BASE, 			GPIO_PinSource11, 		GPIO_AF_4, 					GPIO_Pin_10,			GPIO_Pin_11,				USART3_BASE,
		 //13					14						15						16							17						18
		 DMA1_Channel7_BASE, 	DMA1_Channel6_BASE, 	DMA1_Channel4_5_6_7_IRQn,DMA1_Channel4_5_6_7_IRQn,	USART3_4_IRQn,			(uint32_t) (&(USART3->TDR)),
		 //19					20						21						22							23						24							25
		 RCC_APB1Periph_TIM2, 	TIM2_BASE, 				TIM2_IRQn,			 	DMA1_FLAG_TC7, 				DMA1_FLAG_TE7, 			DMA1_FLAG_TC6, 				DMA1_FLAG_TE6,
		 // 26
		 (uint32_t) (&(USART3->RDR))}
};

static	uint8_t			u8Index[MAX_USARTS] = {0, 0};
static	uint8_t			u8MessageSent[MAX_USARTS] = {0, 0};
static 	uint8_t			u8PendingMessages[MAX_USARTS] = {0, 0};


stportUSART 			stUsart[MAX_USARTS];
DMA_InitTypeDef 		DMA_InitStructure[MAX_USARTS];

static void RestartResetTimer(uint8_t Nro);


void USART_Config(uint8_t Nro, uint8_t Mode, uint32_t Speed){

	stUsart[Nro].Modo = Mode;
	stUsart[Nro].Baudrate = Speed;
	stUsart[Nro].PrioridadUSART = 3;
	stUsart[Nro].UseTimer = 0;
	stUsart[Nro].Inicializada = 0x3B;					// Marca de inicialización
}

void portInitUSART(uint8_t Nro){

	USART_InitTypeDef 		USART_InitStructure;
	GPIO_InitTypeDef 		GPIO_InitStructure;
	NVIC_InitTypeDef		NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;

	if(stUsart[Nro].Inicializada != 0x3B)				// assert para debug
		while(1);

	if(stUsart[Nro].Modo & USART_Mode_Tx)	RCC_AHBPeriphClockCmd(USARTx[Nro][USART_GPIO_TX_CLK], ENABLE);
	if(stUsart[Nro].Modo & USART_Mode_Rx)	RCC_AHBPeriphClockCmd(USARTx[Nro][USART_GPIO_RX_CLK], ENABLE);

	if(Nro == USART_1){

		RCC_APB2PeriphClockCmd(USARTx[Nro][USART_X_CLK], ENABLE);

	}else if (Nro == USART_3){

		RCC_APB1PeriphClockCmd(USARTx[Nro][USART_X_CLK], ENABLE);
	}

	RCC_AHBPeriphClockCmd(USARTx[Nro][USART_DMA_CLK], ENABLE);

	if(stUsart[Nro].Modo & USART_Mode_Tx)
		GPIO_PinAFConfig((GPIO_TypeDef *) USARTx[Nro][USART_TX_GPIO_PORT], (uint16_t) USARTx[Nro][USART_TX_SOURCE], (uint8_t) USARTx[Nro][USART_TX_AF]);

	if(stUsart[Nro].Modo & USART_Mode_Rx)
		GPIO_PinAFConfig((GPIO_TypeDef *) USARTx[Nro][USART_RX_GPIO_PORT], (uint16_t) USARTx[Nro][USART_RX_SOURCE], (uint8_t) USARTx[Nro][USART_RX_AF]);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	if(stUsart[Nro].Modo & USART_Mode_Tx){

		GPIO_InitStructure.GPIO_Pin = USARTx[Nro][USART_TX_PIN];
		GPIO_Init((GPIO_TypeDef *) USARTx[Nro][USART_TX_GPIO_PORT], &GPIO_InitStructure);
	}

	if(stUsart[Nro].Modo & USART_Mode_Rx){

		GPIO_InitStructure.GPIO_Pin = USARTx[Nro][USART_RX_PIN];
		GPIO_Init((GPIO_TypeDef *) USARTx[Nro][USART_RX_GPIO_PORT], &GPIO_InitStructure);
	}

	/*

	 if(stUsart[Nro].Modo & USART_Mode_Rx){

		RCC_APB1PeriphClockCmd(USARTx[Nro][CLK_TIM_USART], ENABLE);

		// Timer 48Mhz / 2 -> 65535 / 24Mhz = 2.7mS max
		TIM_TimeBaseStructure.TIM_Prescaler = 53;		// 2 * 2.7ms = 5.4ms
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit((TIM_TypeDef *) USARTx[Nro][TIM_USART_NUM], &TIM_TimeBaseStructure);

		NVIC_InitStructure.NVIC_IRQChannel = USARTx[Nro][TIM_USART_IRQ];
		NVIC_InitStructure.NVIC_IRQChannelPriority = 0x05;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		NVIC_DisableIRQ(USARTx[Nro][TIM_USART_IRQ]);

		TIM_Cmd((TIM_TypeDef *) USARTx[Nro][TIM_USART_NUM], ENABLE);
		TIM_ITConfig((TIM_TypeDef *) USARTx[Nro][TIM_USART_NUM], TIM_IT_Update, ENABLE);


		NVIC_InitStructure.NVIC_IRQChannel = USARTx[Nro][USART_IRQn];
		NVIC_InitStructure.NVIC_IRQChannelPriority = 0x04;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = USARTx[Nro][USART_DMA_IRQ_RX];
		NVIC_InitStructure.NVIC_IRQChannelPriority = 0x03;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
	*/

//	// Configuro Interrupciones
//	NVIC_InitStructure.NVIC_IRQChannel = USARTx[Nro][USART_DMA_IRQ_TX];
//	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x03;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

	/* USART Config */
	USART_InitStructure.USART_BaudRate = stUsart[Nro].Baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = stUsart[Nro].Modo;
	USART_Init((USART_TypeDef *) USARTx[Nro][USART_NUM], &USART_InitStructure);

	USART_Cmd((USART_TypeDef *) USARTx[Nro][USART_NUM], ENABLE);

	DMA_DeInit((DMA_Channel_TypeDef *) USARTx[Nro][USART_TX_DMA_CHANNEL]);

	/* DMA Config */
	DMA_InitStructure[Nro].DMA_PeripheralBaseAddr = USARTx[Nro][USART_TDR];
	DMA_InitStructure[Nro].DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure[Nro].DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure[Nro].DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure[Nro].DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure[Nro].DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure[Nro].DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure[Nro].DMA_M2M = DMA_M2M_Disable;

	// TX
	DMA_InitStructure[Nro].DMA_BufferSize = BUFF_SIZE;
	DMA_InitStructure[Nro].DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure[Nro].DMA_MemoryBaseAddr = (uint32_t)stUsart[Nro].BufferTX[0];
	DMA_Init((DMA_Channel_TypeDef *)  USARTx[Nro][USART_TX_DMA_CHANNEL], &DMA_InitStructure[Nro]);

	if(stUsart[Nro].Modo & USART_Mode_Rx){

		NVIC_InitStructure.NVIC_IRQChannel = USARTx[Nro][USART_IRQn];
		NVIC_InitStructure.NVIC_IRQChannelPriority = 0x04;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		DMA_DeInit((DMA_Channel_TypeDef *) USARTx[Nro][USART_RX_DMA_CHANNEL]);

		// RX
		DMA_InitStructure[Nro].DMA_BufferSize = BUFF_SIZE;
		DMA_InitStructure[Nro].DMA_DIR = DMA_DIR_PeripheralSRC;
		DMA_InitStructure[Nro].DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure[Nro].DMA_PeripheralBaseAddr = USARTx[Nro][USART_RDR];
		DMA_InitStructure[Nro].DMA_MemoryBaseAddr = (uint32_t) stUsart[Nro].BufferRX[0];
		DMA_Init((DMA_Channel_TypeDef *)  USARTx[Nro][USART_RX_DMA_CHANNEL], &DMA_InitStructure[Nro]);

		DMA_Cmd((DMA_Channel_TypeDef *) USARTx[Nro][USART_RX_DMA_CHANNEL], ENABLE);

		//DMA_ITConfig((DMA_Channel_TypeDef *) USARTx[Nro][USART_RX_DMA_CHANNEL], DMA_IT_TC, ENABLE);
		//DMA_ITConfig((DMA_Channel_TypeDef *) USARTx[Nro][USART_RX_DMA_CHANNEL], DMA_IT_TE, ENABLE);

		USART_ClearFlag((USART_TypeDef *) USARTx[Nro][USART_NUM], USARTx[Nro][DMA_RX_FLAG_TC]);
		USART_ClearFlag((USART_TypeDef *) USARTx[Nro][USART_NUM], USARTx[Nro][DMA_RX_FLAG_TE]);
		USART_ClearFlag((USART_TypeDef *)USARTx[Nro][USART_NUM], USART_FLAG_IDLE);

		USART_ITConfig((USART_TypeDef *)USARTx[Nro][USART_NUM], USART_IT_IDLE, ENABLE);
		USART_ClearITPendingBit((USART_TypeDef *)USARTx[Nro][USART_NUM], USART_IT_IDLE);

		USART_DMACmd((USART_TypeDef *) USARTx[Nro][USART_NUM], USART_DMAReq_Rx, ENABLE);
	}
}


void portUSART_SendDMA(uint8_t Nro, uint8_t *Buffer, uint16_t Largo){

	stUsart[Nro].Enviando = 1;

	DMA_DeInit((DMA_Channel_TypeDef *) USARTx[Nro][USART_TX_DMA_CHANNEL]);

	// Canal de envio

	DMA_InitStructure[Nro].DMA_BufferSize = Largo;
	DMA_InitStructure[Nro].DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure[Nro].DMA_PeripheralBaseAddr = USARTx[Nro][USART_TDR];
	DMA_InitStructure[Nro].DMA_MemoryBaseAddr = (uint32_t)Buffer;
	DMA_Init((DMA_Channel_TypeDef *)  USARTx[Nro][USART_TX_DMA_CHANNEL], &DMA_InitStructure[Nro]);

	DMA_ClearFlag(USARTx[Nro][DMA_TX_FLAG_TC]);
	DMA_ClearFlag(USARTx[Nro][DMA_TX_FLAG_TE]);

	USART_DMACmd((USART_TypeDef *) USARTx[Nro][USART_NUM], USART_DMAReq_Tx, ENABLE);
	DMA_ITConfig((DMA_Channel_TypeDef *)  USARTx[Nro][USART_TX_DMA_CHANNEL], DMA_IT_TC | DMA_IT_TE, ENABLE);
	DMA_Cmd((DMA_Channel_TypeDef *) USARTx[Nro][USART_TX_DMA_CHANNEL], ENABLE);
}


void USART_Queue_Message(uint8_t Nro, uint8_t *Buffer, uint8_t Buffsize){

	if(!Buffsize)
		return;

	if(Buffsize > BUFF_SIZE)
		while(1);					// Detengo para poder depurar

	u8PendingMessages[Nro]++;

	memcpy(stUsart[Nro].BufferTX[u8Index[Nro]], Buffer, Buffsize);

	stUsart[Nro].LargoBufferTX[u8Index[Nro]++] = Buffsize;

	if(u8Index[Nro] == MAX_TX_BUFFERS){

		u8Index[Nro] = 0;
	}
}

uint8_t portUSART_SendQueueMessages(uint8_t Nro){

	uint8_t	Index = 0;

	if(u8PendingMessages[Nro]){

		if(u8Index[Nro] < u8PendingMessages[Nro])
			Index = MAX_TX_BUFFERS - u8PendingMessages[Nro];
		else
			Index = u8Index[Nro] - u8PendingMessages[Nro];

		portUSART_SendDMA(Nro, stUsart[Nro].BufferTX[Index], stUsart[Nro].LargoBufferTX[Index]);
		return 1;
	}

	return 0;
}

uint8_t	portUSART_Bussy(uint8_t Nro){

	return u8MessageSent[Nro];
}

void portUSART_MessageSent(uint8_t Nro){

	u8MessageSent[Nro] = 0;
	if(u8PendingMessages[Nro])
		u8PendingMessages[Nro]--;
}


void USART_IRQ_Tx(uint8_t Nro){

	u8MessageSent[Nro] = 1;
}

/* Recepción */


uint8_t portUSART_HayDatosDisponibles(int Nro){

	return stUsart[Nro].Mensajes;
}

uint8_t *portUSART_ApuntoRespuesta(uint8_t Nro, uint16_t *Lenght){

	uint8_t	Indice;

	if(stUsart[Nro].Indice >= stUsart[Nro].Mensajes){

		Indice = (stUsart[Nro].Indice - stUsart[Nro].Mensajes);
		*Lenght = stUsart[Nro].Largo[Indice];
		return stUsart[Nro].BufferRX[Indice];

	}else{

		Indice = (MAX_RX_BUFFERS - stUsart[Nro].Mensajes + stUsart[Nro].Indice);
		*Lenght = stUsart[Nro].Largo[Indice];
		return stUsart[Nro].BufferRX[Indice];
	}
}

void portUSART_BorroDatos(uint8_t Nro){

	if(stUsart[Nro].Mensajes)
		stUsart[Nro].Mensajes--;
}

void USART_IRQ_Rx(uint8_t Nro){

	uint16_t			Largo;
	DMA_Channel_TypeDef	*DMAx;

	USART_ClearFlag((USART_TypeDef *) USARTx[Nro][USART_NUM], USARTx[Nro][DMA_RX_FLAG_TC]);
	USART_ClearFlag((USART_TypeDef *) USARTx[Nro][USART_NUM], USARTx[Nro][DMA_RX_FLAG_TE]);

	if(USART_GetITStatus((USART_TypeDef *) USARTx[Nro][USART_NUM], USART_IT_IDLE)){

		USART_ClearITPendingBit((USART_TypeDef *) USARTx[Nro][USART_NUM], USART_IT_IDLE);

		if(stUsart[Nro].UseTimer == 0){

			GPIO_ToggleBits(GPIOB, GPIO_Pin_2);
			DMAx = (DMA_Channel_TypeDef	*)(USARTx[Nro][USART_RX_DMA_CHANNEL]);

			DMA_Cmd((DMA_Channel_TypeDef *) USARTx[Nro][USART_RX_DMA_CHANNEL], DISABLE);

			//stUsart[Nro].Indice++;
			stUsart[Nro].Error = 0; // ??

			stUsart[Nro].Mensajes++;
			Largo = BUFF_SIZE - DMAx->CNDTR;
			stUsart[Nro].Largo[stUsart[Nro].Indice] = BUFF_SIZE - DMAx->CNDTR;

			// Canal de recepcion
			DMA_InitStructure[Nro].DMA_BufferSize = BUFF_SIZE;
			DMA_InitStructure[Nro].DMA_DIR = DMA_DIR_PeripheralSRC;
			DMA_InitStructure[Nro].DMA_MemoryInc = DMA_MemoryInc_Enable;
			DMA_InitStructure[Nro].DMA_PeripheralBaseAddr = USARTx[Nro][USART_RDR];

			//stUsart[Nro].BufferRX[stUsart[Nro].Indice][Largo] = '\0';

			if(++stUsart[Nro].Indice == MAX_RX_BUFFERS)
				stUsart[Nro].Indice = 0;

			DMA_InitStructure[Nro].DMA_MemoryBaseAddr = (uint32_t)stUsart[Nro].BufferRX[stUsart[Nro].Indice];
			DMA_Init((DMA_Channel_TypeDef *) USARTx[Nro][USART_RX_DMA_CHANNEL], &DMA_InitStructure[Nro]);

			DMA_Cmd((DMA_Channel_TypeDef *) USARTx[Nro][USART_RX_DMA_CHANNEL], ENABLE);

			//USART_ReceiveData(USART1);

		}else{

			RestartResetTimer(Nro);
		}

		//USART_ReceiveData((USART_TypeDef *) USARTx[Nro][USART_NUM]);
		USART_ClearITPendingBit((USART_TypeDef *) USARTx[Nro][USART_NUM], USART_IT_IDLE);
	}
}


static void RestartResetTimer(uint8_t Nro){

	GPIO_SetBits(GPIOB, GPIO_Pin_2);

	TIM_SetCounter((TIM_TypeDef *) USARTx[Nro][TIM_USART_NUM], 0x0000);

	TIM_ClearITPendingBit((TIM_TypeDef *) USARTx[Nro][TIM_USART_NUM], TIM_IT_Update);

	NVIC_EnableIRQ((IRQn_Type) USARTx[Nro][TIM_USART_IRQ]);
}


void ISR_TimerUSART(uint8_t Nro){

	uint16_t				Largo;
	DMA_Channel_TypeDef		*DMAx;

	GPIO_ResetBits(GPIOB, GPIO_Pin_2);

	DMAx = (DMA_Channel_TypeDef	*)(USARTx[Nro][USART_RX_DMA_CHANNEL]);

	NVIC_DisableIRQ((IRQn_Type) USARTx[Nro][TIM_USART_IRQ]);

	DMA_Cmd((DMA_Channel_TypeDef *) USARTx[Nro][USART_RX_DMA_CHANNEL], DISABLE);

	//stUsart[Nro].Indice++;
	stUsart[Nro].Error = 0; // ??

	stUsart[Nro].Mensajes++;
	Largo = stUsart[Nro].Largo[stUsart[Nro].Indice] = BUFF_SIZE - DMAx->CNDTR;

	DMA_InitStructure[Nro].DMA_BufferSize = BUFF_SIZE;
	DMA_InitStructure[Nro].DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure[Nro].DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure[Nro].DMA_PeripheralBaseAddr = USARTx[Nro][USART_RDR];

	stUsart[Nro].BufferRX[stUsart[Nro].Indice][Largo] = '\0';

	if(++stUsart[Nro].Indice == MAX_RX_BUFFERS)
		stUsart[Nro].Indice = 0;

	DMA_InitStructure[Nro].DMA_MemoryBaseAddr = (uint32_t)stUsart[Nro].BufferRX[stUsart[Nro].Indice];
	DMA_Init((DMA_Channel_TypeDef *) USARTx[Nro][USART_RX_DMA_CHANNEL], &DMA_InitStructure[Nro]);

	DMA_Cmd((DMA_Channel_TypeDef *) USARTx[Nro][USART_RX_DMA_CHANNEL], ENABLE);
}

