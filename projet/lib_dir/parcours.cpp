#include "parcours.h"
#include <util/delay.h>



state_t current_state = NORMAL;
capteur capteur_principal;
capteur capteur_secondaire;
volatile bool canChangeWall = true;


/********************************************
 * @brief Active l'interruption externe lors de l'appui du bouton Interrupt.
 * @param ---
 * @return void
 ********************************************/

void init_INT0(void)
{
    cli();// bloque les interruptions.
    EIMSK |= (1 << INT0); // Enable external interrupts
    EICRA |= (1<<ISC00); // Set INT0_vect to logical change 
    sei();// permet de recevoir à nouveau des interruptions.
}

/********************************************
 * @brief Machine à état qui change l'état en fonction de l'état présent et de la valeur reçue des capteurs.
 * @param ---
 * @return void
 ********************************************/
void parcours_run()
{
	DDRB = OUTPUT;
	DDRC = OUTPUT;
	DDRD = 0xF0;
	init_INT0();
	init_pwm();
	sensors.initConversion();
	LED_parcours();
	if (sensors.getLeft() > 280){
		capteur_principal = GAUCHE;
		capteur_secondaire = DROITE;
	}
	else if (sensors.getRight() > 280){
		capteur_principal = DROITE;
		capteur_secondaire = GAUCHE;
	}
	for(;;) {
			current_state = next_state(current_state, sensors.getLeft(), sensors.getRight());
			state_action(current_state);
	}
}

/********************************************
 * @brief Appelle l'action en fonction de l'état présent
 * @param state_t state, l'état présent
 * @return void
 ********************************************/
void state_action(state_t state)
{
	switch(state)
	{
		case NORMAL:
			normal_action();
			break;

		case SWITCH_WALL_LEFT:
			switch_wall_left_action();
			break;

		case SWITCH_WALL_RIGHT:
			switch_wall_right_action();
			break;

		case RIGHT_WALL_END:
			right_wall_end_action();
			break;

		case LEFT_WALL_END:
			left_wall_end_action();
			break;

		default:
			break;
	}
}

/********************************************
 * @brief Ajuste le robot afin qu'il soit à 15 cm du mur
 * @param ---
 * @return void
 ********************************************/
void normal_action()
{

	if (capteur_principal == GAUCHE){
		uint8_t outSpeed = offset(sensors.getLeft()) + 120;
		set_pwm(120 , outSpeed, FORWARD, FORWARD);
	}
	else if (capteur_principal == DROITE){
		uint8_t outSpeed = offset(sensors.getRight()) + 120;
		set_pwm(outSpeed, 120, FORWARD, FORWARD);
	}
}


/********************************************
 * @brief Calcule la correction à appliquer aux roues pour conserver une distance de 15 cm du mur.
 * @param uint16_t lecture, la valeur reçue du capteur.
 * @return uint8_t la correction à appliquer.
 ********************************************/
uint8_t offset(uint16_t lecture)
{
	Interval_parcours interval;
	if  (capteur_principal == GAUCHE) 
		interval = value_to_interval_parcours_left(lecture);
	else
		interval = value_to_interval_parcours_right(lecture);

	uint8_t correction;

	if (interval == LESS_100){
		correction = -50;
		PORTC = RED;
	}
	else if (interval == IN_100_125){
		correction =  -30;
		PORTC = RED;
	}
	else if (interval == IN_125_150){
		correction = -20;
		PORTC = GREEN;
	}
	else if (interval == IN_150_175){
		correction = 20;
		PORTC = GREEN;
	}
	else if (interval == IN_175_200){
		correction =  30;
		PORTC = RED;
	}
	else if (interval == IN_200_225){
		correction = 30;
		PORTC = RED;
	}
	else if (interval == IN_225_250){
		correction = 30;
		PORTC = RED;
	}
	else if (interval == IN_250_275){
		correction = 20;
		PORTC = RED;
	}
	else if (interval == IN_275_300){
		correction = 20;
		PORTC = RED;
	}
	else if (interval == IN_300_600){
		correction = 20;
		PORTC = RED;
	}
	else 
		correction = 0;

	return correction;

}



/********************************************
 * @brief Détermine l'état suivant en fonction de l'état présent et des valeurs des capteurs.
 * @param state_t state, l'état présent
 * @param uint16_t leftSensor, la valeur du capteur gauche.
 * @param uint16_t rightSensor, la valeur du capteur droit.
 * @return state_t next_state, le prochaine état.
 ********************************************/
state_t next_state(state_t state, uint16_t leftSensor, uint16_t rightSensor)
{
	state_t new_state = NORMAL;
	switch(state)
	{
		case NORMAL:
			new_state = next_state_normal(leftSensor, rightSensor);
			break;
		case SWITCH_WALL_LEFT:
			new_state = next_state_switch_wall_left(leftSensor, rightSensor);		
			break;
		case SWITCH_WALL_RIGHT:
			new_state = next_state_switch_wall_right(leftSensor, rightSensor);
			break;
		case RIGHT_WALL_END:
			new_state = next_state_wall_end(leftSensor, rightSensor);
			break;
		case LEFT_WALL_END:
			new_state = next_state_wall_end(leftSensor, rightSensor);
			break;

	}
	return new_state;
}


/********************************************
 * @brief Détermine l'état suivant l'état normal, en fonction des valeurs des capteurs.
 * @param uint16_t leftSensor, la valeur du capteur gauche.
 * @param uint16_t rightSensor, la valeur du capteur droit.
 * @return state_t next_state_normal, le prochain état.
 ********************************************/
state_t next_state_normal(uint16_t leftSensor, uint16_t rightSensor)
{

	if ((capteur_principal == DROITE) && (100 <= leftSensor) && (leftSensor <= 340)){
			_delay_ms(100);
			uint16_t left_Sensor = sensors.getLeft();
			if ((100 <= left_Sensor) && (left_Sensor <= 340)){
				for(uint8_t i=0; i < 4; i++){
					_delay_ms(250);
					normal_action();
				}
            	left_Sensor = sensors.getLeft();
        		if (left_Sensor < 100) {
        			startTimerCTC_INT_2(78);
            		return NORMAL;
            	}
            	else if ((100 <=left_Sensor) && (left_Sensor <= 340) && (canChangeWall))
					return SWITCH_WALL_LEFT;

		}
	}
    else if ((capteur_principal == GAUCHE) && (100 <= rightSensor) && (rightSensor <= 340)){
		_delay_ms(100);
		uint16_t right_Sensor = sensors.getRight();
		if ((100 <= right_Sensor) && (right_Sensor <= 340)){
    		for(uint8_t i=0; i < 4; i++){
				_delay_ms(250);
				normal_action();
			}
			right_Sensor = sensors.getRight();
			if (right_Sensor < 100) {
				startTimerCTC_INT_2(78);
				return NORMAL;
			}
			else if ((100 <= right_Sensor) && (right_Sensor <= 340) && (canChangeWall))
				return SWITCH_WALL_RIGHT;
		}
    }

    else if ((rightSensor <= 120) && (leftSensor <=120)){
        if(capteur_principal == DROITE){
			canChangeWall= true;			//Redonne le droit de changer de mur lorsqu'il n'y a plus de mur interdit
            return RIGHT_WALL_END;
        }
        else if(capteur_principal== GAUCHE){
			canChangeWall = true;
            return LEFT_WALL_END;
        }
    }
    
	else if ((capteur_principal == GAUCHE) && (rightSensor < 120)){
			_delay_ms(50);
			uint16_t right_Sensor = sensors.getRight();
			if (right_Sensor < 120)
				canChangeWall = true;		//Redonne le droit de changer de mur lorsqu'il n'y a plus de mur interdit
	}
					
	else if ((capteur_principal == DROITE) && (leftSensor <120)){
			_delay_ms(50);
			uint16_t left_Sensor = sensors.getLeft();
			if (left_Sensor < 120)
				canChangeWall = true;
	}


	return NORMAL;
}


/********************************************
 * @brief Détermine l'état suivant l'état switch_wall, en fonction des valeurs des capteurs.
 * @param uint16_t leftSensor, la valeur du capteur gauche.
 * @param uint16_t rightSensor, la valeur du capteur droit.
 * @return state_t next_state_switch_wall_left, le prochain état.
 ********************************************/
state_t next_state_switch_wall_left(uint16_t leftSensor, uint16_t rightSensor)
{
	if (250 <= leftSensor) {
			capteur_principal = GAUCHE;
			capteur_secondaire = DROITE;
			canChangeWall = false;	//Enlève le droit de changer de mur après un changement de mur
			return NORMAL;
		}
	return SWITCH_WALL_LEFT;

}

/********************************************
 * @brief Ajuste les roues afin de changer de mur vers la gauche.
 * @param --
 * @return void
 ********************************************/
void switch_wall_left_action(){
	PORTC = RED;
	set_pwm(170,170, BACKWARD, FORWARD);
	_delay_ms(100);
	set_pwm(170,170, FORWARD, 	FORWARD);
	_delay_ms(500);
	set_pwm(170,170, FORWARD, 	BACKWARD);
	_delay_ms(95);
}

/********************************************
 * @brief Détermine l'état suivant l'état switch_wall, en fonction des valeurs des capteurs.
 * @param uint16_t leftSensor, la valeur du capteur gauche.
 * @param uint16_t rightSensor, la valeur du capteur droit.
 * @return state_t next_state_switch_wall_right, le prochain état.
 ********************************************/
state_t next_state_switch_wall_right(uint16_t leftSensor, uint16_t rightSensor)
{
	if (250 <= rightSensor) {
			capteur_principal = DROITE;
			capteur_secondaire = GAUCHE;
			canChangeWall = false;	//Enlève le droit de changer de mur après un changement de mur
			return NORMAL;
		}
	return SWITCH_WALL_RIGHT;

}

/********************************************
 * @brief Ajuste les roues afin de changer de mur vers la droite.
 * @param --
 * @return void
 ********************************************/
void switch_wall_right_action(){
	PORTC = RED;
	set_pwm(170, 170, FORWARD, BACKWARD);
	_delay_ms(90);
	set_pwm(170,170, FORWARD, FORWARD);
	_delay_ms(500);
	set_pwm(170, 170, BACKWARD, FORWARD);
	_delay_ms(95);
}


/********************************************
 * @brief Ajuste les roues afin de faire demi-tour au bout d'un mur du côté droit.
 * @param --
 * @return void
 ********************************************/
void right_wall_end_action(){
	PORTC = RED;
    set_pwm(220, 130, FORWARD, FORWARD);
    _delay_ms(300);
}

/********************************************
 * @brief Ajuste les roues afin de faire demi-tour au bout d'un mur du côté gauche.
 * @param --
 * @return void
 ********************************************/
void left_wall_end_action(){
	PORTC = RED;
    set_pwm(130, 220, FORWARD, FORWARD);
    _delay_ms(300);
}

/********************************************
 * @brief Détermine l'état suivant l'état wall_end, en fonction des valeurs des capteurs.
 * @param uint16_t leftSensor, la valeur du capteur gauche.
 * @param uint16_t rightSensor, la valeur du capteur droit.
 * @return state_t next_state_wall_end, le prochain état.
 ********************************************/
state_t next_state_wall_end(uint16_t leftSensor, uint16_t rightSensor)
{
    if(capteur_principal == GAUCHE){
        if(leftSensor <= 120)
            return LEFT_WALL_END;
    }
    else if (capteur_principal== DROITE){
        if(rightSensor <= 120){
            return RIGHT_WALL_END;
        }
    }
    return NORMAL;
}




