/*
 * portSPI.c
 *
 *  Created on: 26/02/2019
 *      Author: HP
 */

#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "portSPI.h"

uint32_t SPI[CANTIDAD_SPIs][ULTIMO_CAMPO_SPI] = {

		{RCC_AHBPeriph_GPIOA, RCC_APB2Periph_SPI1, GPIOA_BASE, GPIO_PinSource5, GPIO_PinSource6, GPIO_PinSource7, GPIO_AF_0, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7, SPI1_BASE},
		{RCC_AHBPeriph_GPIOB, RCC_APB1Periph_SPI2, GPIOB_BASE, GPIO_PinSource13, GPIO_PinSource14, GPIO_PinSource15, GPIO_AF_0, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15, SPI2_BASE},

};



void initSPI(uint8_t spiNum){

	GPIO_InitTypeDef 	GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	RCC_AHBPeriphClockCmd(SPI[spiNum][CLOCK_PUERTO], ENABLE);

	if(!spiNum)
		RCC_APB2PeriphClockCmd(SPI[spiNum][CLOCK_SPI], ENABLE);
	else
		RCC_APB1PeriphClockCmd(SPI[spiNum][CLOCK_SPI], ENABLE);

	GPIO_PinAFConfig((GPIO_TypeDef *) SPI[spiNum][SPI_PUERTO], SPI[spiNum][SPI_PINSOURCE_SCK], SPI[spiNum][SPI_GPIO_AF]);
	GPIO_PinAFConfig((GPIO_TypeDef *) SPI[spiNum][SPI_PUERTO], SPI[spiNum][SPI_PINSOURCE_MISO], SPI[spiNum][SPI_GPIO_AF]);
	GPIO_PinAFConfig((GPIO_TypeDef *) SPI[spiNum][SPI_PUERTO], SPI[spiNum][SPI_PINSOURCE_MOSI], SPI[spiNum][SPI_GPIO_AF]);

	GPIO_InitStructure.GPIO_Pin = SPI[spiNum][SPI_GPIO_PIN_SCK] | SPI[spiNum][SPI_GPIO_PIN_MISO] | SPI[spiNum][SPI_GPIO_PIN_MOSI];
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef *) SPI[spiNum][SPI_PUERTO], &GPIO_InitStructure);

	SPI_I2S_DeInit((SPI_TypeDef *) SPI[spiNum][SPI_NUMERO]);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init((SPI_TypeDef *) SPI[spiNum][SPI_NUMERO], &SPI_InitStructure);

	SPI_Cmd((SPI_TypeDef *) SPI[spiNum][SPI_NUMERO], ENABLE);
}



void spiSpeed(uint8_t spiNum, uint16_t Preescaler, uint16_t CPOL, uint16_t CPHA){

	SPI_InitTypeDef  SPI_InitStructure;

	SPI_Cmd((SPI_TypeDef *) SPI[spiNum][SPI_NUMERO], DISABLE);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = CPOL;
	SPI_InitStructure.SPI_CPHA = CPHA;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = Preescaler;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init((SPI_TypeDef *) SPI[spiNum][SPI_NUMERO], &SPI_InitStructure);

	SPI_Cmd((SPI_TypeDef *) SPI[spiNum][SPI_NUMERO], ENABLE);
}



uint8_t SPI_ReadWrite_Byte(uint8_t spiNum, unsigned char byte){

	while (SPI_I2S_GetFlagStatus((SPI_TypeDef *) SPI[spiNum][SPI_NUMERO], SPI_I2S_FLAG_TXE) == RESET); //wait buffer empty

	SPI_SendData8((SPI_TypeDef *) SPI[spiNum][SPI_NUMERO], byte);

	while (SPI_I2S_GetFlagStatus((SPI_TypeDef *) SPI[spiNum][SPI_NUMERO], SPI_I2S_FLAG_BSY) == SET); //wait finish sending

	//while (SPI_I2S_GetFlagStatus((SPI_TypeDef *) SPI[spiNum][SPI_NUMERO], SPI_I2S_FLAG_RXNE) == RESET); //wait finish sending

	return SPI_ReceiveData8((SPI_TypeDef *) SPI[spiNum][SPI_NUMERO]);
}
