#ifndef MY_LED_DRIVER_H
#define MY_LED_DRIVER_H

#include "my_led.h"
#include "my_button.h"

enum class button_state_t
{
  RELEASED,
  PRESSED
};

enum class light_command_t
{
  LIGHT_OFF,
  LIGHT_ON,
  LIGHT_TOGGLE
};

class LedDriver
{
private:
  Led &_led;
  Button &_sw;

  button_state_t _button_state;
  unsigned long _last_button_state_time;
  light_command_t _command;
  byte _led_state;
  unsigned long _last_blinking_time;

  unsigned long get_duration_ms(char *mode);
  void set_command(unsigned long duration);
  void set_led_state();

public:
  LedDriver(Led &led, Button &sw);
  ~LedDriver() = default;
  LedDriver(const LedDriver &) = delete;
  LedDriver &operator=(const LedDriver &) = delete;

  void update_led(); // Update the LED state based on the button state
};
#endif // MY_LED_DRIVER_H