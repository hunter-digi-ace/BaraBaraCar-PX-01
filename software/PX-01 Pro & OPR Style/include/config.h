#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#include "motors.h"
#include "pinout.h"
#include "rc5.h"

/**
 * @brief Indica el modo de funcionamiento del robot.
 *
 */
//#define MODE_TEST 1
#define MODE_RACE 2

/**
 * @brief Indica si la línea a seguir es blanca o negra.
 * Este control se usa para aplicar un filtro en la detección de la línea.
 * 
 */
// #define LINE_WHITE 0
#define LINE_BLACK 1

/**
 * @brief Tiempo de espera para iniciar carrera después de pulsar el botón.
 *
 */
#define START_TEST_MS 3000
#define START_RACE_MS 5000

/**
 * @brief Tiempo máximo de ejecución en modo prueba (MODE_TEST).
 * Después de este tiempo, el robot se detendrá automáticamente.
 * 
 */
#define TEST_DURATION_MS 2000

/**
 * @brief Define el tiempo de espera entre ejecuciones del bucle de control en microsegundos.
 *
 */
#define CONTROL_LOOP_US 1000

/**
 * @brief Tiempo de calibración de sensores.
 *
 */
#define SENSORS_CALIBRATION_MS 3000

/**
 * @brief Configuración de Velocidad y Aceleración.
 * Dispone de varios menús para seleccionar la velocidad y aceleración del robot.
 * 
 */
#define STARTING_SPEED 5

#define MENU_1_BASE_SPEED 40
#define MENU_1_ACCEL_SPEED 30
#define MENU_1_BASE_FAN_SPEED 40

#define MENU_2_BASE_SPEED 45
#define MENU_2_ACCEL_SPEED 30
#define MENU_2_BASE_FAN_SPEED 50

#define MENU_3_BASE_SPEED 50
#define MENU_3_ACCEL_SPEED 35
#define MENU_3_BASE_FAN_SPEED 60

#define MENU_4_BASE_SPEED 55
#define MENU_4_ACCEL_SPEED 40
#define MENU_4_BASE_FAN_SPEED 70

#define MENU_5_BASE_SPEED 65
#define MENU_5_ACCEL_SPEED 45
#define MENU_5_BASE_FAN_SPEED 75

/**
 * @brief Constantes del controlador PID.
 *
 */
#define PID_KP 0.2 // 0.2
#define PID_KD 2.5//0.80 //1.5 //2

void init_components();
long get_ms_start();

#endif