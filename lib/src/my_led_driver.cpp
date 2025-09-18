#include "my_led_driver.h"

const unsigned long SHORT_TIME_MS = 500;
const unsigned long LONG_TIME_MS = 1000;
const unsigned long BLINKING_TIME_MS = 500;

LedDriver::LedDriver(Led &led, Button &sw) : _led(led), _sw(sw),
                                             _button_state(button_state_t::PRESSED),
                                             _last_button_state_time(millis()),
                                             _command(light_command_t::LIGHT_OFF),
                                             _led_state(LOW),
                                             _last_blinking_time(0)
{
  update_led();
}

void LedDriver::update_led()
{
  unsigned long duration = get_button_pressed_duration_ms();
  if (duration > 0)
    set_command(duration);
  set_led_state();
}

unsigned long LedDriver::get_button_pressed_duration_ms(char mode[])
{
  unsigned long pressed_duration = 0;
  unsigned long released_duration = 0;

  button_state_t new_state = (_sw.update() == LOW) ? button_state_t::PRESSED : button_state_t::RELEASED;
  if (new_state != _button_state)
  {
    unsigned long now = millis();
    if (_button_state == button_state_t::PRESSED)
      released_duration = now - _last_button_state_time;
    else
      pressed_duration = now - _last_button_state_time;
    _last_button_state_time = now;
    _button_state = new_state;
  }
  if (strcmp(mode, "released") == 0)
    return released_duration;
  if (strcmp(mode, "pressed") == 0)
    return pressed_duration;
}

void LedDriver::set_command(unsigned long duration)
{
  if (duration < SHORT_TIME_MS)
    _command = light_command_t::LIGHT_ON;
  else if (duration < LONG_TIME_MS)
    _command = light_command_t::LIGHT_TOGGLE;
  else
    _command = light_command_t::LIGHT_OFF;
}

void LedDriver::set_led_state()
{
  unsigned long blinking_duration = 0;
  switch (_command)
  {
  case light_command_t::LIGHT_OFF:
    _led_state = LOW;
    break;
  case light_command_t::LIGHT_ON:
    _led_state = HIGH;
    break;
  case light_command_t::LIGHT_TOGGLE:
    if (_last_blinking_time == 0)
      _last_blinking_time = millis();
    else
      blinking_duration = millis() - _last_blinking_time;
    if (blinking_duration > BLINKING_TIME_MS)
    {
      _led_state = !_led_state;
      _last_blinking_time = 0;
    }
    break;
  }
  _led.set_led(_led_state);
}