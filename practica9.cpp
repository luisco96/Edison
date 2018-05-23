#include <ncurses.h> 
#include <stdio.h>
#include <time.h>
#include <mraa.h>

#define LED_PIN 13
#define SW_PIN 5

int contador = 0, c = 0, PBreset, PBon;
mraa_gpio_context ledPin;
mraa_gpio_context PushB;

int main(void)
{
  mraa_init();
  ledPin = mraa_gpio_init(LED_PIN);
  PushB = mraa_gpio_init(SW_PIN);
  
