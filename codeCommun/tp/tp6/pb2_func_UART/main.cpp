/*
 * File   : main.cpp
 * Author : Frederic Brossard-Pellerin (1908718) and Youcef Anis Dilmi (1895231)
 * Date   : 01/02/18
 * Descr  : TP6 Probleme 2
*/


#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <stdio.h>

/*constants*/
const uint8_t RED = 0x01;
const uint8_t GREEN = 0x02;
const uint8_t OFF = 0x00;
const uint8_t IN = 0x00;
const uint8_t OUT = 0xFF;

void initialisationUART ( void ) 
{
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premier registres pour vous éviter des complications
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la reception et la transmission par le UART0
    UCSR0A = 0 ;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void UART_transmit(uint8_t donnee) {
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) ){}
    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

void UART_transmit_string(char* string) {
    for (uint8_t i=0; i<100; i++) {
        UART_transmit(string[i]);
    }
}

void UART_transmit_number(uint16_t nombre) {
    char buff[100];
    sprintf(buff, "nombre=%d\n",nombre);
    UART_transmit_string(buff);
}

int main()
{
    char mots[21] = "Le robot en INF1995\n";
    initialisationUART();
    uint8_t i, j;
    for ( i = 0; i < 100; i++ ) {
        for ( j=0; j < 20; j++ ) {
            UART_transmit(mots[j]);
        }
    }
    return 0;
}
