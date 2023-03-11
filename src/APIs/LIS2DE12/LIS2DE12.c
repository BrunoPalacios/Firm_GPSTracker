#include "LIS2DE12.h"
#include "main.h"

#define	ACEL_CS_PORT	GPIOA
#define	ACEL_CS_PIN		GPIO_Pin_9

uint8_t	WHOAMI = 0;

void initLIS2(void){

	spiSpeed(1, SPI_BaudRatePrescaler_256, SPI_CPOL_High, SPI_CPHA_2Edge);

	Delay_ms(10);

	GPIO_ResetBits(ACEL_CS_PORT, ACEL_CS_PIN);
	Delay_ms(2);
	SPI_ReadWrite_Byte(1, 0x23);
	WHOAMI = SPI_ReadWrite_Byte(1, 0x00);
	Delay_ms(2);
	GPIO_SetBits(ACEL_CS_PORT, ACEL_CS_PIN);

	GPIO_ResetBits(ACEL_CS_PORT, ACEL_CS_PIN);
	Delay_ms(2);
	SPI_ReadWrite_Byte(1, 0x8F);
	WHOAMI = SPI_ReadWrite_Byte(1, 0xFF);
	Delay_ms(2);
	GPIO_SetBits(ACEL_CS_PORT, ACEL_CS_PIN);
}
