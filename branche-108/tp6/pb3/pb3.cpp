#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <memoire_24.h>
#include <util/twi.h>

void initialisationUART ( void ) {

	// 2400 bauds. Nous vous donnons la valeur des deux

	// premier registres pour vous éviter des complications

	UBRR0H = 0;

	UBRR0L = 0xCF;

	// permettre la reception et la transmission par le UART0

	UCSR0A = 0;

	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	// Format des trames: 8 bits, 1 stop bits, none parity

	UCSR0C = (1 << UCSZ00) ;	//00000110
	UCSR0C |= 1 << UCSZ01;

}

// De l'USART vers le PC

void transmissionUART ( uint8_t donnee ) {

 /* Wait for empty transmit buffer */
 while ( !( UCSR0A & (1<<UDRE0)) )
 ;
 /* Put data into buffer, sends the data */
 UDR0 = donnee;

}

int main()
{
	initialisationUART();


	Memoire24CXXX allo;
	
	unsigned char phrase[47] = "E*C*O*L*E**P*O*L*Y*T*E*C*H*N*I*Q*U*E*00000000";
	
	unsigned char* ptr = phrase;					//&phrase[0] ?
	allo.ecriture(0x0000,ptr,47);			//longueur = nombre de char X 8 bits? 
	_delay_ms(5);
	
	unsigned char phraseLue[47];										
	unsigned char* ptrLu = phraseLue;
	
	allo.lecture(0x0000,ptrLu, 47);			

uint8_t i, j;

for ( i = 0; i < 10; i++ ) {

	for ( j=0; j < 47; j++ ) {

		transmissionUART( phraseLue[j] );

//USART_Receive();
		}
	}
	
return 0;
}
