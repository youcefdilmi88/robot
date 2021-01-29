/*
 * File   : main.cpp
 * Author : Frederic Brossard-Pellerin (1908718) and Youcef Anis Dilmi (1895231)
 * Date   : 01/02/18
 * Descr  : TP5 Probleme 3
*/


#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

/*constants*/
const uint8_t INPUT = 0x00;
const uint8_t OUTPUT = 0xFF;
const uint8_t TOP = 0xFF;
const uint8_t DIVBY100 = 0x64;


void signalPWM (uint8_t percentage, char direction) 
{
		uint8_t compareValue = ((percentage*TOP)/DIVBY100);
		
		if (direction == 'B') {
			PORTD |= (1 << 6) | (1 << 7);
		}
		
		if (direction == 'F') {
			PORTD &= ~((1 << 6) | (1 << 7));
		}
		
		if (direction == 'T') {
			PORTD &= ~(1 << 6);
			PORTD |= (1 << 7);
		}
		
		
		//set timer value
		TCNT1 = 0x0000;

		//Set compare value
		OCR1A = compareValue; // Outputs on PORTD[5] on compare match
		OCR1B = compareValue; // Outputs on PORTD[4] on compare match

		//Set mode #1 PWM, Phase correct, 8-bits, TOP 0x00FF (Table 17-6 p.177)
		//Set OC1A/OC1B on Compare Match when up-counting, clear OC1A/OC1B on Compare Match when down-counting. (Table 17-5 p.177)
		TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
		
		TCCR1C = 0x00;
		
		//set clock/8 (Table 17-7 p.179)
		TCCR1B |= (1 << CS11);
}

	
int main()
{
	DDRD = OUTPUT;
	
	signalPWM(0, 'F');
	_delay_ms(2000);
	signalPWM(25, 'F');
	_delay_ms(2000);
	signalPWM(50, 'F');
	_delay_ms(2000);
    signalPWM(75, 'F');
	_delay_ms(2000);
    signalPWM(100, 'F');
	_delay_ms(2000);
    
	
	return 0;
}

