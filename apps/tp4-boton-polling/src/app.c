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

	// Crear una variable del tipo booleano
	bool_t buttonValue = OFF;

	// ---------- REPETIR POR SIEMPRE --------------------------
	while (TRUE) {
		// Leer pin conectado al boton.
		buttonValue = gpioRead(CIAA_BOARD_BUTTON);

		// Invertir el valor leido, pues lee un 0 (OFF) con boton
		// presionado y 1 (ON) al liberarla.
		buttonValue = !buttonValue;

		// Escribir el valor leido en el LED correspondiente.
		gpioWrite(CIAA_BOARD_LED, buttonValue);

		// ****************************************************

		// Enciede/apaga el LED amarillo mediante el pulsador TEC2
		buttonValue = gpioRead(TEC2);
		buttonValue = !buttonValue;
		gpioWrite(LED1, buttonValue);

		// ****************************************************

		// Enciede/apaga el LED rojo mediante el pulsador TEC3
		buttonValue = gpioRead(TEC3);
		buttonValue = !buttonValue;
		gpioWrite(LED2, buttonValue);

		// ****************************************************

		// Enciede/apaga el LED verde mediante el pulsador TEC4
		buttonValue = gpioRead(TEC4);
		buttonValue = !buttonValue;
		gpioWrite(LED3, buttonValue);
	}

	// NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
	// directamenteno sobre un microcontroladore y no es llamado por ningun
	// Sistema Operativo, como en el caso de un programa para PC.
	return 0;
}
