#include "LED_PORTA.h"


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
        delay_loop_ms(delay_ms);
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
        delay_loop_ms(delay_ms);
    }
}

/**
* @brief Makes LED flash RED and GREEN
* @param delay_ms_1 Number of milliseconds for GREEN LED coloration
* @param delay_ms_2 Number of milliseconds for RED LED coloration.
* @return void
*/
void error_green_red(uint16_t delay_ms_green, uint16_t delay_ms_red)
{
    for(;;) {
        PORTA = GREEN;
        delay_loop_ms(delay_ms_green);
        PORTA = RED;
        delay_loop_ms(delay_ms_red);
    }
}

void LED_start()
{   for (uint8_t i=0; i<3; i++) {
        PORTA = RED;
        _delay_ms(750);
        PORTA = OFF;
        _delay_ms(500);
    }
        PORTA = GREEN;
       _delay_ms(1000);
        PORTA = OFF;
}


void LED_finish()
{   for (uint8_t i=0; i<3; i++) {
        PORTA = GREEN;
        _delay_ms(750);
        PORTA = OFF;
        _delay_ms(500);
    }
        PORTA = RED;
       _delay_ms(1000);
        PORTA = OFF;
}
