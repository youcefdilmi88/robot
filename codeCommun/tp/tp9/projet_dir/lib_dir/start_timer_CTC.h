#ifndef START_TIMER_CTC_H
#define START_TIMER_CTC_H

#include <avr/io.h>

void startTimerCTC_INT(uint16_t top);
void startTimerCTC_WGM(uint16_t top);

#endif /* START_TIMER_CTC_H */
