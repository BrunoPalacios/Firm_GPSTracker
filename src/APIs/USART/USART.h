/*
 * Uart.h
 *
 *  Created on: 02/06/2018
 *      Author: HP
 */

#ifndef USART_H_
#define USART_H_

#include "stm32f0xx.h"
#include "portUSART_STM32F072.h"

#define	MAX_ESPERA_ENVIO_USART	50 //ms

typedef enum {

	USART_Initialize = 0,
	USART_Send_Data,
	USART_Wait,

} teUSARTState;


void USARTTask(void);
#endif /* USART_H_ */
