#ifndef LED_PORTA_H
#define LED_PORTA_H

#include <avr/io.h>
#include <util/delay.h>

const uint8_t RED = 0x01;
const uint8_t GREEN = 0x02;
const uint8_t OFF = 0x00;


void delay_loop_ms(uint16_t iterations);
void error_red(uint16_t delay_ms);
void error_green(uint16_t delay_ms);
void error_green_red(uint16_t delay_ms_green, uint16_t delay_ms_red);
void LED_start();
void LED_finish();

#endif /* LED_PORTA_H */
