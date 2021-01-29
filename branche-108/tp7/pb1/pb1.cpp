/************************************************************************************	
//Fichier probleme2.cpp
//	Auteur Maude Laflamme et Elisabeth Fagnan
//	Date 1er mars 2018
//	Descr Programme permettant de faire clignoter la del dans differents etats
************************************************************************************/


#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>


const uint8_t PIN_2 = (1 << 2); 		//Constante permettant d'acceder à la PIN 2 d'un port.

/**********************************************************************************************
* Fonction: Anti-rebond
* Description: Permet de s'assurer que le bouton-poussoir est bien appuyé
* Paramètres: aucun
* Retour: Retourne un boolean indiquant si le bouton-poussoir est appuyé (true) ou pas (false).
**********************************************************************************************/
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
	enum Lumiere { initial, compt, clignoteVert, rien, clignoteRouge, vert2 };		//Les 6 états de la DEL selon le bouton-poussoir
	
	const uint8_t rouge = 0b00000001;		//DEL couleur rouge
	const uint8_t vert = 0b00000010;        //DEL couleur verte
	const uint8_t off = 0b00000000;         //DEL éteinte   
	
	Lumiere state = initial; 				//État initial de la DEL
	int compteur = 0;	//Éviter les variables globales
	
	
	for(;;){
		switch(state)
		{
			case initial : 		PORTC=off;
								if(interrupteurEstActionne()){
									state=compt;
								}
								else
									state = initial;
								break;
								
								
			
			
			
			case compt :		while (interrupteurEstActionne()){
									//if(interrupteurEstActionne()){
										_delay_ms(100);
										compteur+=1;
										if (compteur >= 120)
											break;
									//}	
								}
								state = clignoteVert;	
								break;
								
			case clignoteVert : 	for(unsigned i=0; i<3;i++){	//Boucle for permettant de faire clignoter la DEL pendant 1/2 seconde.					
									PORTC = vert;
									_delay_ms(100); 			//Delai permettant de faire clignoter la DEL 
									PORTC = off;
									_delay_ms(100);
								}							
								state = rien;
								break;
								
			case rien : 		PORTC = off;
								_delay_ms(2000);
								state = clignoteRouge;
								break;
								
			case clignoteRouge :	for(int i=0; i < (compteur/2); i++){		//Boucle for permettant de faire clignoter la DEL 2 fois par 
									PORTC = rouge;								//seconde pour compteur/2 fois.
									_delay_ms(250);
									PORTC = off;
									_delay_ms(250);
								}
								compteur =0;
								state = vert2;
								break;
								
			case vert2 : 		PORTC = vert;
								_delay_ms(1000);
								PORTC = off;
								state = initial;
								break;
	
		}
		
	}
	return 0;
}
					  
