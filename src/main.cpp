#include <my_led.h>
#include <my_button.h>
#include <my_led_driver.h>

Led *led1 = NULL;
Button *sw1 = NULL;
LedDriver *led_driver = NULL;

void setup()
{
  led1 = new Led(3);
  sw1 = new Button(9);
  led_driver = new LedDriver(*led1, *sw1);
  Serial.begin(9600);
}

void loop()
{
  led_driver->update_led();
}
