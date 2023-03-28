/*
 * GPS.c
 *
 *  Created on: 25 mar. 2023
 *      Author: Bruno
 */

#include "Global.h"
#include "GPS.h"

/*
 *
$GNGLL,,,,,,V,M*79
$GPGSA,A,1,,,,,,,,,,,,,25.5,25.5,25.5*02
$BDGSA,A,1,,,,,,,,,,,,,25.5,25.5,25.5*13
$GPGSV,1,1,00*79
$BDGSV,1,1,00*68
$GNRMC,,V,,,,,,,,,,M*4E
$GNVTG,,,,,,,,,M*2D
$GNZDA,,,,,,*56
$GPTXT,01,01,01,ANTENNA OPEN*25
$GNGGA,,,,,,0,00,25.5,,,,,,*64

$GNGGA,,,,,,0,00,25.5,,,,,,*64
$GNGLL,,,,,,V,M*79
$GPGSA,A,1,,,,,,,,,,,,,25.5,25.5,25.5*02
$BDGSA,A,1,,,,,,,,,,,,,25.5,25.5,25.5*13
$GPGSV,1,1,00*79
$BDGSV,1,1,00*68
$GNRMC,,V,,,,,,,,,,M*4E
$GNVTG,,,,,,,,,M*2D
$GNZDA,,,,,,*56
$GPTXT,01,01,01,ANTENNA OPEN*25

 */

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
