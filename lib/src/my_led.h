#ifndef MY_LED_H
#define MY_LED_H

#include <Arduino.h>

class Led
{
private:
  byte pin;

public:
  Led(byte pin);
  ~Led() = default;
  Led(const Led &) = delete;            // prevent from create copying
  Led &operator=(const Led &) = delete; // prevent from assignment copying

  void set_led(byte state);
  void on();
  void off();
};

#endif // MY_LED_H