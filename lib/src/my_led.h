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
  // Prevent copying
  Led(const Led &) = delete;
  Led &operator=(const Led &) = delete;


  void set_led(byte state);
  void on();
  void off();
};

#endif // MY_LED_H