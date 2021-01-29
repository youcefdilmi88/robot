/*
 * File   : main.cpp
 * Author : Frederic Brossard-Pellerin (1908718) and Youcef Anis Dilmi (1895231)
 * Date   : 01/02/18
 * Descr  : TP4 Probleme 2
*/



#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

const uint8_t HIGH_STATE_FWD = 0x03;
const uint8_t LOW_STATE_FWD = 0x02;
const uint8_t HIGH_STATE_BWD = 0x01;
const uint8_t LOW_STATE_BWD = 0x00;
const uint8_t STOP = 0x00;
const uint8_t OUTPUT = 0xFF;
const int PERIOD_60Hz_us = 16667;
const int PERIOD_25_60Hz_us = 4167;

const int PERIOD_25_400Hz_us = 625;
const int PERIOD_50_400Hz_us = 1250;
const int PERIOD_75_400Hz_us = 1875;
const int PERIOD_100_400Hz_us = 2500;


void move60Hz(char direction, int percentage, int seconds)
{

	if (direction == 'F') {
			for (int i = 0; i < 60*seconds; i++) {
				
				switch (percentage) {
				
				case 0: 
				PORTD = LOW_STATE_FWD;
				_delay_us(PERIOD_60Hz_us);
				break;
			
				case 25:
				PORTD = HIGH_STATE_FWD;
				_delay_us(PERIOD_25_60Hz_us);
				PORTD = LOW_STATE_FWD;
				_delay_us(PERIOD_60Hz_us-PERIOD_25_60Hz_us);
				 break;
				
				case 50:
				PORTD = HIGH_STATE_FWD;
				_delay_us(PERIOD_60Hz_us/2);
				PORTD = LOW_STATE_FWD;
				_delay_us(PERIOD_60Hz_us/2);
				break;
				
				case 75:
				PORTD = HIGH_STATE_FWD;
				_delay_us(PERIOD_60Hz_us-PERIOD_25_60Hz_us);
				PORTD = LOW_STATE_FWD;
				_delay_us(PERIOD_25_60Hz_us);
				break;
				
				case 100: 
				PORTD = HIGH_STATE_FWD;
				_delay_us(PERIOD_60Hz_us);
				break;
				}
			}
		}

	if (direction == 'B') {
			for (int i = 0; i < 60*seconds; i++) {
				
				switch (percentage) {
				
				case 0: 
				PORTD = LOW_STATE_BWD;
				_delay_us(PERIOD_60Hz_us);
				break;
			
				case 25:
				PORTD = HIGH_STATE_BWD;
				_delay_us(PERIOD_25_60Hz_us);
				PORTD = LOW_STATE_BWD;
				_delay_us(PERIOD_60Hz_us-PERIOD_25_60Hz_us);
				 break;
				
				case 50:
				PORTD = HIGH_STATE_BWD;
				_delay_us(PERIOD_60Hz_us/2);
				PORTD = LOW_STATE_BWD;
				_delay_us(PERIOD_60Hz_us/2);
				break;
				
				case 75:
				PORTD = HIGH_STATE_BWD;
				_delay_us(PERIOD_60Hz_us-PERIOD_25_60Hz_us);
				PORTD = LOW_STATE_BWD;
				_delay_us(PERIOD_25_60Hz_us);
				break;
				
				case 100: 
				PORTD = HIGH_STATE_BWD;
				_delay_us(PERIOD_60Hz_us);
				break;
				}
			}
		}
	PORTD = STOP;
}

void move400Hz(char direction, int percentage, int seconds)
{

	if (direction == 'F') {
				
				switch (percentage) {
				
					case 0: 
					for (int i = 0; i < 400*seconds; i++){
						PORTD = LOW_STATE_FWD;
						_delay_us(PERIOD_100_400Hz_us);
					}
					break;
				
					case 25:
					for (int i = 0; i < 400*seconds; i++){
						PORTD = HIGH_STATE_FWD;
						_delay_us(PERIOD_25_400Hz_us);
						PORTD = LOW_STATE_FWD;
						_delay_us(PERIOD_75_400Hz_us);
					}
					 break;
					
					case 50:
					for (int i = 0; i < 400*seconds; i++){
					PORTD = HIGH_STATE_FWD;
					_delay_us(PERIOD_50_400Hz_us);
					PORTD = LOW_STATE_FWD;
					_delay_us(PERIOD_50_400Hz_us);
					}
					break;
					
					case 75:
					for (int i = 0; i < 400*seconds; i++){
						PORTD = HIGH_STATE_FWD;
						_delay_us(PERIOD_75_400Hz_us);
						PORTD = LOW_STATE_FWD;
						_delay_us(PERIOD_25_400Hz_us);
					}
					break;
					
					case 100: 
					for (int i = 0; i < 400*seconds; i++){
						PORTD = HIGH_STATE_FWD;
						_delay_us(PERIOD_100_400Hz_us);
					}
					break;
				}
	}

	if (direction == 'B') {
				
				switch (percentage) {
				
					case 0: 
					for (int i = 0; i < 400*seconds; i++){
						PORTD = LOW_STATE_BWD;
						_delay_us(PERIOD_100_400Hz_us);
					}
					break;
				
					case 25:
					for (int i = 0; i < 400*seconds; i++){
						PORTD = HIGH_STATE_BWD;
						_delay_us(PERIOD_25_400Hz_us);
						PORTD = LOW_STATE_BWD;
						_delay_us(PERIOD_75_400Hz_us);
					}
					 break;
					
					case 50:
					for (int i = 0; i < 400*seconds; i++){
						PORTD = HIGH_STATE_BWD;
						_delay_us(PERIOD_50_400Hz_us);
						PORTD = LOW_STATE_BWD;
						_delay_us(PERIOD_50_400Hz_us);
					}
					break;
					
					case 75:
					for (int i = 0; i < 400*seconds; i++){
						PORTD = HIGH_STATE_BWD;
						_delay_us(PERIOD_75_400Hz_us);
						PORTD = LOW_STATE_BWD;
						_delay_us(PERIOD_25_400Hz_us);
					}
					break;
					
					case 100: 
					for (int i = 0; i < 400*seconds; i++){
						PORTD = HIGH_STATE_BWD;
						_delay_us(PERIOD_100_400Hz_us);
					}
					break;
				}
	}
	PORTD = STOP;
}

int main()
{
	


	DDRD = OUTPUT;


	move60Hz('F', 0, 2);
	move60Hz('F', 25, 2);
	move60Hz('F', 50, 2);
	move60Hz('F', 75, 2);
	move60Hz('F', 100, 2);

	move400Hz('F', 0, 2);
	move400Hz('F', 25, 2);
	move400Hz('F', 50, 2);
	move400Hz('F', 75, 2);
	move400Hz('F', 100, 2);


return 0; 
}
