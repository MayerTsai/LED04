#include "my_button.h"

const unsigned long DEBOUNCE_TIME = 50;

Button::Button(byte pin) : _pin(pin) // Initialize state to off
{
  pinMode(pin, INPUT);
}

byte Button::update()
{
  byte reading_1 = digitalRead(_pin);
  delay(DEBOUNCE_TIME);
  byte reading_2 = digitalRead(_pin);
  if (reading_1 == reading_2)
    return reading_1;
  return reading_2;
}