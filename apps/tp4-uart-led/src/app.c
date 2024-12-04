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

	uint8_t receivedByte;

	int rgbLed = 0;
	int ledOne = 0;
	int ledTwo = 0;
	int ledThree = 0;

	// ---------- REPETIR POR SIEMPRE --------------------------
	while ( TRUE) {

		if (uartReadByte(UART_USB, &receivedByte)) {

			switch (receivedByte) {
			case '1':
				switch (rgbLed) {
				case 0:
					gpioWrite( CIAA_BOARD_LED, 1);
					rgbLed = 1;
					break;
				case 1:
					gpioWrite( CIAA_BOARD_LED, 0);
					rgbLed = 0;
					break;
				}
				break;
			case '2':
				// Bloque de codigo para el LED amarillo
				switch (ledOne) {
				case 0:
					gpioWrite(LED1, 1);
					ledOne = 1;
					break;
				case 1:
					gpioWrite(LED1, 0);
					ledOne = 0;
					break;
				}
				break;
			case '3':
				// Bloque de codigo para el LED rojo
				switch (ledTwo) {
				case 0:
					gpioWrite(LED2, 1);
					ledTwo = 1;
					break;
				case 1:
					gpioWrite(LED2, 0);
					ledTwo = 0;
					break;
				}
				break;
			case '4':
				// Bloque de codigo para el LED verde
				switch (ledThree) {
				case 0:
					gpioWrite(LED3, 1);
					ledThree = 1;
					break;
				case 1:
					gpioWrite(LED3, 0);
					ledThree = 0;
					break;
				}
				break;
			}

		}

	}

	// NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
	// directamenteno sobre un microcontroladore y no es llamado por ningun
	// Sistema Operativo, como en el caso de un programa para PC.
	return 0;
}
