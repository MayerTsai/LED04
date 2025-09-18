#include <my_led.h>
#include <my_button.h>
#include <my_led_driver.h>

const byte LED_PIN = 3;
const byte SW_PIN = 9;

Led led1(LED_PIN);
Button sw1(SW_PIN);
LedDriver led_driver(led1, sw1);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  led_driver.update_led();
}
