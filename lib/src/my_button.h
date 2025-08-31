#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <Arduino.h>

class Button
{
private:
  byte _pin;

public:
  Button(byte pin);
  ~Button() = default;
  Button(const Button &) = delete;            // Prevent create copying
  Button &operator=(const Button &) = delete; // Prevent assignment copying

  byte update();
};

#endif // MY_BUTTON_H