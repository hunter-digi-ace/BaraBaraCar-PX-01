#include <Arduino.h>

#include "config.h"
#include "control.h"
#include "menu.h"
#include "pinout.h"
#include "sensors.h"

bool race_started = false;
long race_started_ms = 0;

void setup() {
  init_components();
  calibrate_sensors();
  main_menu();
  
  pinMode(BTN_1, INPUT);
}

void loop() {
  //modo test, para que pare despues de TEST_DURATION_MS millis
  //if ((millis() - get_race_started_ms()) >= TEST_DURATION_MS) {
  //  set_fan_speed(0);
  //  set_motors_speed(0, 0);
  //  set_race_started(false);
  //}else{

  
  if (!is_race_starting()) {
    set_fan_speed(0);
    set_motors_speed(0, 0);
    set_race_started(false);
  }else{
    control_loop();
  }

  
  //}


/*
  if (!is_race_starting()) {
    clear_leds();
  }else{
    set_leds(0,200,50);
    Serial.println(digitalRead(BTN_1));
  }*/

}
