/*
 * File   : main.cpp
 * Author : Frederic Brossard-Pellerin (1908718) and Youcef Anis Dilmi (1895231)
 * Date   : 01/02/18
 * Descr  : TP7 Probleme 2
*/

/*
 * Connexions :
 * DEL libre = PORTC(0,1)
 * Photo-résistance = PORTA(0)
 * Alimentation breadboard = PORTA(VCC. GND)
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <can.h>


/*constants*/
const uint8_t RED = 0x01;
const uint8_t GREEN = 0x02;
const uint8_t OFF = 0x00;
const uint8_t INPUT = 0x00;
const uint8_t OUTPUT = 0xFF;
const uint8_t BORNE_INFERIEUR = 200;
const uint8_t BORNE_SUPERIEUR = 230;



void LED_isAmber()
{
    PORTC = RED;
    _delay_ms(2);
    PORTC = GREEN;
    _delay_ms(10);
}


int main()
{
    DDRC = OUTPUT;
    can myCan = can();

    for(;;) {
        uint16_t signalPhotoRes = (myCan.lecture(0));
        uint8_t donnee = ((signalPhotoRes >> 2) & 0x00FF);

        if (donnee < BORNE_INFERIEUR) {
            PORTC = GREEN;
        }

        if ((donnee > BORNE_INFERIEUR) && (donnee < BORNE_SUPERIEUR)) {
            LED_isAmber();
        }

        if (donnee > BORNE_SUPERIEUR) {
          PORTC = RED;
        }
    }
    return 0;
}



