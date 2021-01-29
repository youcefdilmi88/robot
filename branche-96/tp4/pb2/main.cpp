/*
 * File   : main.cpp
 * Author : Frederic Brossard-Pellerin (1908718) and Youcef Anis Dilmi (1895231)
 * Date   : 01/02/18
 * Descr  : TP4 Probleme 2
*/


#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <util/delay_basic.h>

const uint8_t HIGH_STATE = 0b00000001;
const uint8_t LOW_STATE =  0b00000000;
const uint8_t OUTPUT = 0xFF;


void delayLoop (uint16_t frequency, uint8_t percentage)
{
	unsigned int loop_iterations = (percentage*1000000)/(frequency*1000);
	for (uint16_t i=0; i < loop_iterations; i++) {
			_delay_us(10);
	}
}


void delay(uint16_t frequency, uint8_t percentage)
{
	int nDelayCycles = ((80000*percentage) / frequency);
	_delay_loop_2(nDelayCycles/4);
}


void move(char direction, uint16_t frequency, uint8_t percentage, uint8_t seconds)
{
	switch (direction) {

		case 'F':
							for (uint8_t i=0; i<(frequency*seconds); i++) {
									PORTD = (HIGH_STATE | 0b00000010);
									delayLoop(frequency, percentage);
									PORTD = (LOW_STATE | 0b00000010);
									delayLoop(frequency, (100-percentage));
							}
							break;

		case 'B':
							for (uint8_t i=0; i<(frequency*seconds); i++) {
									PORTD = HIGH_STATE;
									delayLoop(frequency, percentage);
									PORTD = LOW_STATE;
									delayLoop(frequency, (100-percentage));
							}
							break;
	}
}


int main() {

	DDRD = OUTPUT;
    /*
	move('F', 60, 0, 2);
	move('F', 60, 25, 2);
	move('F', 60, 50, 2);
	move('F', 60, 75, 2);
	move('F', 60, 100, 2);
*/
	move('F', 400, 0, 2);
	move('F', 400, 25, 2);
	move('F', 400, 50, 2);
	move('F', 400, 75, 2);
	move('F', 400, 100, 2);

return 0;

}
