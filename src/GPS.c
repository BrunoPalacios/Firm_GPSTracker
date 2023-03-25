/*
 * GPS.c
 *
 *  Created on: 25 mar. 2023
 *      Author: Bruno
 */

#include "Global.h"
#include "GPS.h"


void GPSTask(stGeneral *Gen){

	uint8_t				*pu8BufferUSART;
	uint16_t			u16LargoUSART;

	static teGPState	enGPSState = GPS_Initialize;
	static	uint32_t	u32LocalSystick;

	switch(enGPSState){

	case GPS_Initialize:

		GPIO_SetBits(GPS_RESET_PORT, GPS_RESET_PIN);
		GPIO_SetBits(GPS_ONOFF_PORT, GPS_ONOFF_PIN);

		USART_Config(USART_1, USART_Mode_Tx | USART_Mode_Rx, 9600);
		portInitUSART(USART_1);

		enGPSState = GPS_Receive;

		break;

	case GPS_Receive:

		if(portUSART_HayDatosDisponibles(USART_1)){

			pu8BufferUSART = portUSART_ApuntoRespuesta(USART_1, &u16LargoUSART);

			portUSART_BorroDatos(USART_1);
		}

		break;

	case GPS_Wait:

		break;

	default:

		enGPSState = GPS_Initialize;
		break;
	}
}
