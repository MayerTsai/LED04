#include "my_led_driver.h"

const unsigned long SHORT_TIME_MS = 500;
const unsigned long LONG_TIME_MS = 1000;
const unsigned long BLINKING_TIME_MS = 500;

LedDriver::LedDriver(Led &led, Button &sw) : _led(led), _sw(sw),
                                             _button_state(button_state_t::PRESSED),
                                             _last_button_state_time(0),
                                             _command(light_command_t::LIGHT_OFF),
                                             _led_state(LOW),
                                             _last_blinking_time(0)
{
  update_led();
}

void LedDriver::update_led()
{
  unsigned long duration = get_duration_ms();
  set_command(duration);
  set_led_state();
  _led.set_led(_led_state);
}

unsigned long LedDriver::get_duration_ms(char *mode = "pressed")
{
  unsigned long pressed_duration = 0;
  unsigned long released_duration = 0;

  button_state_t new_state = button_state_t::RELEASED;
  byte reading = _sw.update();
  if (reading == LOW)
    new_state = button_state_t::PRESSED;

  if (new_state != _button_state)
  {
    _button_state = new_state;
    if (_button_state == button_state_t::PRESSED)
    {
      released_duration = millis() - _last_button_state_time;
      _last_button_state_time = millis();
    }
    else
    {
      pressed_duration = millis() - _last_button_state_time;
      _last_button_state_time = millis();
    }
  }
  if (strcmp(mode, "released"))
    return released_duration;
  else
    return pressed_duration;
}

void LedDriver::set_command(unsigned long duration)
{
  if (duration > 0)
  {
    if (duration < SHORT_TIME_MS)
      _command = light_command_t::LIGHT_ON;
    else if (duration < LONG_TIME_MS)
      _command = light_command_t::LIGHT_TOGGLE;
  }
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
}