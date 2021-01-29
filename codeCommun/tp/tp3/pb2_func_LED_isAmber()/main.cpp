/*
 * File   : main.cpp
 * Author : Frederic Brossard-Pellerin (1908718) and Youcef Anis Dilmi (1895231)
 * Date   : 01/02/18
 * Descr  : TP3 Probleme 2
*/

/*
 * Connexions :
 * DEL libre = PORTA(0,1)
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

/*constants*/
const uint8_t RED = 0x01; // "DEL libre" lights up red when PORTA(0) is in logical state 1 and PORTA(1) is in logical state 0
const uint8_t GREEN = 0x02; // "DEL libre" lights up green when PORTA(0) is in logical state 0 and PORTA(1) is in logical state 1
const uint8_t OFF = 0x00; // "DEL libre" is off when PORTA(0) is in logical state 0 and PORTA(1) is in logical state 0
const uint8_t INPUT = 0x00; // Port is in input mode
const uint8_t OUTPUT = 0xFF; // Port is in output mode

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

/*
* Réponses aux questions du TP:
*
* Pour le problème 1, il est nécéssaire de faire un antirebond parce que
* si le système pense que le bouton est appuyé et relâché plusieurs fois rapidement,
* il passera aux états suivants et ceci fera que le système ne répondra pas à l'appui du bouton comme demandé.
*
* Pour le problème 2, il n'est pas nécéssaire de faire un antirebond parce le TP demande à ce que l'on garde notre doigt
* appuyé sur le bouton, ce qui empêche le phénomène de rebond.
*
* Pour écouler une seconde, le nombre de cycle de délai est de 16 000 000 dans le cas d'un microcontrôlleur qui roule à 16MHz.
* Ce sera 8 192 000 cycles pour un microcontrôlleur qui roule à 8.192 MHz.
*
*/

void LED_isAmber()
{
	PORTA = RED;
	_delay_ms(10);
	PORTA = GREEN;
	_delay_ms(3);
}

int main()
{
	DDRA = OUTPUT; // PORTA is in output mode
	DDRD = INPUT; // PORTB is in input mode
	enum state_type {INIT, first_pressDown, first_release, second_pressDown, second_release, third_pressDown};
	state_type state = INIT;
	bool isPressed = false;

	for (;;)
	{
		isPressed = PIND & 0x04; // PORTD(2) receives high signal when "Interrupt" button is pressed
		_delay_ms(30);

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
