/* 
 * File:   Lectura ADCs.h
 * Author: Bruno
 *
 * Created on 14 de marzo de 2018, 20:03
 */

#ifndef LECTURA_ADCS_H
#define	LECTURA_ADCS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_dma.h"
#include "stm32f0xx_adc.h"
#include "stm32f0xx_it.h"
#include "string.h"

typedef	struct {

	uint16_t	Bateria;
	uint16_t	Microfono;
	uint16_t	Presion;

} EntradasAnalogicas;

void initADC(void);
void procesoADCs(void);
void ADC_InterruptRoutine(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LECTURA_ADCS_H */

