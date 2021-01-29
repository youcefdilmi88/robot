#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include "func_UART.h"
#include "start_timer_CTC.h"
#include "sensors.h"
#include "value_to_interval.h"
#include "PWM_PORTD.h"
#include "LED_PORTA.h"
#include <avr/io.h>



enum Instruction {NAME = 0xF0, TEAM = 0xF1, SECTION = 0xF2, SESSION = 0xF3, BASE_COLOR = 0xF4, BUTTON_STATE = 0xF5, LEFTSENSOR = 0xF6, RIGHTSENSOR = 0xF7, LEFTSPEED = 0xF8, RIGHTSPEED = 0xF9, LEDCOLOR = 0xFA, INFO = 0xFB};
void transmitButton();
void transmitLeftSensor();
void transmitRightSensor();
void diagnostic_run();
void sendInfo();
void operateRightWheel(uint8_t data);
void operateLeftWheel(uint8_t data);
void operateLED(uint8_t data);
void action(uint8_t request, uint8_t data);



#endif /* DIAGNOSTIC_H */