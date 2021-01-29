#include "start_timer_CTC.h"



/**
* @brief Controls speed and rotation direction of each wheel
* @param left_wheel_ratio Number between 0 and 255 that represents ratio on 255 for PWM signal
* @return void
*/
void startTimerCTC_INT(uint16_t top)
{
    OCR1A = top; // Interruption after specific number of cycles 
    TCCR1A = 0; // Puts timer1 in CTC mode
    TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM12); // Clock/1024
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A); // Timer output compare A match interrupt vector enabled (TIMER1_COMPA_vect)
}

void startTimerCTC_WGM(uint16_t top)
{
    OCR0A = top;
    TCCR0A |= (1 << COM0A0) | (1 << WGM01);
    TCCR0B |= (1 << CS02) | (1 << CS00);
}