/*
 * File   : main.cpp
 * Author : Frederic Brossard-Pellerin (1908718) and Youcef Anis Dilmi (1895231)
 * Date   : 01/02/18
 * Descr  : TP5 Probleme 2
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
volatile bool boutonPoussoir = false;
volatile bool minuterieExpiree = false;

ISR (TIMER1_COMPA_vect)
{
minuterieExpiree = true;
}

ISR (INT0_vect)
{
boutonPoussoir = true;
_delay_ms(30);
}

void startTimerCTC(uint16_t top)
{
    compteur = 0x00;
    TCNT1 = 0x0000;
    OCR1A = top; // Interrupt after specific number of cycles 
    TCCR1A = 0; // Timer 1 CTC mode
    TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM12); // Clock/1024
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A); // Timer output compare A match interrupt vector enabled
}

void initialisation (void)
{
cli();
DDRD = INPUT;
DDRA = OUTPUT;
EIMSK |= (1<<INT0);// cette procédure ajuste le registre EIMSK de l’ATmega324PA pour permettre les interruptions externes
EICRA |= (1<<ISC00);// set INT0_vect to logical change
_delay_ms(5000);
for (uint8_t i=0; i<5; i++) {
PORTA = RED;
_delay_ms(10);
PORTA = OFF;
_delay_ms(20);
}
sei();
}
	
	
int main()
{
	initialisation();
	startTimerCTC(7812);
	while((!boutonPoussoir) && (!minuterieExpiree)) {
		PORTA = OFF;
	}
	cli();
	if (boutonPoussoir) {
		PORTA = GREEN;
	}
	if (minuterieExpiree) {
		PORTA = RED;
	}
	return 0;
}

