/* 
 * Fichier: ecriture_mem.cpp
 * Auteurs: Maude Laflamme(1690784), Elisabeth Fagnan(1893587) et Youcef Anis Dilmi(1895231)
 * Équipe: 96108
 * Remise: 21 mars 2018
 * Description: Envoie du fichier binaire dans la mémoire externe et vérification de la validité
 */


#include <avr/io.h> 
#include <util/delay.h>
#include <memoire_24.h>
#include <func_UART.h>
#include <LED_PORTA.h>

const uint8_t OUTPUT = 0xFF;
const uint8_t INTPUT = 0x00;


int main()
{
	DDRA = OUTPUT;
	Memoire24CXXX myMem;
	uint8_t donnee = 0x00;
	uint16_t adresse = 0x0000;
	uint16_t size = 0x0000;
	uint8_t buffer = 0x00;
	initialisationUART();

	// Boucle de réception et écriture dans la mémoire des deux premiers octets du fichier binaire
	// contenants la taille (en octets) du fichier
	for(uint8_t i=0; i<2 ; i++){
		donnee = UART_receive();
		myMem.ecriture(adresse++,donnee);
		buffer = donnee;
		size = (size << 8) | buffer;
		_delay_ms(5);	
	}

	// Boucle de réception et écriture dans la mémoire de tous les octets du fichier binaire
	// contenants les instructions et opérande.
	for(uint8_t i=0;i<(size-2) ; i++) {
		donnee = UART_receive();
		myMem.ecriture(adresse++,donnee);			
		_delay_ms(5);
	}

	// Donne 7 secondes de délais pour avoir le temps d'executer serieViaUSB -l	
	PORTA = RED;
	_delay_ms(7000);
	PORTA = OFF;
	
	// Boucle de lecture et transmission des octets écris en mémoire pour pouvoir 
	// les intercepter avec serieViaUSB - et pouvoir confirmer qu'ils sont valides.
    uint16_t adresse_test = 0x0000;
	uint8_t donnee_test = 0x00;
    for (uint8_t i=0; i<size; i++) {
		myMem.lecture(adresse_test++,&donnee_test);
		_delay_ms(5);
		UART_transmit_number(donnee_test);
    }

	return 0;
}
