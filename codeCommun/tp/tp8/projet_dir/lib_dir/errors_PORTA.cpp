#include "errors_PORTA.h"


const uint8_t RED = 0x01;
const uint8_t GREEN = 0x02;
const uint8_t OFF = 0x00;




/*
Connexions :
DEL libre = PORTA(0,1)
*/

/**
* @brief It is 1 millisecond delay loop, processor does nothing for 1 millisecond at every iterations
* @param iterations Number of iterations for delay_loop
* @return void
*/
void delay_loop_ms(uint16_t iterations)
{
    for (uint16_t i=0; i<iterations; i++) {
        _delay_ms(1);
    }
}

/**
* @brief Makes LED flash RED
* @param delay_ms Number of milliseconds for LED RED coloration.
* @return void
*/
void error_red(uint16_t delay_ms)
{
    for(;;) {
        PORTA = RED;
        delay_loop_ms(delay_ms);
        PORTA = OFF;
    }
}

/**
* @brief Makes LED flash GREEN
* @param delay_ms Number of milliseconds for LED GREEN coloration.
* @return void
*/
void error_green(uint16_t delay_ms)
{
    for(;;) {
        PORTA = GREEN;
        delay_loop_ms(delay_ms);
        PORTA = OFF;
    }
}

/**
* @brief Makes LED flash RED and GREEN
* @param delay_ms_1 Number of milliseconds for GREEN LED coloration
* @param delay_ms_2 Number of milliseconds for RED LED coloration.
* @return void
*/
void error_green_red(uint16_t delay_ms_1, uint16_t delay_ms_2)
{
    for(;;) {
        PORTA = GREEN;
        delay_loop_ms(delay_ms_1);
        PORTA = RED;
        delay_loop_ms(delay_ms_2);
    }
}
