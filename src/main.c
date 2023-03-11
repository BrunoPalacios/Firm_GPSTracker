/*
 *  --------------------------------------------------------------------------
 *
 *                              GPS Tracker
 *                               ----------------
 *
 *                      Copyright (C) 2023 Embels Ingeniería
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
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "Pinout.h"
#include "APIs/ADCs/Lectura ADCs.h"
#include "USART.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define	BUFF_SIZE			256

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
void Delay_ms(uint32_t Delay);
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/* ---------------------------- Local functions ---------------------------- */
void initIOs(void){

	uint8_t					i = 0;
	uint8_t					j = 0;
	GPIO_InitTypeDef		GPIO;

	for(j = 0; j < PUERTOS; j++){

		for(i = 0; i < PINES; i++){

			if(Pin[j][i][CONFIG] == 1){

				GPIO.GPIO_Pin = (uint32_t) Pin[j][i][PIN];
				GPIO.GPIO_Mode = (GPIOMode_TypeDef) Pin[j][i][MODO];
				GPIO.GPIO_OType = (GPIOOType_TypeDef) Pin[j][i][OTYPE];
				GPIO.GPIO_PuPd = (GPIOPuPd_TypeDef) Pin[j][i][PUPD];
				GPIO.GPIO_Speed = (GPIOSpeed_TypeDef) Pin[j][i][SPEED];

				GPIO_Init((GPIO_TypeDef *) Puerto[j], &GPIO);
			}
		}
	}
}

/* ---------------------------- Global functions --------------------------- */

int main(int argc, char *argv[]){

	char			Buffer[512];

	uint8_t			*BufferUSART = NULL;

	uint16_t		i = 0;
	uint16_t		LargoUSART = 0;

	uint32_t		LocalSystick = 0;
	uint32_t		LocalSystick2 = 0;

	SysTick_Config(SystemCoreClock / 1000);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, DISABLE);						// Reduce consumption
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);

	initIOs();

	initADC();

	while(1){

		USARTTask();

		procesoADCs();

		if(portUSART_HayDatosDisponibles(USART_3)){

			BufferUSART = portUSART_ApuntoRespuesta(USART_3, &LargoUSART);

			sprintf(Buffer, "Recibi: %s\r\n", (char *) BufferUSART);
			USART_Queue_Message(USART_3, (uint8_t *) Buffer, strlen(Buffer));

			portUSART_BorroDatos(USART_3);
		}
	}

	return 0; // Never reach here
}


void Delay_ms(uint32_t Delay){

	uint32_t LocalSystick = getSystick();

	while(getSystick() - LocalSystick < Delay);

}

void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){

	GPIOx->ODR ^= GPIO_Pin;
}

/* ------------------------------ End of file ------------------------------ */
