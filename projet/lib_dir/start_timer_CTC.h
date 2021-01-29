#ifndef START_TIMER_CTC_H
#define START_TIMER_CTC_H

#include <avr/io.h>
#include <avr/interrupt.h>

void startTimerCTC_INT_1(uint16_t top);
void startTimerCTC_INT_0(uint16_t top);
void startTimerCTC_WGM(uint16_t top);
void clearTimerCTC_INT_1();
void clearTimerCTC_WGM();
void clearTimerCTC_INT_2();
void startTimerCTC_INT_2(uint8_t top);

#endif /* START_TIMER_CTC_H */
