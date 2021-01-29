////////////////////////////////////////////////////////////////////////////////////	
//Fichier probleme2.cpp
//	Auteur Maude Laflamme et Elisabeth Fagnan
//	Date 26 janvier 2018
//	Descr Programme permettant de faire clignoter la del dans differents etats
/////////////////////////////////////////////////////////////////////////////////////

/*
 * 		Etat	     PIND	Etat suivant	PORTC
 * 
 *	Rouge Initial		0	RougeInitial	0x01
 *	Rouge Initial		1	Ambre			Oscillation entre 0x01 et 0x02
 *	Ambre				0	Vert1			0x02
 *	Ambre				1	Ambre			Oscillation entre 0x01 et 0x02
 *	Vert1				0	Vert1			0x02
 *	Vert1				1	Rouge2			0x01
 *	Rouge2				0	Eteint			0x00
 *	Rouge2				1	Rouge2			0x01
 *	Eteint				0	Eteint			0x00
 *	Eteint				1	vert2			0x00
 *	Vert2				0	RougeInitial	0x01
 *	Vert2				1	vert2			0x02
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



const uint8_t PIN_2 = (1 << 2);			// Constante permettant d'accéder à la PIN 2 d'un port 

// Fonction de l'anti-rebonds

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

//Déclaration de constantes
	
	
	DDRA = 0xff;		//DDRA est en mode sortie
	DDRC = 0xff;		//DDRC est en mode sortie
	DDRB = 0xff;		//DDRB est en mode sortie
	DDRD = 0x00;		//DDRD est en mode entree

	enum Lumiere { rougeInitial, ambre, vert1, rouge2, eteint, vert2 };		// Les 6 états de la DEL selon le bouton-poussoir
	
	const uint8_t rouge = 0b00000001;		// DEL couleur rouge
	const uint8_t vert = 0b00000010;        // DEL couleur verte
	const uint8_t off = 0b00000000;         // DEL éteinte   
	
	Lumiere state = rougeInitial; 			//État initial de la DEL


	for(;;){
		switch(state)
		{
			case rougeInitial : PORTC = rouge;
								if (interrupteurEstActionne())
									state = ambre;	
								break;
								
			case ambre : 		while (interrupteurEstActionne()){							
									PORTC = rouge;
									_delay_ms(5); 				//Délai permettant d'afficher la couleur ambré
									PORTC = vert;
								}							
								state = vert1;
								break;
								
			case vert1 : 		PORTC = vert;
								if (interrupteurEstActionne())
									state = rouge2;
								break;
								
			case rouge2 : 		while (interrupteurEstActionne()){
									PORTC = rouge;
								}
								state = eteint;
								break;
								
			case eteint : 		PORTC = off;
								if (interrupteurEstActionne())
									state = vert2;
								break;
								
			case vert2 : 		while (interrupteurEstActionne()){
									PORTC = vert;
								}
								state = rougeInitial;
								break;
		}
		
	}
	return 0;
}
					  
