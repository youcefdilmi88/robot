#include "can_photo_PORTC.h"

const uint8_t RED = 0x01;
const uint8_t GREEN = 0x10;
const uint8_t INF_THRESH = 160;
const uint8_t SUP_THRESH = 245;


/*Connexions
DEL libre = PORTD(0,1)
/**
* @brief Put LED light in specific color depending on light intensity
* @param myCan Object of class can, used to read value from analog-digital converter
* @param inf_thresh Inferior threshold for for turning LED from amber to green
* @param sup_thresh Superior threshold for turning LED from amber to red
* @return void
*/
void can_photo(can myCan, uint8_t inf_thresh, uint8_t sup_thresh)
{
    for(;;) {
        uint8_t analog_signal = myCan.lecture(0) >> 2; //myCan.lecture() function returns a uint16_t.
        if(analog_signal < inf_thresh) {               //We need to remove 2 LSB with bit shift to get an 8 bits, 0 to 255 value depending on 0 to 5V signal
            PORTC=GREEN;
        }
        else if ((analog_signal > inf_thresh) && (analog_signal < sup_thresh)) {
            LED_amber();
        }
        else if (analog_signal > sup_thresh) {
            PORTC = RED;		
        }
    }
}