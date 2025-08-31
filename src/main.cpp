#include <my_led.h>
#include <my_button.h>
#include <my_led_driver.h>

const byte LED_PIN = 3;
const byte SW_PIN = 9;

Led *led1 = NULL;
Button *sw1 = NULL;
LedDriver *led_driver = NULL;

void setup()
{
  led1 = new Led(LED_PIN);
  sw1 = new Button(SW_PIN);
  led_driver = new LedDriver(*led1, *sw1);
  Serial.begin(9600);
}

void loop()
{
  led_driver->update_led();
}
