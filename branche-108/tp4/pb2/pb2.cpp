#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/sfr_defs.h>

using namespace std;

int main()
{
	DDRA = 0xff;		//DDRA est en mode sortie
	DDRC = 0b00000011;		//DDRC est en mode sortie
	DDRB = 0xff;		//DDRB est en mode sortie
	DDRD = 0xff;		//DDRD est en mode entree
	
	
const uint8_t roule = 0b00000010;			 	//Roues en fonction
const uint8_t immobile = 0b00000000; 		     //Roues immobiles
	
	PORTC=0b00000000;
	int A= 0;
	int C = 17;
	const int B =17;
	
	for(;;){
		
	for(uint32_t i=0;i<1600000;i++){ 
		 PORTC= roule;
		 for(int i = 0; i<A; i++){
		_delay_ms(1);
		}
	
		PORTC=immobile;
		for(int i = 0; i<C; i++){
		_delay_ms(1);
		}
	}
	//PORTC=immobile;
	A+=B/4; 
	C-=B/4;
		
	}
return 0;
}
