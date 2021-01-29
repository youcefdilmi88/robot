
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

/*constants*/
const uint8_t RED = 0x01; // "DEL libre" lights up red when PORTA(0) is in logical state 1 and PORTA(1) is in logical state 0
const uint8_t GREEN = 0x02; // "DEL libre" lights up green when PORTA(0) is in logical state 0 and PORTA(1) is in logical state 1

void LED_isAmber()
{
	PORTA = RED;
	_delay_ms(10);
	PORTA = GREEN;
	_delay_ms(3);
}
