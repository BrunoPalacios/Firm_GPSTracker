/* 
 * File:   Pulsadores.h
 * Author: Bruno
 *
 * Created on 5 de mayo de 2018, 13:10
 */

#ifndef PULSADORES_H
#define	PULSADORES_H

#include "stm32f0xx.h"

#if defined(STM32)

#define bit_test(d, b)	(d &  (1<<b))
#define bit_clear(d,b) 	(d &=~(1<<b))
#define bit_set(d,b) 	(d |= (1<<b))

#endif

#define DEBOUNCE_TIME       40
    
#define PULSADOR_SUELTO     0
#define PULSADO_CORTO       1
#define PULSADO_LARGO       2

#define NIVEL_REPOSO        0
#define PULSADOR_PRESIONADO 1   
#define MARCA_PULSADO       2    
    

typedef enum{

    NoPresionado = 0,
    Bajando,
    Presionado,
    PresionadoCorto,
    PresionadoLargo,
    Subiendo,
    EsperandoDebounce,
    AnalizoTiempo

} EstadosPulsador;

typedef struct{

    uint16_t            PinPulsador;
    EstadosPulsador     EstadoPulsador;
    
    uint8_t             General;
    uint8_t             PulsadorPresionado;
    
    uint16_t            TiempoPresionCorto;
    uint16_t            TiempoPresionLargo;

#if !defined(STM32)

    uint16_t            Debounce;
    uint16_t            ExDebounce;

#else

    uint32_t            Debounce;
    uint32_t            ExDebounce;
    uint32_t			Puerto;
#endif

} EstructuraPulsador;    



uint8_t ProcesoPulsador(uint32_t Systick, EstructuraPulsador *Pulsador);
uint8_t ConsultoPulsador(EstructuraPulsador *Pulsador);
void    BorroMarcaPulsador(EstructuraPulsador *Pulsador);
void    InicializoPulsador(EstructuraPulsador *Pulsador, uint16_t  PinPulsador, uint8_t NivelReposo, uint16_t  TiempoPresionCorto, uint16_t TiempoPresionLargo);

#if defined(STM32)
uint8_t	Input(uint32_t Puerto, uint16_t Pin);
#endif


#endif	/* PULSADORES_H */

