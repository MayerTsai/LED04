#include "my_led_driver.h"

const unsigned long SHORT_TIME_MS = 500;
const unsigned long LONG_TIME_MS = 1000;
const unsigned long BLINKING_TIME_MS = 500;

LedDriver::LedDriver(Led &led, Button &sw) : _led(led), _sw(sw),
                                             _last_button_state(button_state_t::PRESSED),
                                             _command(light_command_t::LIGHT_OFF),
                                             _last_command_time(0),
                                             _last_led_state(LOW),
                                             _last_blinking_time(0)
{
  update_led();
}

void LedDriver::update_led()
{

  button_state_t new_state = button_state_t::RELEASED;
  byte reading = _sw.update();
  if (reading == LOW)
    new_state = button_state_t::PRESSED;

  unsigned long duration = 0;
  if (new_state != _last_button_state)
  {
    _last_button_state = new_state;
    if (_last_button_state == button_state_t::PRESSED)
      _last_command_time = millis();
    else
      duration = millis() - _last_command_time;
  }

  if (duration > 0)
  {
    if (duration < SHORT_TIME_MS)
      _command = light_command_t::LIGHT_ON;
    else if (duration < LONG_TIME_MS)
      _command = light_command_t::LIGHT_TOGGLE;
    else
      _command = light_command_t::LIGHT_OFF;
  }

  unsigned long blinking_duration = 0;
  switch (_command)
  {
  case light_command_t::LIGHT_OFF:
    _last_led_state = LOW;
    break;
  case light_command_t::LIGHT_ON:
    _last_led_state = HIGH;
    break;
  case light_command_t::LIGHT_TOGGLE:
    if (_last_blinking_time == 0)
      _last_blinking_time = millis();
    else
      blinking_duration = millis() - _last_blinking_time;
    if (blinking_duration > BLINKING_TIME_MS)
    {
      _last_led_state = !_last_led_state;
      _last_blinking_time = 0;
    }
    break;
  }
  _led.set_led(_last_led_state);
}
