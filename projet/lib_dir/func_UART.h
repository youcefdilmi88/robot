
#ifndef FUNC_UART_H
#define FUNC_UART_H

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

void UART_transmit(uint8_t donnee);
void UART_transmit_string(char* string);
void initialisationUART( void );
void initialisationUART_RECEIVE_INT ( void );
void UART_transmit_number_left(uint16_t nombre);
void UART_transmit_number_right(uint16_t nombre);
void UART_transmit_number(uint16_t nombre);
unsigned char UART_receive( void );

#endif /* FUNC_UART_H */