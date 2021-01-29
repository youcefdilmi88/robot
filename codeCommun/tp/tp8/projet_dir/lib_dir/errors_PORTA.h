#ifndef ERRORS_PORTA_H
#define ERRORS_PORTA_H

#include <avr/io.h>
#include <util/delay.h>

void delay_loop(uint16_t delay);
void error_red(uint16_t delay_ms);
void error_green(uint16_t delay_ms);
void error_green_red(uint16_t delay_ms_1, uint16_t delay_ms_2);

#endif /* ERRORS_PORTA_H */