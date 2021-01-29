#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/sfr_defs.h>


int main()
{
	DDRA = 0xff;		//DDRA est en mode sortie
	DDRC = 0xff;		//DDRC est en mode sortie
	DDRB = 0xff;		//DDRB est en mode sortie
	DDRD = 0x00;		//DDRD est en mode entree

const uint8_t eteinte = 0x00;			 //DEL éteinte 
const uint8_t rouge = 0x01; 		     //DEL couleur rouge


	int A=1400;
	 int B = 0;
	
	for(;;){
		PORTC = rouge;
		for(int i = 0; i<A; i++){
		_delay_us(1);
	}
	
	PORTC = eteinte;
	for(int i = 0; i<B; i++){
		_delay_us(1);
	}
	
	A-=1;
	B+=1;
		
	}
return 0;
}
