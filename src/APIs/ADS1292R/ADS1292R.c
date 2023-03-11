#include <APIs/ADS1292R/ADS1292R.h>
#include "portSPI.h"
#include "main.h"
#include "portUSART_STM32F072.h"
#include "string.h"

static uint8_t ADS1292R_Write (uint8_t data);
static void ADS1292_Write_Cmd(uint8_t READ_ADDRESS, uint8_t DATA);

void procesoADS1292R(void){

	uint8_t		Buffer[6];
	uint8_t		i = 0;
	uint8_t 	ECG_Byte;
	uint8_t		SPI_Buff[9];								// ECG_Byte (Lectura ECG). SPI_Buff (Buffer SPI)

	int32_t 	ECG_Data_32;								// ECG_Data_32 (Variable ECG 32 Bit)
	int32_t 	Respiracion;

	if(GPIO_ReadInputDataBit(ADS_DRDY_PORT, ADS_DRDY_PIN) == Bit_RESET){

		spiSpeed(1, SPI_BaudRatePrescaler_16, SPI_CPOL_Low, SPI_CPHA_2Edge);	// Antes de usar reconfiguro SPI por si alguien lo cambió

		GPIO_ResetBits(ADS_CS_PORT, ADS_CS_PIN); 					// enable device
		//Delay_ms(1);

		for (i = 0; i < 9; i++){

			SPI_Buff[i] = SPI_ReadWrite_Byte(1, 0x00);
		}

		GPIO_SetBits(ADS_CS_PORT, ADS_CS_PIN);						// disable device

		ECG_Byte = 0;
		ECG_Data_32 = 0;
		ECG_Byte = SPI_Buff[6] | 0x7F;

		if(ECG_Byte==0xFF)					// Verifica signo +/-
			ECG_Data_32 |= 0xFF000000;

		ECG_Data_32 |= SPI_Buff[6]<<16; 	// read top 8 bits data
		ECG_Data_32 |= SPI_Buff[7]<<8; 		// read middle 8 bits  data
		ECG_Data_32 |= SPI_Buff[8];			// read bottom 8 bits data

		Respiracion = 0;
		Respiracion |= SPI_Buff[3]<<16; 	// read top 8 bits data
		Respiracion |= SPI_Buff[4]<<8; 		// read middle 8 bits  data
		Respiracion |= SPI_Buff[5];

		memcpy(Buffer, &ECG_Data_32, 4);

		USART_Queue_Message(USART_3, Buffer, 4);

	}else{

		ECG_Data_32 = 0;
	}
}


void initADS1292R(void){

	spiSpeed(1, SPI_BaudRatePrescaler_16, SPI_CPOL_Low, SPI_CPHA_2Edge);

	GPIO_SetBits(ADS_RESET_PORT, ADS_RESET_PIN);
	ADS1292R_Write(SDATAC);
	GPIO_SetBits(ADS_START_PORT, ADS_START_PIN);
	Delay_ms(2);

	ADS1292_Write_Cmd(ADS1292_REG_CONFIG1, 0x00); 				//Set sampling rate to 125 SPS
	ADS1292_Write_Cmd(ADS1292_REG_CONFIG2, 0b10100000);//ADS1292_Write_Cmd(ADS1292_REG_CONFIG2, 0b10100011);		//Lead-off comp off, test signal disabled
	ADS1292_Write_Cmd(ADS1292_REG_LOFF, 0b00010000);			//Lead-off defaults
	ADS1292_Write_Cmd(ADS1292_REG_CH1SET, 0b01000000);//ADS1292_Write_Cmd(ADS1292_REG_CH1SET, 0b01001010);		//Ch 1 enabled, gain 6, connected to electrode in
	ADS1292_Write_Cmd(ADS1292_REG_CH2SET, 0b01100000);//ADS1292_Write_Cmd(ADS1292_REG_CH2SET, 0b01100101);	//Ch 2 enabled, gain 6, connected to electrode in
	ADS1292_Write_Cmd(ADS1292_REG_RLDSENS, 0b00101100);		//RLD settings: fmod/16, RLD enabled, RLD inputs from Ch2 only
	ADS1292_Write_Cmd(ADS1292_REG_LOFFSENS, 0x00);				//LOFF settings: all disabled
	 	  	  	  	  	  	  	  	  	  	  	  	  	    //Skip register 8, LOFF Settings default
	ADS1292_Write_Cmd(ADS1292_REG_RESP1, 0b11110010);			//Respiration: MOD/DEMOD turned only, phase 0
	ADS1292_Write_Cmd(ADS1292_REG_RESP2, 0b00000011);			//Respiration: Calib OFF, respiration freq defaults
	ADS1292R_Write(CMD_RDATAC);
}


static uint8_t ADS1292R_Write(uint8_t data){

	uint8_t	Recibido = 0;

	GPIO_ResetBits(ADS_CS_PORT, ADS_CS_PIN); 					// enable device
	Delay_ms(1);
	Recibido = SPI_ReadWrite_Byte(1, data); 								// send address to device
	Delay_ms(1);
	GPIO_SetBits(ADS_CS_PORT, ADS_CS_PIN);						// disable device
	Delay_ms(1);

	return Recibido;
}

static void ADS1292_Write_Cmd(uint8_t READ_ADDRESS, uint8_t DATA){		// Write control Reg

	uint8_t	dataToSend;

	dataToSend = 0x40 | READ_ADDRESS;
	GPIO_ResetBits(ADS_CS_PORT, ADS_CS_PIN); 					// enable device
	Delay_ms(1);
	SPI_ReadWrite_Byte(1, dataToSend);
	Delay_ms(1);
	SPI_ReadWrite_Byte(1, 0x00);
	Delay_ms(1);
	SPI_ReadWrite_Byte(1, DATA);
	Delay_ms(1);
	GPIO_SetBits(ADS_CS_PORT, ADS_CS_PIN);
	Delay_ms(1);
}



















