#include "LED_PORTA.h"


/*******************************************************************
* @brief It is 1 millisecond delay loop, processor does nothing for 1 millisecond at every iterations
* @param iterations Number of iterations for delay_loop
* @return void
********************************************************************/
void delay_loop_ms(uint16_t iterations)
{
    for (uint16_t i=0; i<iterations; i++) {
        _delay_ms(1);
    }
}

/*******************************************************************
* @brief Makes LED flash RED
* @param delay_ms Number of milliseconds for LED RED coloration.
* @return void
*******************************************************************/
void error_red(uint16_t delay_ms)
{
    for(;;) {
        PORTC = RED;
        delay_loop_ms(delay_ms);
        PORTC = OFF;
        delay_loop_ms(delay_ms);
    }
}

/*******************************************************************
* @brief Makes LED flash GREEN
* @param delay_ms Number of milliseconds for LED GREEN coloration.
* @return void
*******************************************************************/
void error_green(uint16_t delay_ms)
{
    for(;;) {
        PORTA = GREEN;
        delay_loop_ms(delay_ms);
        PORTA = OFF;
        delay_loop_ms(delay_ms);
    }
}

/*******************************************************************
* @brief Makes LED flash RED and GREEN 3 times.
* @param delay_ms_1 Number of milliseconds for GREEN LED coloration
* @param delay_ms_2 Number of milliseconds for RED LED coloration.
* @return void
*******************************************************************/
void error_green_red(uint16_t delay_ms_green, uint16_t delay_ms_red)
{
    for(uint8_t i =0; i<3; i++) {
        PORTC = GREEN;
        delay_loop_ms(delay_ms_green);
        PORTC = RED;
        delay_loop_ms(delay_ms_red);
    }
}

/*******************************************************************
* @brief Makes LED flash RED at the beginning of mode Diagnostic.
* @param --
* @return void
*******************************************************************/
void LED_diagnostic()
{   for (uint8_t i=0; i<3; i++) {
        PORTC = RED;
        _delay_ms(750);
        PORTC = OFF;
        _delay_ms(500);
    }
}

/*******************************************************************
* @brief Makes LED flash GREEN at the beginning of mode Parcours.
* @param --
* @return void
*******************************************************************/
void LED_parcours()
{   for (uint8_t i=0; i<6; i++) {
        PORTC = GREEN;
        _delay_ms(750);
        PORTC = OFF;
        _delay_ms(500);
    }
}
