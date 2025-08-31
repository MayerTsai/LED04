#include "my_led_driver.h"

const unsigned long SHORT_TIME_MS = 500;
const unsigned long LONG_TIME_MS = 1000;
const unsigned long BLICKING_TIME_MS = 500;

LedDriver::LedDriver(Led &led, Button &sw) : _led(led), _sw(sw),
                                             _last_button_state(RELEASED),
                                             _command(LIGHT_OFF),
                                             _last_command_time(0),
                                             _last_led_state(LOW),
                                             _last_blinking_time(0)
{
  update_led();
}

void LedDriver::update_led()
{

  button_state_t new_state = RELEASED;
  byte reading = _sw.update();
  if (reading == LOW)
    new_state = PRESSED;

  unsigned long duration = 0;
  if (new_state != _last_button_state)
  {
    _last_button_state = new_state;
    if (_last_button_state == PRESSED)
      _last_command_time = millis();
    else
      duration = millis() - _last_command_time;
  }

  if (duration > 0)
  {
    if (duration < SHORT_TIME_MS)
      _command = LIGHT_ON;
    else if (duration < LONG_TIME_MS)
      _command = LIGHT_TOGGLE;
    else
      _command = LIGHT_OFF;
  }

  unsigned long blinking_duration = 0;
  switch (_command)
  {
  case LIGHT_OFF:
    _last_led_state = LOW;
    break;
  case LIGHT_ON:
    _last_led_state = HIGH;
    break;
  case LIGHT_TOGGLE:
    if (_last_blinking_time == 0)
      _last_blinking_time = millis();
    else
      blinking_duration = millis() - _last_blinking_time;
    if (blinking_duration > BLICKING_TIME_MS)
    {
      _last_led_state = !_last_led_state;
      _last_blinking_time = 0;
    }
    break;
  }
  _led.set_led(_last_led_state);
}
