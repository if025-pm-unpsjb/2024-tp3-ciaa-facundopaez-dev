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
#include "semphr.h"

void task(void *taskParameters);

/*
 * Busy wait the specified number of ticks.
 */
static void vBusyWait(TickType_t ticks);

struct xTaskStruct {
	int id;
	TickType_t wcet;
	TickType_t period;
	pwmMap_t led;
};

typedef struct xTaskStruct xTask;

TaskHandle_t task2Handle, task3Handle, task4Handle;

/*
 * La constante PWM7 esta asociada al LED amarillo.
 * La constante PWM8 esta asociada al LED rojo.
 * La constante PWM9 esta asociada al LED verde.
 */

xTask task1 = { 1, 500, 4000 };
xTask task2 = { 2, 1000, 6000, PWM7 };
xTask task3 = { 3, 2000, 8000, PWM8 };
xTask task4 = { 4, 3000, 10000, PWM9 };

SemaphoreHandle_t s;

int main(void) {
	// Inicializar y configurar la placa de desarrollo
	boardConfig();

	pwmConfig(0, PWM_ENABLE);

	pwmConfig(PWM7, PWM_ENABLE_OUTPUT);
	pwmConfig(PWM8, PWM_ENABLE_OUTPUT);
	pwmConfig(PWM9, PWM_ENABLE_OUTPUT);

	s = xSemaphoreCreateMutex();

	xTaskCreate(task, NULL, 256, (void*) &task1, configMAX_PRIORITIES - 1,
	NULL);
	xTaskCreate(task, NULL, 256, (void*) &task2, configMAX_PRIORITIES - 2,
			&task2Handle);
	xTaskCreate(task, NULL, 256, (void*) &task3, configMAX_PRIORITIES - 3,
			&task3Handle);
	xTaskCreate(task, NULL, 256, (void*) &task4, configMAX_PRIORITIES - 4,
			&task4Handle);
	vTaskStartScheduler();
	for (;;)
		;
}

void task(void *taskParameters) {
	TickType_t xPreviousWakeTime = xTaskGetTickCount();
	xTask *task = (xTask*) taskParameters;

	while ( TRUE) {

		if (task->id == 1) {
			/*
			 * Enciende el LED azul
			 */
			gpioWrite( CIAA_BOARD_LED, 1);

			/*
			 * Hace uso de la CPU
			 */
			vBusyWait(task->wcet);

			/*
			 * Apaga el LED azul
			 */
			gpioWrite( CIAA_BOARD_LED, 0);

			/*
			 * Bloquea la tarea hasta su proxima ejecucion
			 */
			vTaskDelayUntil(&xPreviousWakeTime, task->period);
		}

		if (task->id == 2) {
			/*
			 * Enciende el LED asociado a la tarea 2
			 */
			pwmWrite(task->led, 255);

			/*
			 * Hace uso de la CPU
			 */
			vBusyWait(task->wcet);

			/*
			 * Apaga el LED asociado a la tarea 2
			 */
			pwmWrite(task->led, 0);

			/*
			 * Bloquea la tarea hasta su proxima ejecucion
			 */
			vTaskDelayUntil(&xPreviousWakeTime, task->period);
		}

		if (task->id == 3) {
			/*
			 * Enciende el LED asociado a la tarea 3
			 */
			pwmWrite(task->led, 255);

			/*
			 * Hace uso de la CPU
			 */
			vBusyWait(task->wcet);

			/*
			 * Apaga el LED asociado a la tarea 3
			 */
			pwmWrite(task->led, 0);

			/*
			 * Bloquea la tarea hasta su proxima ejecucion
			 */
			vTaskDelayUntil(&xPreviousWakeTime, task->period);
		}

		if (task->id == 4) {
			/*
			 * Enciende el LED asociado a la tarea 4
			 */
			pwmWrite(task->led, 255);

			/*
			 * Hace uso de la CPU
			 */
			vBusyWait(task->wcet);

			/*
			 * Apaga el LED asociado a la tarea 4
			 */
			pwmWrite(task->led, 0);

			/*
			 * Bloquea la tarea hasta su proxima ejecucion
			 */
			vTaskDelayUntil(&xPreviousWakeTime, task->period);
		}

	}

}

void vBusyWait(TickType_t ticks) {
	TickType_t elapsedTicks = 0;
	TickType_t currentTick = 0;

	while (elapsedTicks < ticks) {
		currentTick = xTaskGetTickCount();
		while (currentTick == xTaskGetTickCount()) {
			__asm("nop");
		}
		elapsedTicks++;
	}

}
