/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// DEPENDENCIAS
#include "../../example/inc/app.h"         // <= Su propia cabecera (opcional)

#include "sapi.h"        // <= Biblioteca sAPI
#include <stdio.h>
#include <ctype.h>

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main(void) {
	// ---------- CONFIGURACIONES ------------------------------

	// Inicializar y configurar la plataforma
	boardConfig();
	uartConfig(UART_USB, 9600);

	int indexLed = 0;
	int size = 4;

	uint8_t receivedByte;
	uint8_t leds[size];
	leds[0] = CIAA_BOARD_LED;
	leds[1] = LED1;
	leds[2] = LED2;
	leds[3] = LED3;

	// ---------- REPETIR POR SIEMPRE --------------------------
	while ( TRUE) {

		if (uartReadByte(UART_USB, &receivedByte) && isdigit(receivedByte)) {
			indexLed = (receivedByte - '0') - 1;

			if (0 <= indexLed && indexLed < size) {
				gpioToggle(leds[indexLed]);
			}

		}

	}

	// NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
	// directamenteno sobre un microcontroladore y no es llamado por ningun
	// Sistema Operativo, como en el caso de un programa para PC.
	return 0;
}
