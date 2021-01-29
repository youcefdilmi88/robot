#include "start_timer_CTC.h"



/*********************************************************************************************
* @brief Controls speed and rotation direction of each wheel
* @param left_wheel_ratio Number between 0 and 255 that represents ratio on 255 for PWM signal
* @return void
*********************************************************************************************/
void startTimerCTC_INT_1(uint16_t top)
{

    OCR1A = top; // Interrupt after specific number of cycles 
    TCCR1A = 0; // Timer 1 CTC mode
    TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM12); // Clock/1024
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A);
    sei();

}

/*********************************
* @brief Réinitialise le timer 1
* @param --
* @return void
*********************************/
void clearTimerCTC_INT_1()
{

    OCR1A = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1C = 0;
    TIMSK1 = 0;
}

/**************************************************************************************
* @brief Initialise le timer 2 afin qu'il compte jusqu'à la valeur passée en paramètre.
* @param uint8_t top, la valeur maximale du timer.
* @return void
***************************************************************************************/
void startTimerCTC_INT_2(uint8_t top)
{
    OCR2A = top; // Interrupt after specific number of cycles 
    TCCR2A = 1 << WGM21; // Timer 1 CTC mode
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // Clock/1024
    TIMSK2 |= (1 << OCIE2A);
    sei();
}

/*********************************
* @brief Réinitialise le timer 2
* @param --
* @return void
*********************************/
void clearTimerCTC_INT_2()
{
    OCR2A = 0;
    TCCR2A = 0;
    TCCR2B = 0;
    TIMSK2 = 0;
}

/**************************************************************************************
* @brief Initialise le timer 0 afin qu'il compte jusqu'à la valeur passée en paramètre.
* @param uint8_t top, la valeur maximale du timer.
* @return void
***************************************************************************************/
void startTimerCTC_INT_0(uint16_t top)
{
    cli();
    OCR0A = top; // Interruption after specific number of cycles 
    TCCR0A |= (1 << WGM01); // Puts timer1 in CTC mode
    TCCR0B |= (1 << CS00) | (1 << CS02); // Clock/1024
    TIMSK0 |= (1 << OCIE0A); // Timer output compare A match interrupt vector enabled (TIMER1_COMPA_vect)
    sei();
}

/**************************************************************************************
* @brief Initialise le timer 0 afin qu'il compte jusqu'à la valeur passée en paramètre.
* @param uint8_t top, la valeur maximale du timer.
* @return void
***************************************************************************************/
void startTimerCTC_WGM(uint16_t top)
{
    OCR0A = top;
    TCCR0A |= (1 << COM0A0) | (1 << WGM01);
    TCCR0B |= (1 << CS02) | (1 << CS00);
}


/*********************************
* @brief Réinitialise le timer 0
* @param --
* @return void
*********************************/
void clearTimerCTC_WGM()
{    
    OCR0A = 0;
    TCCR0A = 0;
    TCCR0B = 0;
}
