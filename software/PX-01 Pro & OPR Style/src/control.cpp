#include "control.h"

static long last_control_loop_us = 0;
static int position = 0;
static int last_error = 0;

static int base_speed = 0;
static int base_accel_speed = 0;
static int base_fan_speed = 0;

static int curve_speed = 0;
static int curve_fan_speed = 0;

static int speed = 0;

static bool race_starting = false;
static bool race_started = false;
static long race_started_ms = 0;
static long last_turn_ms = 0;
static long race_stopped_ms = 0;

static bool curve_entry = false;
static bool first_accel = true;

/**
 * @brief Realiza el cálculo de la corrección del controlador PID en función del error respecto a la posición de la línea.
 *
 * @param error Desplazamiento del robot respecto a la línea.
 * @return float Corrección del controlador PID.
 */
static float calc_correction(int error) {
  float p = PID_KP * error;
  float d = PID_KD * (error - last_error);
  last_error = error;
  return p + d;
}

/**
 * @brief Establece el estado de iniciando carrera.
 *
 * @param starting Indica si la carrera está iniciando.
 */
void set_race_starting(bool starting) {
  race_starting = starting;
}

/**
 * @brief Comprueba si la carrera está iniciando.
 *
 * @return true Iniciando.
 * @return false En espera o iniciada.
 */
bool is_race_starting() {
  return race_starting;
}

/**
 * @brief Establece el estado de la carrera y, en caso de haber comenzado, guarda el tiempo (ms) de inicio.
 *
 * @param started Indica si la carrera ha comenzado.
 */
void set_race_started(bool started) {
  speed = 0;
  race_started = started;
  if (started) {
    speed = 0;
    race_started_ms = millis();
    last_turn_ms = millis();
  }else{
    race_stopped_ms = millis();
  }
}

/**
 * @brief Comprueba si la carrera está en curso.
 *
 * @return true En carrera.
 * @return false En espera.
 */
bool is_race_started() {
  return race_started;
}

/**
 * @brief Obtiene los ms de inicio de la carrera.
 * Comparando este dato con el resultado de millis() se puede calcular el tiempo transcurrido desde el inicio de la carrera.
 *
 * @return long Tiempo de inicio de la carrera en ms.
 */
long get_race_started_ms() {
  return race_started_ms;
}

long get_race_stopped_ms() {
  return race_stopped_ms;
}

/**
 * @brief Establece la velocidad base del robot.
 *
 * @param speed Velocidad base.
 */
void set_base_speed(int speed) {
  base_speed = speed;
  curve_speed = speed * 7/10;
}

/**
 * @brief Establece la aceleración inicial del robot.
 *
 * @param accel_speed Aceleración inicial.
 */
void set_base_accel_speed(int accel_speed) {
  base_accel_speed = accel_speed;
}

/**
 * @brief Establece la velocidad base del ventilador.
 *
 * @param fan_speed Velocidad base del ventilador.
 */
void set_base_fan_speed(int fan_speed) {
  base_fan_speed = fan_speed;
  curve_fan_speed = fan_speed *12/10;
}

/**
 * @brief Obtiene la velocidad base del ventilador.
 *
 * @return int Velocidad base del ventilador.
 */ 
int get_base_fan_speed() {
  return base_fan_speed;
}

/**
 * @brief Bucle de control principal. Realiza el cálculo de la corrección del controlador PID y establece la velocidad de los motores y el ventilador.
 * Esta función debe llamarse lo más frecuentemente posible. El tiempo entre ejecuciones está definido por la constante CONTROL_LOOP_US.
 * 
 */
void control_loop() {
  if (micros() - last_control_loop_us > CONTROL_LOOP_US || micros() < last_control_loop_us) {
    position = get_sensor_position(position);
    int correction = calc_correction(position);
    if (millis() - get_last_line_detected_ms() > 250) {
      set_motors_speed(0, 0);
      set_fan_speed(0);
      set_race_started(false);
    } else {
      if(first_accel) {
        if (speed < base_speed) {
          speed = /*8 +*/ (base_accel_speed * ((millis() - race_started_ms) / 1000.0f));
        } else if (speed > base_speed) {
          speed = base_speed;
          first_accel = false;
        }
      }else{
        if (speed < base_speed) {
          speed = curve_speed + (base_accel_speed * ((millis() - race_started_ms) / 1000.0f));
        } else if (speed > base_speed) {
          speed = base_speed;
        }
      }
      /*
      if(!qre1113FrontalBlanco()){
        set_led(RGB_LEFT, 95, 0, 160);
        set_led(RGB_RIGHT, 95, 0, 160);
        set_motors_speed((curve_speed) + correction, (curve_speed) - correction);
        if (base_fan_speed > 0) {
          set_fan_speed(curve_fan_speed);
        }
        if(curve_entry){
          last_turn_ms = millis();
          curve_entry = false;
        }
      }else{
        clear_led(RGB_LEFT);
        clear_led(RGB_RIGHT);
        curve_entry = true;
        set_motors_speed(speed + correction, speed - correction);
        if (base_fan_speed > 0) {
          set_fan_speed(base_fan_speed);
        }
      }*/
      set_motors_speed(speed + correction, speed - correction);
      if (base_fan_speed > 0) {
        set_fan_speed(base_fan_speed);
      }
      /////
    }
    last_control_loop_us = micros();
  }
}