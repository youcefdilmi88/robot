#ifndef PWM_PORTD_H
#define PWM_PORTD_H


#include <avr/io.h>
#include <errors_PORTA.h>


enum Direction {FORWARD, BACKWARD};

void init_pwm();
void set_pwm(uint8_t left_wheel_ratio, uint8_t right_wheel_ratio, Direction left_wheel_dir, Direction right_wheel_dir);


#endif /* PWM_PORTD_H */