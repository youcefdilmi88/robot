#include "LED_amber_PORTA.h"
#include "can.h"
#include "start_timer_CTC.h"
#include "PWM_PORTD.h"



int main()
{
can myCan;
LED_amber();
startTimerCTC(255);
init_pwm();
return 0;
}