////////////////////////////////////////////////////////////////////////////////////	
//Fichier probleme2.cpp
//	Auteur Maude Laflamme et Elisabeth Fagnan
//	Date 26 janvier 2018
//	Descr Programme permettant dallumer la DEL en rouge apres 5 appuis sur le bouton poussoir
/////////////////////////////////////////////////////////////////////////////////////

/*
 * 
 * Tableau d'état pour le problème 1
 * 
 * Etat	   PIND	     Compteur	        Etat suivant    PORTC
 *Eteint	1     (compteur+1)<5	      eteint	      0
 *Eteint	0	      compteur<5	      eteint	      0
 *Eteint	1	    compteur+1=5	      Allumé	      0
 *Allumé	X	      compteur=0	      Eteint	      1
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/sfr_defs.h>



const uint8_t PIN_2 = (1 << 2); 		// Constante permettant d'accéder à la PIN 2 d'un port 

//Fonction Antirebond

bool interrupteurEstActionne()
{
	if(PIND & PIN_2) {			
		_delay_ms(10);
		if(PIND & PIN_2) {
			return true;
		}
		return false;
	}
	return false;
}

int main()
{
	DDRA = 0xff;		//DDRA est en mode sortie
	DDRC = 0xff;		//DDRC est en mode sortie
	DDRB = 0xff;		//DDRB est en mode sortie
	DDRD = 0x00;		//DDRD est en mode entree


//Déclaration de constantes

	enum Lumiere { eteint, allume }; 		 //États possibles de la DEL
	const uint8_t eteinte = 0x00;			 //DEL éteinte 
	const uint8_t rouge = 0x01; 		     //DEL couleur rouge
	uint8_t compteur = 0;					 //Initialisation du compteur d'appui de l'interrupteur

	Lumiere state = eteint;

	for(;;) {			
						 
		if (interrupteurEstActionne())  {
			compteur++;
			_delay_ms(200);				//Délai ralentissant la vitesse d'éxecution du programme
		}
			
		if (compteur < 5) {
			state = eteint;
		}
				
		else if (compteur == 5) {
			state = allume;
		}
				
		switch (state) {
			case eteint : 
				PORTC = eteinte;
				break;
					 
			case allume : 
				PORTC = rouge;
			  _delay_ms(1000);
			  state = eteint;
			  compteur = 0;
			  break;
		}
	}
return 0;
}

							 
