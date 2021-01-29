#include "PWM_PORTD.h"
#include "LED_PORTA.h"







/*******************************************************************
* @brief Initialize PWM signal by entering values in specific registers
* @param --
* @return void
********************************************************************/
void init_pwm()
{
    cli();
    TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
    TCCR1B |= (1 << CS11);
    TCCR1C = 0x00;
    sei();
}


/**********************************************************************************************************
* @brief Controls speed and rotation direction of each wheel
* @param left_wheel_ratio Number between 0 and 255 that represents ratio on 255 for PWM signal
* @param right_wheel_ratio Number between 0 and 255 that represents ratio on 255 for PWM signal
* @param left_wheel_dir enum variable to decide if we send signal to wheel for forward or backward rotation
* @param right_wheel_dir enum variable to decide if we send signal to wheel for forward or backward rotation
* @return void0
***********************************************************************************************************/
void set_pwm(uint8_t left_wheel_ratio, uint8_t right_wheel_ratio, Direction left_wheel_dir, Direction right_wheel_dir)
{
    OCR1A = right_wheel_ratio; //Value compared with timer value for PWM signal
    OCR1B = left_wheel_ratio; //Value compared with timer value for PWM signal

    switch (left_wheel_dir){
        case FORWARD:
            PORTD &= ~(1 << 6); //Outputs low logical level in PORTD(6) for forward rotation
            break;
        case BACKWARD:
            PORTD |= (1 << 6); //Outputs high logical level in PORTD(6) for backward rotation
            break;
        default:
            error_green(500); //Outputs green light in LED if bug occurs
    }

    switch (right_wheel_dir){
        case FORWARD:
            PORTD &= ~(1 << 7); //Outputs low logical level in PORTD(7) for forward rotation
            break;
        case BACKWARD:
            PORTD |= (1 << 7); //Outputs high logical level in PORTD(7) for backward rotation
            break;
        default:
            error_red(500); //Outputs red light in LED if bug occurs
    }
}

/*******************************************************************
* @brief Change la direction de la roue gauche.
* @param uint8_t la fréquence du PWM
* @param Direction la direction de la roue (FORWARD ou BACKWARD)
* @return void
********************************************************************/
void setLeftWheel(uint8_t ratio, Direction direction)
{
    OCR1B = ratio;
    switch (direction)
    {
        case FORWARD:
            PORTD &= ~(1 << 6); //Outputs low logical level in PORTD(6) for forward rotation
            break;
        case BACKWARD:
            PORTD |= (1 << 6); //Outputs high logical level in PORTD(6) for backward rotation
            break;
        default:
            break;
    }
}

/*******************************************************************
* @brief Change la direction de la roue droite.
* @param uint8_t la fréquence du PWM
* @param Direction la direction de la roue (FORWARD ou BACKWARD)
* @return void
********************************************************************/
void setRightWheel(uint8_t ratio, Direction direction)
{
    OCR1A = ratio;
    switch (direction)
    {
        case FORWARD:
            PORTD &= ~(1 << 7); //Outputs low logical level in PORTD(7) for forward rotation
            break;
        case BACKWARD:
            PORTD |= (1 << 7); //Outputs high logical level in PORTD(7) for backward rotation
            break;
        default:
            break;
    }

}
