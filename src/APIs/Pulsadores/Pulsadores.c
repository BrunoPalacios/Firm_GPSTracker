#include "Pulsadores.h"

uint8_t ProcesoPulsador(uint32_t Systick, EstructuraPulsador *Pulsador) {

	switch (Pulsador->EstadoPulsador) {

	case NoPresionado:

		bit_clear(Pulsador->General, MARCA_PULSADO);                        // Marco pulsador no presionado

		if (Input(Pulsador->Puerto, Pulsador->PinPulsador) != bit_test(Pulsador->General, NIVEL_REPOSO)) {     // Si estoy fuera del estado normal

			Pulsador->EstadoPulsador = Bajando;
			Pulsador->Debounce = Systick;
		}

		break;

	case Bajando:

		if ((uint16_t) (Systick - Pulsador->Debounce) >= DEBOUNCE_TIME){// Tras vencerse el tiempo de debounce

			if (Input(Pulsador->Puerto, Pulsador->PinPulsador) != bit_test(Pulsador->General, NIVEL_REPOSO)){

				// Sigue presionado?

				Pulsador->EstadoPulsador = Presionado;                      // Marco
				Pulsador->Debounce = Systick;

			} else {

				Pulsador->EstadoPulsador = NoPresionado;                    // Acá no pasó nada
			}
		}

		break;

	case Presionado:

		if (Input(Pulsador->Puerto, Pulsador->PinPulsador) != bit_test(Pulsador->General, NIVEL_REPOSO)){      // Si sigue presionado

			if ((uint16_t) (Systick - Pulsador->Debounce) >= Pulsador->TiempoPresionLargo){

				Pulsador->Debounce = Systick - Pulsador->TiempoPresionLargo;

				if(bit_test(Pulsador->General, MARCA_PULSADO) == 0){        // Si aun no lo marque pero paso el tiempo maximo

					bit_set(Pulsador->General, MARCA_PULSADO);              // Marco pulsador presionado
					bit_set(Pulsador->General, PULSADOR_PRESIONADO);        // Marco pulsador presionado
					Pulsador->PulsadorPresionado = PULSADO_LARGO;           // para que el soft actue
				}
			}

		}else{

			if(bit_test(Pulsador->General, MARCA_PULSADO) == 0){            // Si no marque largo

				if ((uint16_t) (Systick - Pulsador->Debounce) >= Pulsador->TiempoPresionCorto){

					bit_set(Pulsador->General, PULSADOR_PRESIONADO);        // Marco pulsador presionado
					Pulsador->PulsadorPresionado = PULSADO_CORTO;           // para que el soft actue
				}
			}

			Pulsador->ExDebounce = Pulsador->Debounce;
			Pulsador->Debounce = Systick;
			Pulsador->EstadoPulsador = Subiendo;
		}

		break;

	case Subiendo:

		if ((uint16_t) (Systick - Pulsador->Debounce) >= DEBOUNCE_TIME){

			if (Input(Pulsador->Puerto, Pulsador->PinPulsador) == bit_test(Pulsador->General, NIVEL_REPOSO)){

				Pulsador->EstadoPulsador = NoPresionado;

			}else{

				Pulsador->EstadoPulsador = Presionado;
				Pulsador->Debounce = Pulsador->ExDebounce ;
			}
		}

		break;

	default:

		Pulsador->EstadoPulsador = NoPresionado;
		break;
	}

	return 0;
}


uint8_t ConsultoPulsador(EstructuraPulsador *Pulsador){

	uint8_t Estado = 0;

	if(bit_test(Pulsador->General, PULSADOR_PRESIONADO)){

		if(Pulsador->PulsadorPresionado == PULSADO_CORTO){

			Estado = PULSADO_CORTO;

		}else{

			Estado = PULSADO_LARGO;
		}
	}

	return Estado;
}

void BorroMarcaPulsador(EstructuraPulsador *Pulsador){

	bit_clear(Pulsador->General, PULSADOR_PRESIONADO);
}


void InicializoPulsador(EstructuraPulsador *Pulsador, uint16_t PinPulsador, uint8_t NivelReposo, uint16_t TiempoPresionCorto, uint16_t TiempoPresionLargo) {

	Pulsador->PinPulsador = PinPulsador;
	Pulsador->EstadoPulsador = NoPresionado;
	Pulsador->TiempoPresionCorto = TiempoPresionCorto;

	if(!TiempoPresionLargo)
		TiempoPresionLargo = 0xffff;

	Pulsador->TiempoPresionLargo = TiempoPresionLargo;
	Pulsador->PulsadorPresionado = PULSADOR_SUELTO;

	if(NivelReposo)
		bit_set(Pulsador->General, NIVEL_REPOSO);
	else
		bit_clear(Pulsador->General, NIVEL_REPOSO);

	bit_clear(Pulsador->General, PULSADOR_PRESIONADO);
	bit_clear(Pulsador->General, MARCA_PULSADO);
}


#if defined(STM32)

uint8_t	Input(uint32_t Puerto, uint16_t Pin){

	return GPIO_ReadInputDataBit((GPIO_TypeDef*) Puerto, Pin);
}

#endif
