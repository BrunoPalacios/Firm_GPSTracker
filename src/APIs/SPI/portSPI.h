/*
 * portSPI.h
 *
 *  Created on: 26/02/2019
 *      Author: HP
 */

#ifndef FATFS_PORTSPI_H_
#define FATFS_PORTSPI_H_

#include "stm32f0xx_spi.h"
#include "IOConfig.h"

#define	CANTIDAD_SPIs		2

#define	CLOCK_PUERTO		0
#define	CLOCK_SPI			1
#define	SPI_PUERTO			2
#define	SPI_PINSOURCE_SCK	3
#define	SPI_PINSOURCE_MISO	4
#define	SPI_PINSOURCE_MOSI	5
#define	SPI_GPIO_AF			6
#define	SPI_GPIO_PIN_SCK	7
#define	SPI_GPIO_PIN_MISO	8
#define	SPI_GPIO_PIN_MOSI	9
#define	SPI_NUMERO			10

#define	ULTIMO_CAMPO_SPI	11

//#define	SPI_LowSpeed(a)		spiSpeed(a, 0x0038)
//#define	SPI_HighSpeed(a)	spiSpeed(a, 0x0008)

void initSPI(uint8_t spiNum);
void spiSpeed(uint8_t spiNum, uint16_t Preescaler, uint16_t CPOL, uint16_t CPHA);
uint8_t SPI_ReadWrite_Byte(uint8_t spiNum, unsigned char byte);

#endif /* FATFS_PORTSPI_H_ */
