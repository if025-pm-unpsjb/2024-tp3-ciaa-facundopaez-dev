/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// DEPENDENCIAS
#include "../../example/inc/app.h"         // <= Su propia cabecera (opcional)

#include "sapi.h"        // <= Biblioteca sAPI

void led(void*);

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main(void) {
	// ---------- CONFIGURACIONES ------------------------------

	// Inicializar y configurar la plataforma
	boardConfig();

	uartConfig(UART_USB, 9600);
	uartInterrupt(UART_USB, TRUE);
	uartCallbackSet(UART_USB, UART_RECEIVE, led, NULL);

	// ---------- REPETIR POR SIEMPRE --------------------------
	while (TRUE) {
	}

	// NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
	// directamenteno sobre un microcontroladore y no es llamado por ningun
	// Sistema Operativo, como en el caso de un programa para PC.
	return 0;
}

void led(void*) {
	uint8_t receivedByte = uartRxRead(UART_USB);

	if (receivedByte == '1') {
		gpioToggle(CIAA_BOARD_LED);
	}

	if (receivedByte == '2') {
		gpioToggle(LED1);
	}

	if (receivedByte == '3') {
		gpioToggle(LED2);
	}

	if (receivedByte == '4') {
		gpioToggle(LED3);
	}

}
