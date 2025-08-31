#ifndef MY_LED_DRIVER_H
#define MY_LED_DRIVER_H

#include "my_led.h"
#include "my_button.h"

typedef enum{
RELEASED,
PRESSED
} button_state_t;

typedef enum{
  LIGHT_OFF,
  LIGHT_ON,
  LIGHT_TOGGLE
} light_command_t;

class LedDriver
{
private:
  Led& _led;
  Button& _sw;

  button_state_t _last_button_state;  
  light_command_t _command;
  unsigned long _last_command_time;
  byte _last_led_state;

public:
  LedDriver(Led &led, Button &sw);
  ~LedDriver() = default;
  LedDriver(const LedDriver &) = delete;
  LedDriver &operator=(const LedDriver &) = delete;

  void update_led();  // Update the LED state based on the button state
};
#endif // MY_LED_DRIVER_H