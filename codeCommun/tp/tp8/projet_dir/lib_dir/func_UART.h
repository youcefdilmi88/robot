
#ifndef FUNC_UART_H
#define FUNC_UART_H

#include <avr/io.h>
#include <stdio.h>

void UART_transmit(uint8_t donnee);
void UART_transmit_string(char* string);
void initialisationUART ( void );
void UART_transmit_number(uint16_t nombre);
unsigned char USART_Receive( void );

#endif /* FUNC_UART_H */