#include "my_led.h"

Led::Led(byte pin) : pin(pin)
{
  pinMode(pin, OUTPUT);
  off();
}

void Led::set_led(byte state)
{
  digitalWrite(pin, state);
}

void Led::on()
{
  set_led(HIGH);
}

void Led::off()
{
  set_led(LOW);
}