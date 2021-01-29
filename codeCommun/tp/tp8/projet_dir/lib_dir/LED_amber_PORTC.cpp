#include "LED_amber_PORTC.h"

const uint8_t RED = 0x01;
const uint8_t GREEN = 0x02;
const uint8_t OFF = 0x00;


/*Connexions
DEL libre = PORTC(0,1)
/**
* @brief Put LED light in amber coloration
* @return void
*/
void LED_amber()
{
	PORTC = RED;
	_delay_ms(10);
	PORTC = GREEN;
	_delay_ms(3);
}
