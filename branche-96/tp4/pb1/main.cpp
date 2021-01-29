/*
 * File   : main.cpp
 * Author : Frederic Brossard-Pellerin (1908718) and Youcef Anis Dilmi (1895231)
 * Date   : 01/02/18
 * Descr  : TP7 Probleme 1
*/


#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

const uint8_t ROUGE = 0x01;
const uint8_t VERT = 0x02;
const uint8_t ETEINT = 0x00;
const uint8_t ENTREE = 0x00;
const uint8_t SORTIE = 0xFF;

void delay_loop (int16_t delay)
{
    for (int16_t i=0; i < delay; i++) {
        _delay_us(30);
    }
}

int main()
{
DDRA = SORTIE;
DDRD = ENTREE;

  for (;;) {
      if (PIND & 0x04) {
          int16_t delay_ON = 100;
          int16_t delay_OFF = 0;
          for (int16_t i=0; i < 100 ; i++) {
              for (int16_t j=0; j < 30 ; j++){
                  PORTA = ROUGE;
                  delay_loop(delay_ON);
                  PORTA = ETEINT;
                  delay_loop(delay_OFF);
              }
              delay_ON -= 1;
              delay_OFF += 1;
          }
      }
  }
return 0; 
}

