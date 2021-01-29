////////////////////////////////////////////////////////////////////////////////////	
//Fichier probleme2.cpp
//	Auteur Maude Laflamme et Elisabeth Fagnan
//	Date 26 janvier 2018
//	Descr Programme permettant de faire clignoter la del dans differents etats
/////////////////////////////////////////////////////////////////////////////////////


#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>


//volatile enum Lumiere { rougeInitial, ambre, vert1, rouge2, eteint, vert2 };// Les 6 états de la DEL selon le bouton-poussoir
volatile int state =1; 										//État initial de la DEL
//volatile uint8_t action;
volatile const uint8_t PIN_2 = (1 << 2);									// Constante permettant d'accéder à la PIN 2 d'un port 
volatile const uint8_t rouge = 0b00000001;
volatile const uint8_t vert = 0b00000010;        // DEL couleur verte
volatile const uint8_t off = 0b00000000; 
//volatile uint8_t bonjour;
// Fonction de l'anti-rebonds

ISR (INT0_vect) {

	// laisser un delai avant de confirmer la réponse du

	// bouton-poussoir: environ 30 ms (anti-rebond)
	//PORTC = rouge;
	_delay_ms(30);
	
	if(PIND & PIN_2) {
		state++;
	}
	

		
	// se souvenir ici si le bouton est pressé ou relâché
	
	
	

	// changements d'états tels que ceux de la semaine précédente

	//'modifier ici'

	// Voir la note plus bas pour comprendre cette instruction et son rôle

	EIFR |= (1 << INTF0) ;			

}

void initialisation ( void ) {

	  cli ();
	   
	  // configurer et choisir les ports pour les entrees
	  // et les sorties. DDRx... Initialisez bien vos variables
	   
	  DDRB = 0xff; // PORT B est en mode sortie
	  DDRD = 0x00; // PORT D est en mode entree
		
	  // cette procédure ajuste le registre EIMSK
	  // de ATmega324PA pour permettre les interruptions externes
	  EIMSK |= (1 << INT0);
	 
	  // il faut sensibiliser les interruptions externes aux
	  // changement de niveau du bouton-poussoir
	  // en ajustant le registre EICRA

	  
	  EICRA |= (1 << ISC00);
	  EICRA &= (0 << ISC01);
	  sei ();

}


int main()
{
	initialisation();
	//enum Lumiere { rougeInitial, ambre, vert1, rouge2, eteint, vert2 };
	//Lumiere state = rougeInitial;
	//int etat;
	//action=0;
//Déclaration de constantes	
	//const uint8_t rouge = 0b00000001;		// DEL couleur rouge
	//const uint8_t vert = 0b00000010;        // DEL couleur verte
	//const uint8_t off = 0b00000000;         // DEL éteinte   
	/*bonjour = 0 ;
	PORTB =0x00;
	for(;;){
	while(bonjour ==1) {
		PORTB = 0x01;
	}
	
	PORTB=0x00;
	//bonjour =0;
}*/

	
	for(;;){		
		switch(state)
		{
			case 1 : PORTB = rouge;
								//if (INT0==0x01)
									//state = ambre;
										
								break;
								
			case 2 : 		//while (interrupteurEstActionné()){							
									
									PORTB = vert;
									_delay_ms(5); 				//Délai permettant d'afficher la couleur ambré
									PORTB = rouge;
											
								//state = vert1;
								break;
								
			case 3 : 		PORTB = vert;
								//if (interrupteurEstActionné())
									//state = rouge2;
								break;
								
			case 4 : 		//while (interrupteurEstActionné()){
									PORTB = rouge;
								
								//state = eteint;
								break;
								
			case 5 : 		PORTB = off;
								//if (interrupteurEstActionné())
									//state = vert2;
								break;
								
			case 6 : 		//while (interrupteurEstActionné()){
									PORTB = vert;
									_delay_ms(100);
									state =1;
								//state = rougeInitial;
								break;
		
	}
	}
	return 0;
}

