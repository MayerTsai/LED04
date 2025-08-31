#include "my_led_driver.h"

const unsigned long SHORT_TIME_MS = 500;
const unsigned long LONG_TIME_MS = 1000;

LedDriver::LedDriver(Led &led, Button &sw) : _led(led), _sw(sw),
                                             _last_button_state(RELEASED),
                                             _command(LIGHT_OFF),
                                             _last_command_time(0),
                                             _last_led_state(LOW)
{
  _led.set_led(_last_led_state);
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
      _last_command_time == millis();
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

  switch (_command)
  {
  case LIGHT_OFF:
    _last_led_state = LOW;
  case LIGHT_ON:
     _last_led_state = HIGH;
  case LIGHT_TOGGLE:
     _last_led_state = !_last_led_state;
  }

  _led.set_led(_last_led_state);
}
