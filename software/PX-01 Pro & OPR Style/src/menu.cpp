#include "menu.h"

static int8_t menu_index = 0;

/**
 * @brief Menú principal despues de calibrar sensores.
 *
 */
void main_menu(){
  while (!is_race_started()) {
    BTN_STATES btn_state = get_btn_pressed_state();
    if (btn_state == BTN_PRESSING && get_btn_pressing_ms() >= 250) {
      clear_leds();
      while (btn_state == BTN_PRESSING) {
        blink_leds(95, 0, 160, 125);
        btn_state = get_btn_pressed_state();
      }
    } else {
      handle_menu(btn_state);
    }

    if ((btn_state == BTN_LONG_PRESSED) || is_race_starting()) {
      set_race_starting(true);
      set_leds(95, 0, 160);
      long starting_ms = millis();
      while (millis() < (starting_ms + get_ms_start())) {
        if (get_ms_start() > 3000 && millis() - starting_ms < get_ms_start() - 3000) {
          blink_leds(95, 0, 160, 500);
        } else {
          if (millis() - starting_ms < get_ms_start() - 2000) {
            set_leds(95, 0, 160);
          } else if (millis() - starting_ms < get_ms_start() - 1000) {
            set_led(RGB_RIGHT, 95, 0, 160);
            set_led(RGB_LEFT, 95, 0, 160);
            clear_led(RGB_TOP);
          } else {
            set_led(RGB_TOP, 95, 0, 160);
            clear_led(RGB_LEFT);
            clear_led(RGB_RIGHT);
            if (get_base_fan_speed() != 0) {
              set_fan_speed(get_base_fan_speed() * 0.85f);
            }
          }
        }
      }
      clear_leds();
      set_race_started(true);
    }
  }
}

/**
 * @brief En función de la selección del menú, establece la velocidad de motores y ventilador y la aceleración del robot.
 * Además, muestra el LED RGB correspondiente.
 *
 */
static void handle_menu_index() {
  switch (menu_index) {
    case 0:
      set_led(RGB_LEFT, 95, 0, 160);
      clear_led(RGB_TOP);
      clear_led(RGB_RIGHT);
      set_base_speed(MENU_1_BASE_SPEED);
      set_base_accel_speed(MENU_1_ACCEL_SPEED);
      set_base_fan_speed(MENU_1_BASE_FAN_SPEED);
      break;
    case 1:
      clear_led(RGB_LEFT);
      set_led(RGB_TOP, 95, 0, 160);
      clear_led(RGB_RIGHT);
      set_base_speed(MENU_2_BASE_SPEED);
      set_base_accel_speed(MENU_2_ACCEL_SPEED);
      set_base_fan_speed(MENU_2_BASE_FAN_SPEED);
      break;
    case 2:
      clear_led(RGB_LEFT);
      clear_led(RGB_TOP);
      set_led(RGB_RIGHT, 95, 0, 160);
      set_base_speed(MENU_3_BASE_SPEED);
      set_base_accel_speed(MENU_3_ACCEL_SPEED);
      set_base_fan_speed(MENU_3_BASE_FAN_SPEED);
      break;
    case 3:
      clear_led(RGB_LEFT);
      clear_led(RGB_TOP);
      set_led(RGB_RIGHT, 95, 0, 160);
      set_led(RGB_TOP, 95, 0, 160);
      set_base_speed(MENU_4_BASE_SPEED);
      set_base_accel_speed(MENU_4_ACCEL_SPEED);
      set_base_fan_speed(MENU_4_BASE_FAN_SPEED);
      break;
  }
}

/**
 * @brief Gestiona el menú de selección de velocidades.
 *
 * @param btn_state Estado del botón.
 */
void handle_menu(BTN_STATES btn_state) {
  if (btn_state == BTN_PRESSED) {
    menu_index = (menu_index + 1) % 4;
  }
  handle_menu_index();
}