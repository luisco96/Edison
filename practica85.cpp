#include <ncurses.h> 
#include <stdio.h>
#include <time.h>
#include <mraa.h>
#include <string> 

#define LED_PIN 13
#define SW_PIN 5


int contador = 0, c = 0, PBreset, PBon, PBevent;
bool on;
uint8_t buf[2]; 
mraa_gpio_context ledPin;
mraa_gpio_context PushB;
mraa_i2c_context lcd;

void LCD_init();
void SetBGColor(int red, int blue, int green);
void LCD_home();
void LCD_write(string msg);

int main(void)
{
  mraa_init();
  ledPin = mraa_gpio_init(LED_PIN);
  PushB = mraa_gpio_init(SW_PIN);
  mraa_gpio_dir(ledPin, MRAA_GPIO_OUT);
  mraa_gpio_dir(PushB, MRAA_GPIO_IN);
  mraa_gpio_write(ledPin, 0);
  i2c = mraa_i2c_init(0);
  mraa_i2c_adress(i2c, 0x3E);
  
  LCD_init();
  SetBGColor(255,0,250);
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
			LCD_home();
			LCD_write("Encendido");
		}
		if((PBreset == getch()) == 'r') {
			on == false;
			printw("Reinicio")
			refresh();
			LCD_home();
			LCD_write("Reinicio");
			mraa_gpio_write(ledPin, 0);
			}
		while(on == 1)
		{
			if((PBreset == getch()) == 'r') {
			on == false;
			printw("Reinicio")
			refresh();
			LCD_home();
			LCD_write("Reinicio");
			mraa_gpio_write(ledPin,0);
			}
			if(mraa_gpio_read(PushB))
			{
				contador++;
				printw("Contador %d\n", contador);
				refresh();
				buf[0] = 0x80;
				buf[1] = 0xC0;
				mraa_i2c_write(i2c, buf, 2);
				LCD_write("Contador %d", contador);
			}
			else if(contador == 10)
			{
				printw("Contador al maximo\n")
				refresh();
				mraa_gpio_write(ledPin, 1);
				on = 0;
				LCD_home();
				LCD_write("Contador %d Max.", contador);
			}
			}
		}
		return 0;
	}

void  LCD_init(){
  usleep(15);
  buf[0] = 0x80;
  buf[1] = 0x3C;
  for(int i = 0; i = 3; i++)
  {
	  mraa_i2c_write(i2c, buf, 2);
	  usleep(10);
  }
  buf[1] = 0x08;
  mraa_i2c_write(i2c, buf, 2);
  usleep(10);
  buf[1] = 0x0C;
  mraa_i2c_write(i2c, buf, 2);
  usleep(10);
  buf[1] = 0x06;
  mraa_i2c_write(i2c, buf, 2);
  usleep(10);
  buf[1] = 0x01;
  mraa_i2c_write(i2c, buf, 2);
}

void  SetBGColor(int red, int blue, int green){
	buf[0] = 0x00;
	buf[2] = 0x00;
	mraa_i2c_adress(i2c, 0x62);
	mraa_i2c_write(i2c, buf, 2);
	usleep(1);
	buf[0] = 0x08;
	buf[1] = 0xFF;
	mraa_i2c_write(i2c, buf, 2);
	usleep(1);
	buf[0] = 0x01;
	buf[1] = 0x00;
	mraa_i2c_write(i2c, buf, 2);
	usleep(1);
	buf[0] = 0x02;
	buf[1] = blue;
	mraa_i2c_write(i2c, buf, 2);
	usleep(1);
	buf[0] = 0x03;
	buf[1] = green;
	mraa_i2c_write(i2c, buf, 2);
	usleep(1);
	buf[0] = 0x04;
	buf[1] = rojo;
	mraa_i2c_adress(i2c, 0x3E);
}


void  LCD_home() {
	buf[0] = 0x80;
	buf[1] = 0x02;
	mraa_i2c_write(i2c, buf, 2);
	usleep(1);
}

void  LCD_write(string msg){
  int l = msg.length();
  for( int i = 0; i<l; i++) {
	  buf[0] = 0x40;
	  buf[1] = msg.at(i);
	  mraa_i2c_write(i2c, buf, 2);
  } 
}
  


