#include <ncurses.h> 
#include <stdio.h>
#include <time.h>
#include <mraa.h>
#include "rgb_lcd.h"

#define LED_PIN 13
#define SW_PIN 5
rgb_lcd lcd;

int contador = 0, c = 0, PBreset, PBon, PBevent;
bool on;
mraa_gpio_context ledPin;
mraa_gpio_context PushB;

int main(void)
{
  mraa_init();
  ledPin = mraa_gpio_init(LED_PIN);
  PushB = mraa_gpio_init(SW_PIN);
  mraa_gpio_dir(ledPin, MRAA_GPIO_OUT);
  mraa_gpio_dir(PushB, MRAA_GPIO_IN);
  mraa_gpio_write(ledPin, 0);
  
  lcd.begin(16,2);
  lcd.setRGB(255,0,250);
  lcd.home();
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, true);
  printw("Contador, oprimir tecla o para comenzar\n Push button\
	en Edison aumenta contador\n Reset: tecla r\n");
	refresh();
	
	while(1)
	{
		if((PBon == getch()) == 'o') 
		{
			on == true;
			printw("Encendido/n");
			refresh();
			lcd.clear();
			lcd.print("Encendido");
		}
		if((PBreset == getch()) == 'r') {
			on == false;
			printw("Reinicio")
			refresh();
			lcd.clear();
			lcd.print("Reinicio");
			mraa_gpio_write(ledPin, 0);
			}
		while(on == 1)
		{
			if((PBreset == getch()) == 'r') {
			on == false;
			printw("Reinicio")
			refresh();
			lcd.clear();
			lcd.print("Reinicio");
			mraa_gpio_write(ledPin,0);
			}
			if(mraa_gpio_read(PushB))
			{
				contador++;
				printw("Contador %d\n", contador);
				refresh();
				lcd.setCursor(0,2);
				lcd.print("Contador %d", contador);
			}
			else if(contador == 10)
			{
				printw("Contador al maximo\n")
				refresh();
				mraa_gpio_write(ledPin, 1);
				on = 0;
				lcd.setCursor(0,2);
				lcd.print("Contador %d Max.", contador);
			}
			}
		}
		return 0;
	}
		


