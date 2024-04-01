#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>
#include <config.h>
#include <pinout.h>
#include <Adafruit_NeoPixel.h>

enum LEDS {
  RGB_LEFT = 2,
  RGB_TOP = 1,
  RGB_RIGHT = 0
};

void set_led(enum LEDS led, int r, int g, int b);
void clear_led(enum LEDS led);

void blink_led(enum LEDS led, int r, int g, int b, int ms);
void rainbow_led(enum LEDS led);

void clear_leds();
void set_leds(int r, int g, int b);
void blink_leds(int r, int g, int b, int ms);

#endif // LEDS_H