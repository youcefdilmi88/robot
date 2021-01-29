/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//Fichier pb2.cpp
//	Auteur Maude Laflamme et Elisabeth Fagnan
//	Date 1er mars 2018
//	Descr Programme permettant de changer la couleur de la DEL en fonction de la lumiere captee par une photoresistance.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <can.h>

	
int main(){
	
	
	DDRA = 0x00;		//DDRA est en mode entree
	DDRC = 0xff;		//DDRC est en mode sortie
	DDRB = 0xff;		//DDRB est en mode sortie
	DDRD = 0xff;		//DDRD est en mode sortie
	
	//Declaration des constantes
	const uint8_t ROUGE = 0b00000001;		// DEL couleur rouge
	const uint8_t VERT = 0b00000010;        // DEL couleur verte
	const uint8_t BASSE_BORNE =160;         //Borne max du niveau dintensite pour lumiere a faible intensite
	const uint8_t AMBIANTE_BORNE =245;      //Borne max du niveau dintensite pour lumiere ambiante
	
	can CAN;


	for(;;){
		
		uint8_t intensiteLumineuse = CAN.lecture(0) >> 2; // On decale le resultat de lecture de 2 bits pour conserver uniquement les 8 bits significatifs
		
		//La lumiere est basse 
		if(intensiteLumineuse < BASSE_BORNE )
			PORTC=VERT;
			
		//Le robot bronze : lumiere ambiante
		else if (intensiteLumineuse < AMBIANTE_BORNE && intensiteLumineuse > BASSE_BORNE ){
			PORTC=VERT;
			_delay_ms(5);
			PORTC=ROUGE;
			_delay_ms(5);	
		}
		
		//Le robot a un coup de soleil : lumiere de lampe de poche
		else if (intensiteLumineuse > AMBIANTE_BORNE) 
			PORTC = ROUGE;		
		
	 }
	 
return 0;
}
