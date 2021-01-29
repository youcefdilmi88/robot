#ifndef _PARCOURS_H_
#define _PARCOURS_H_



#include "value_to_interval.h"
#include "avr/io.h"
#include "sensors.h"
#include "PWM_PORTD.h"
#include "start_timer_CTC.h"






enum state_t { NORMAL, SWITCH_WALL_LEFT, SWITCH_WALL_RIGHT, RIGHT_WALL_END, LEFT_WALL_END};


void init_INT0(void);
state_t next_state(state_t s, uint16_t leftSensor, uint16_t rightSensor);
state_t next_state_normal(uint16_t leftSensor, uint16_t rightSensor);
state_t next_state_wall_end(uint16_t leftSensor, uint16_t rightSensor);
state_t next_state_switch_wall_left(uint16_t leftSensor, uint16_t rightSensor);
state_t next_state_switch_wall_right(uint16_t leftSensor, uint16_t rightSensor);
void switch_wall_left_action();
void switch_wall_right_action();
void state_action(state_t state);
void normal_action();
void left_wall_end_action();
void right_wall_end_action();


uint8_t offset(uint16_t lecture);
void parcours_run();


enum capteur{GAUCHE, DROITE};

extern state_t current_state;
extern capteur capteur_principal;
extern capteur capteur_secondaire;
extern uint8_t transition_a_faire;

#endif /*_PARCOURS_H_ */
