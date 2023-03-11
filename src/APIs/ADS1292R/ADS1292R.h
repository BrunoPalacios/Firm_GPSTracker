/* 
 * File:   LIS2DE12.h
 * Author: Bruno
 *
 */

#ifndef ADS1292R_H_
#define	ADS1292R_H_

#ifdef	__cplusplus
extern "C" {
#endif

#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "portSPI.h"

#define CONFIG_SPI_MASTER_DUMMY   0xFF		// Envío tonto

// Register Read Commands
#define RREG					0x20;		//Read n nnnn registers starting at address r rrrr
											//first byte 001r rrrr (2xh)(2) - second byte 000n nnnn(2)

#define WREG    				0x40;		//Write n nnnn registers starting at address r rrrr
											//first byte 010r rrrr (2xh)(2) - second byte 000n nnnn(2)

#define CMD_START				0x08		//Start/restart (synchronize) conversions
#define CMD_STOP				0x0A		//Stop conversion
#define CMD_RDATAC 				0x10		//Enable Read Data Continuous mode.

//This mode is the default mode at power-up.
#define SDATAC					0x11		//Stop Read Data Continuously mode
#define RDATA					0x12		//Read data by command; supports multiple read back.

//register address
#define ADS1292_REG_ID			0x00
#define ADS1292_REG_CONFIG1		0x01
#define ADS1292_REG_CONFIG2		0x02
#define ADS1292_REG_LOFF		0x03
#define ADS1292_REG_CH1SET		0x04
#define ADS1292_REG_CH2SET		0x05
#define ADS1292_REG_RLDSENS		0x06
#define ADS1292_REG_LOFFSENS    0x07
#define ADS1292_REG_LOFFSTAT    0x08
#define ADS1292_REG_RESP1	    0x09
#define ADS1292_REG_RESP2	    0x0A



#define	ADS_CLK_PORT	GPIOB
#define	ADS_CLK_PIN		GPIO_Pin_5

#define	ADS_CS_PORT		GPIOB
#define	ADS_CS_PIN		GPIO_Pin_6

#define	ADS_START_PORT	GPIOB
#define	ADS_START_PIN	GPIO_Pin_7

#define	ADS_RESET_PORT	GPIOB
#define	ADS_RESET_PIN	GPIO_Pin_8

#define	ADS_DRDY_PORT	GPIOB
#define	ADS_DRDY_PIN	GPIO_Pin_9

void initADS1292R(void);
void procesoADS1292R(void);

#ifdef	__cplusplus
}
#endif

#endif

