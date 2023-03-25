/*
 * GPS.h
 *
 *  Created on: 25 mar. 2023
 *      Author: Bruno
 */

#ifndef GPS_H_
#define GPS_H_

#include "stm32f0xx.h"
#include "portUSART_STM32F072.h"


#define GPS_ONOFF_PORT		GPIOA
#define GPS_RESET_PORT		GPIOB

#define GPS_ONOFF_PIN		GPIO_Pin_8
#define GPS_RESET_PIN		GPIO_Pin_15

typedef enum {

	GPS_Initialize = 0,
	GPS_Wait,
	GPS_Receive

} teGPState;

void GPSTask(stGeneral *Gen);

#endif /* GPS_H_ */
