/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// DEPENDENCIAS
#include "../../example/inc/app.h"         // <= Su propia cabecera (opcional)

#include "sapi.h"        // <= Biblioteca sAPI

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main(void) {
	// ---------- CONFIGURACIONES ------------------------------

	// Inicializar y configurar la plataforma
	boardConfig();
	uartConfig(UART_USB, 9600);

	int size = 50;
	int index = 0;

	uint8_t receivedByte;
	uint8_t message[size];

	for (int i = 0; i < size; i++) {
		message[i] = "\0";
	}

	// ---------- REPETIR POR SIEMPRE --------------------------
	while ( TRUE) {

		if (uartReadByte(UART_USB, &receivedByte)) {

			if (receivedByte != '\r') {
				message[index] = receivedByte;
				index = (index + 1) % size;
			}

			if (receivedByte == '\r') {

				for (int i = 0; i < size; i++) {
					uartWriteByte(UART_USB, message[i]);
				}

				for (int i = 0; i < size; i++) {
					message[i] = "\0";
				}

			}

		}

	}

	// NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
	// directamenteno sobre un microcontroladore y no es llamado por ningun
	// Sistema Operativo, como en el caso de un programa para PC.
	return 0;
}
