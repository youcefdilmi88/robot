/*
 * File   : main.cpp
 * Author : Frederic Brossard-Pellerin (1908718) and Youcef Anis Dilmi (1895231)
 * Date   : 01/02/18
 * Descr  : TP6 Probleme 1
*/




#include "memoire_24.h"
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <stdio.h>

/*constants*/
const uint8_t RED = 0x01;
const uint8_t GREEN = 0x02;
const uint8_t OFF = 0x00;
const uint8_t IN = 0x00;
const uint8_t OUT = 0xFF;

int main()
{


Memoire24CXXX moBoMem;

uint8_t writeMessage[40] = "*E*C*O*L*E* *P*O*L*Y*T*E*C*H*N*I*Q*U*E*";
uint8_t writeNumber = 0x00;
moBoMem.ecriture(0x0000, writeMessage, 0x28);
moBoMem.ecriture(0x0028, &writeNumber, 0x01);
_delay_ms(2000);
uint8_t readMessage[40];
uint8_t readNumber;
moBoMem.lecture(0x0000, readMessage, 0x28);
moBoMem.lecture(0x0028, &readNumber, 0x01);
DDRA = OUT;

if (*writeMessage == *readMessage) {
PORTA = GREEN;
_delay_ms(3000);
}else {
PORTA = RED;
_delay_ms(3000);
}
PORTA = OFF;

_delay_ms(3000);

if (writeNumber == readNumber) {
PORTA = GREEN;
_delay_ms(3000);
}else {
PORTA = RED;
_delay_ms(3000);
}
PORTA = OFF;

return 0;
}
