/*
 * Uart.h
 *
 *  Created on: 02/06/2018
 *      Author: HP
 */

#ifndef	portUSART_H_
#define portUSART_H_

#include "stm32f0xx.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_dma.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_it.h"
#include "stm32f0xx_tim.h"
#include "string.h"

#define	MAX_USARTS				2
#define	MAX_TX_BUFFERS			5
#define	MAX_RX_BUFFERS			5
#define	BUFF_SIZE				600

#define	USART_1					0
#define	USART_3					1


#define	USART_GPIO_TX_CLK		0
#define	USART_GPIO_RX_CLK		1
#define	USART_X_CLK				2
#define	USART_DMA_CLK			3
#define	USART_TX_GPIO_PORT		4
#define	USART_TX_SOURCE			5
#define	USART_TX_AF				6
#define	USART_RX_GPIO_PORT		7
#define	USART_RX_SOURCE			8
#define	USART_RX_AF				9
#define	USART_TX_PIN			10
#define	USART_RX_PIN			11
#define	USART_NUM				12
#define	USART_TX_DMA_CHANNEL	13
#define	USART_RX_DMA_CHANNEL	14
#define	USART_DMA_IRQ_TX		15
#define	USART_DMA_IRQ_RX		16
#define	USART_IRQn				17
#define	USART_TDR				18
#define	CLK_TIM_USART			19
#define	TIM_USART_NUM			20
#define	TIM_USART_IRQ			21
#define	DMA_TX_FLAG_TC			22
#define	DMA_TX_FLAG_TE			23
#define	DMA_RX_FLAG_TC			24
#define	DMA_RX_FLAG_TE			25
#define	USART_RDR				26

#define	ULTIMO_CAMPO_USART		27


typedef struct{

	uint8_t		Inicializada;
	uint8_t		Modo;
	uint8_t		PrioridadUSART;
	uint8_t		PrioridadDMA;

	uint8_t		Indice;
	uint8_t		Mensajes;
	uint8_t		Enviando;
	uint8_t		Error;

	uint16_t		UseTimer;
	uint16_t	Largo[MAX_RX_BUFFERS];

	uint32_t	Baudrate;

	uint8_t		BufferTX[MAX_TX_BUFFERS][128];
	uint8_t		LargoBufferTX[MAX_TX_BUFFERS];
	uint8_t		BufferRX[MAX_RX_BUFFERS][BUFF_SIZE];

} stportUSART __attribute__((aligned));

void portInitUSART(uint8_t Nro);

void USART_Config(uint8_t USARTx, uint8_t Mode, uint32_t Speed);
void portUSART_SendDMA(uint8_t Nro, uint8_t *Buffer, uint16_t Largo);
void USART_Queue_Message(uint8_t Nro, uint8_t *Buffer, uint8_t Buffsize);
uint8_t portUSART_SendQueueMessages(uint8_t Nro);
uint8_t	portUSART_Bussy(uint8_t Nro);
void portUSART_MessageSent(uint8_t Nro);
void USART_IRQ_Tx(uint8_t Nro);

uint8_t portUSART_HayDatosDisponibles(int Nro);
uint8_t *portUSART_ApuntoRespuesta(uint8_t Nro, uint16_t *Lenght);
void portUSART_BorroDatos(uint8_t Nro);

void USART_IRQ_Rx(uint8_t Nro);
void ISR_TimerUSART(uint8_t Nro);

#endif /* portUSART_H_ */
