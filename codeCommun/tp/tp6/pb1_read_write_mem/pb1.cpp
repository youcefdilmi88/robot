#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <util/twi.h>
#include "memoire_24.h"

using namespace std;


int main(){
	const uint8_t rouge = 0b00000001;
	const uint8_t vert = 0b00000010; 
	DDRB = 0xff; // PORT B est en mode sortie


	Memoire24CXXX allo;
	
	unsigned char phrase[47] = "E*C*O*L*E**P*O*L*Y*T*E*C*H*N*I*Q*U*E*00000000";
	
	unsigned char* ptr = phrase;				
	allo.ecriture(0x0000,ptr,47);			
	_delay_ms(5);
	
	unsigned char phraseLue[47];
	unsigned char* ptrLu = phraseLue;
	
	allo.lecture(0x0000,ptrLu,47);
	bool estPareil;
	for(int i =0; i<47; i++){
		if(phrase[i]==phraseLue[i])
				estPareil = true;
			else{
				estPareil = false;
				break;
			}
		}
	if(estPareil)
		PORTB = vert;
	else
		PORTB = rouge;
}
