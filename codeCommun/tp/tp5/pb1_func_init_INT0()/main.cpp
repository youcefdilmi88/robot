/*
 * File   : main.cpp
 * Author : Frederic Brossard-Pellerin (1908718) and Youcef Anis Dilmi (1895231)
 * Date   : 01/02/18
 * Descr  : TP5 Probleme 1
*/

/*
 * Connexions :
 * DEL libre = PORTA(0,1)
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*constants*/
const uint8_t RED = 0x01; // "DEL libre" lights up red when PORTA(1) is in logical state 1 and PORTA(2) is in logical state 0
const uint8_t GREEN = 0x02; // "DEL libre" lights up green when PORTA(1) is in logical state 0 and PORTA(2) is in logical state 1
const uint8_t OFF = 0x00; // "DEL libre" is off when PORTA(1) is in logical state 0 and PORTA(2) is in logical state 0
const uint8_t INPUT = 0x00; // Port is in input mode
const uint8_t OUTPUT = 0xFF; // Port is in output mode

/*variable globale*/
volatile bool isPressed = false;

/*
 * Tableau d'etats :
 *_________________________________________________________________________________
|___Present State___|_____PORTD(input)____|____Next state___|_____PORTA(output)____|
|  INIT             |     0x04            | first_pressDown |       0x01           |
|  INIT             |     0x00            | INIT            |       0x01           |
|  first_pressDown  |     0x04            | first_pressDown |       0x01/0x02      |
|  first_pressDown  |     0x00            | first_release   |       0x01/0x02      |
|  first_release    |     0x04            | second_pressDown|       0x02           |
|  first_release    |     0x00            | first_release   |       0x02           |
|  second_pressDown |     0x04            | second_pressDown|       0x01           |
|  second_pressDown |     0x00            | second_release  |       0x01           |
|  second_release   |     0x04            | third_pressDown |       0x00           |
|  second_release   |     0x00            | second_release  |       0x00           |
|  third_pressDown  |     0x04            | third_pressDown |       0x02           |
|__third_pressDown__|_____0x00____________|_INIT____________|_______0x02___________|
*/

void LED_isAmber()
{
	PORTA = RED;
	_delay_ms(10);
	PORTA = GREEN;
	_delay_ms(3);
}


ISR (INT0_vect)
{
	_delay_ms ( 30 );
	if (PIND & 0x04) {
		isPressed = true;
	}
	else {
		isPressed = false;
	}
}

void init_INT0(void)
{
    cli (); // cli() bloque les interruptions.
    DDRD = INPUT; // PORTD is in input mode
    DDRA = OUTPUT; // PORTA is in output mode
    EIMSK |= (1 << INT0); // Enable external interrupts
    EICRA |= (1<<ISC00); // Set INT0_vect to logical change 
    sei (); // sei permet de recevoir à nouveau des interruptions.
}
	
	
int main()
{
	init_INT0();
	enum state_type {INIT, first_pressDown, first_release, second_pressDown, second_release, third_pressDown};
	state_type state = INIT;

	for (;;) {
		switch (state)
		{
			case INIT :
				PORTA = RED;
				if (isPressed)
				{
					state = first_pressDown;
				}
				break;

			case first_pressDown :
				LED_isAmber();
				if (!isPressed)
				{
					state = first_release;
				}
				break;

			case first_release :
				PORTA = GREEN;
				if (isPressed)
				{
					state = second_pressDown;
				}
				break;

			case second_pressDown :
				PORTA = RED;
				if (!isPressed)
				{
					state = second_release;
				}
				break;

			case second_release :
				PORTA = OFF;
				if (isPressed)
				{
					state = third_pressDown;
				}
				break;

			case third_pressDown :
				PORTA = GREEN;
				if (!isPressed)
				{
					state = INIT;
				}
		}
	}

	return 0;

}
