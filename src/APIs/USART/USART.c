/*
 * Usart.c
 *
 *  Created on: 02/06/2018
 *      Author: BMP
 */

#include "USART.h"

static	uint32_t		u32LocalSystick;


void USARTTask(void){

	static	teUSARTState	USARTState = 0;

	switch(USARTState){

	case USART_Initialize:

		USART_Config(USART_3, USART_Mode_Tx | USART_Mode_Rx, 115200);
		portInitUSART(USART_3);
		USARTState = USART_Send_Data;

		break;

	case USART_Send_Data:

		if(portUSART_SendQueueMessages(USART_3)){

			u32LocalSystick = getSystick();
			USARTState = USART_Wait;
		}

		break;

	case USART_Wait:

		if(portUSART_Bussy(USART_3) || (getSystick() - u32LocalSystick) > MAX_ESPERA_ENVIO_USART){

			portUSART_MessageSent(USART_3);
			USARTState = USART_Send_Data;
		}

		break;

	default:

		break;
	}
}

