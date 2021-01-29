/*
 * File   : main.cpp
 * Author : Frederic Brossard-Pellerin (1908718) and Youcef Anis Dilmi (1895231)
 * Date   : 24/01/18
 * Descr  : TP3 Probleme 1
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
const uint8_t OFF = 0x00; // "DEL libre" is off when PORTA(0) is in logical state 0 and PORTA(1) is in logical state 0
const uint8_t INPUT = 0x00; // Port is in input mode
const uint8_t OUTPUT = 0xFF; // Port is in output mode

/*
 * Tableau d'etats :
 *__________________________________________________________________________________
|___Present State___|_____PORTD(input)____|____Next state___|_____PORTA(output)____|
|  INIT             |     0x04            | first_pressDown |       0x00           |
|  INIT             |     0x00            | INIT            |       0x00           |
|  first_pressDown  |     0x04            | wait_1          |       0x00           |
|  first_pressDown  |     0x00            | first_pressDown |       0x00           |
|  wait_1           |     0x04            | second_pressDown|       0x00           |
|  wait_1           |     0x00            | wait_1          |       0x00           |
|  second_pressDown |     0x04            | wait_2          |       0x00           |
|  second_pressDown |     0x00            | second_pressDown|       0x00           |
|  wait_2           |     0x04            | third_pressDown |       0x00           |
|  wait_2           |     0x00            | wait_2          |       0x00           |
|  third_pressDown  |     0x04            | wait_3          |       0x00           |
|  third_pressDown  |     0x00            | third_pressDown |       0x00           |
|  wait_3           |     0x04            | fourth_pressDown|       0x00           |
|  wait_3           |     0x00            | wait_3          |       0x00           |
|  fourth_pressDown |     0x04            | wait_4          |       0x00           |
|  fourth_pressDown |     0x00            | fourth_pressDown|       0x00           |
|  wait_4           |     0x04            | third_pressDown |       0x00           |
|  wait_4           |     0x00            | wait_4          |       0x00           |
|  fifth_pressDown  |     0x04            | INIT            |       0x01           |
|__fifth_pressDown__|_____0x00____________| INIT____________|_______0x01___________|
*/

int main()
{
	DDRA = OUTPUT; // PORT A is in output mode
	DDRD = INPUT; // PORT B is in input mode
	enum state_type {INIT, first_pressDown, wait_1, second_pressDown, wait_2, third_pressDown, wait_3, fourth_pressDown, wait_4, fifth_pressDown};
	state_type state = INIT;
	bool isPressed = false;

	for (;;)
	{
		isPressed = PIND & 0x04; // PORTD(2) receives high signal when "Interrupt" button is pressed
		_delay_ms(30);
		switch (state)
		{
			
			case INIT :
				PORTA = OFF;
				if (isPressed)
				{
					state = first_pressDown;
				}
				break;
				
			case first_pressDown :
				if (!isPressed)
				{
					state = wait_1;
				}
				break;
				
			case wait_1 :
				if (isPressed)
				{
					state = second_pressDown;
				}
				break;
				
			case second_pressDown :
				if (!isPressed)
				{
					state = wait_2;
				}
				break;
				
			case wait_2 :
				if (isPressed)
				{
					state = third_pressDown;
				}
				break;
				
			case third_pressDown :
				if (!isPressed)
				{
					state = wait_3;
				}
				break;
				
			case wait_3 :
				if (isPressed)
				{
					state = fourth_pressDown;
				}
				break;
				
			case fourth_pressDown :
				if (!isPressed)
				{
					state = wait_4;
				}
				break;
				
			case wait_4 :
				if (isPressed)
				{
					state = fifth_pressDown;
				}
				break;
				
			case fifth_pressDown :
				if (!isPressed)
				{
					PORTA = RED; // "DEL libre" lights up red // + connected to PORTA(0) // - connected to PORTA(1)
					_delay_ms(1000); // "DEL libre" stays red for 1 seconds
					state = INIT;
				}
				break;
				
		}
	}
	
	return 0;
	
}
