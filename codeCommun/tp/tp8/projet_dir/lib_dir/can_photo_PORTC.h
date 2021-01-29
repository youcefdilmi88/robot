#ifndef CAN_PHOTO_PORTC_H
#define CAN_PHOTO_PORTC_H

#include <avr/io.h> 
#include <util/delay.h>
#include <can.h>
#include "LED_amber_PORTC.h"


void can_photo(can myCan, uint8_t inf_thresh, uint8_t sup_thresh);

#endif /* CAN_PHOTO_PORTC_H */