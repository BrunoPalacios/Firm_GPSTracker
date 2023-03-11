/*
 * DAC.h
 *
 *  Created on: 27/02/2019
 *      Author: HP
 */

#ifndef DAC_DAC_H_
#define DAC_DAC_H_


#define DAC_DHR12R1_ADDRESS      0x40007408
#define DAC_DHR8R1_ADDRESS       0x40007410

void initDAC(void);
void initDAC_DMA(void);
void procesarDAC_DMA(uint8_t *Buffer, uint16_t Largo, uint32_t Frecuencia);
void detenerDAC_DMA(void);
void DAC_DMA_ISR(void);

#endif /* DAC_DAC_H_ */
