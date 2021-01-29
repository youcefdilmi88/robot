#ifndef PWM_PORTD_H
#define PWM_PORTD_H


#include <avr/io.h>
#include <LED_PORTA.h>
#include <avr/interrupt.h>


enum Direction {FORWARD, BACKWARD};

void init_pwm();
void set_pwm(uint8_t left_wheel_ratio, uint8_t right_wheel_ratio, Direction left_wheel_dir, Direction right_wheel_dir);
void setLeftWheel(uint8_t ratio, Direction direction);
void setRightWheel(uint8_t ratio, Direction direction);
#endif /* PWM_PORTD_H */
