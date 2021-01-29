#include "init_INT0.h"



/**
* @brief Initialise le vecteur d'interruption INT0_vect en remplissant les bons registres
* @return void
*/
void init_INT0(void)
{
    cli (); // cli() bloque les interruptions.
    EIMSK |= (1<<INT0); // Enable external interrupts
    EICRA |= (1<<ISC00); // Set INT0_vect to logical change 
    sei (); // sei permet de recevoir à nouveau des interruptions.
}