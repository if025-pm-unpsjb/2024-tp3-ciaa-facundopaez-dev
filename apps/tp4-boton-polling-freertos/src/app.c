/*
 * main.c
 *
 *  Created on: 13 oct. 2022
 *      Author: fep
 */

#include "FreeRTOS.h"
#include "task.h"
#include "app.h"         // <= Su propia cabecera (opcional)
#include "sapi.h"        // <= Biblioteca sAPI

void task(void *p);

int main(void) {
	// Inicializar y configurar la placa de desarrollo
	boardConfig();
	pwmConfig(0, PWM_ENABLE);
	pwmConfig(PWM7, PWM_ENABLE_OUTPUT);

	xTaskCreate(task, "T1", 256, NULL, configMAX_PRIORITIES - 1, NULL);
	vTaskStartScheduler();
	for (;;)
		;
}

void task(void *p) {
	bool_t buttonValue = OFF;

	while ( TRUE) {
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

		if (buttonValue) {
			pwmWrite(PWM7, 255);
		} else {
			pwmWrite(PWM7, 0);
		}

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

}
