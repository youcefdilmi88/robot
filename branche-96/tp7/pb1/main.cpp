/*
 * File   : main.cpp
 * Author : Frederic Brossard-Pellerin (1908718) and Youcef Anis Dilmi (1895231)
 * Date   : 01/02/18
 * Descr  : TP7 Probleme 1
*/

/*
 * Connexions :
 * DEL libre = PORTA(0,1)
 * Bouton poussoir breadboard = PORTD(2,3)
 * Alimentation breadboard = PORTA(VCC. GND)
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*constants*/
const uint8_t RED = 0x01; 
const uint8_t GREEN = 0x02; 
const uint8_t OFF = 0x00; 
const uint8_t INPUT = 0x00;
const uint8_t OUTPUT = 0xFF; 
const uint16_t TENTH_SECOND_TOP = 0x030D;
const uint8_t DIV_BY_2 = 0x02;
const uint8_t TOP_120 = 0x78;

/*global variables*/
volatile bool isPressed = false;
volatile uint8_t compteur = 0x00;


ISR(INT0_vect)
{
    _delay_ms (30);
    if (PIND & 0x04) {
        isPressed = false;
    }
    else {
        isPressed = true;
    }
}

ISR(TIMER1_COMPA_vect)
{
    compteur++;
}

void initialisation(void)
{
    cli (); // cli() bloque les interruptions.
    DDRD = INPUT; // PORTD is in input mode
    DDRA = OUTPUT; // PORTA is in output mode
    EIMSK |= (1 << INT0); // Enable external interrupts
    EICRA |= (1<<ISC00); // Set INT0_vect to logical change 
    sei (); // sei permet de recevoir à nouveau des interruptions.
}
	
void startTimer(uint16_t top)
{
    compteur = 0x00;
    TCNT1 = 0x0000;
    OCR1A = top; // Interrupt after specific number of cycles 
    TCCR1A = 0; // Timer 1 CTC mode
    TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM12); // Clock/1024
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A); // Timer output compare A match interrupt vector enabled
}

int main()
{
    initialisation();
    for (;;) {
        while (!isPressed)
        {}
        startTimer(TENTH_SECOND_TOP);
        while (isPressed && (compteur < TOP_120))
        {}
        cli();
        for (uint8_t i = 0; i < 0x04; i++) {
            PORTA = OFF;
            _delay_ms(125);
            PORTA = GREEN;
            _delay_ms(125);
        }
        PORTA=OFF;
        _delay_ms(2000);
        for (uint8_t i = 0; i < (compteur/DIV_BY_2); i++) {
            PORTA = OFF;
            _delay_ms(400);
            PORTA = RED;
            _delay_ms(100);
        }
        PORTA = GREEN;
        _delay_ms(1000);
        PORTA = OFF;
        sei();
    }
    return 0;
}





























   /* initialisation();
    enum state_type {INIT, first_pressDown, first_condition};
    state_type state = INIT;
    uint8_t compteur = 0;

    for (;;) {
        switch (state)
        {
            case INIT :
                if (isPressed) {
                    state = first_pressDown;
                    startTimer(100);
                }
                break;

            case first_pressDown :
                if ( (!isPressed) || (compteur == 50) ) {
                    state = first_condition;
                }
                break;

            case first_condition :
                for ( uint8_t i = 0; i < 4; i++ ) {
                    PORTA = OFF;
                    _delay_ms(125);
                    PORTA = GREEN;
                    _delay_ms(125);
                }
                PORTA = OFF;
                _delay_ms(2000);
                for ( uint8_t i = 0; i < 10; i++ ) {
                    PORTA = OFF;
                    _delay_ms(400);
                    PORTA = RED;
                    _delay_ms(100);
                }
                PORTA = GREEN;
                _delay_ms(1000);
                PORTA = OFF;
                state = INIT;
                break;
        }
    }
*/
